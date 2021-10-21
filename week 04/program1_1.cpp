#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/

void program1_1(FILE* fp) {
	double initialGuess, result, before, difference;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Enter Your Initial Guess: ");
	scanf("%lf", &initialGuess);
	
	result = initialGuess;
	fprintf(fp, " n             xn1                  |f(xn1)|\n");
	printf(" n             xn1                  |f(xn1)|\n");
	
	for (n = 0; n < Nmax; n++) {
		before = result;
		result = before - _f(before) / _fp(before);

		if (result < DELTA)
			break;
		difference = before - result;
		if (difference > -1 * EPSILON && difference < EPSILON)
			break;
		
		fprintf(fp, "%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
		printf("%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
	}
	fprintf(fp, "\n");
	printf("\n");
}
