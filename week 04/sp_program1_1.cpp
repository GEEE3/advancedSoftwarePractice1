#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/

void sp_program1_1(FILE* fp) {
	float initialGuess, result, before, difference;
	float sp_DELTA = 0.0000001, sp_EPSILON = 0.0000001;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Enter Your Initial Guess: ");
	scanf("%f", &initialGuess);
	result = initialGuess;

	fprintf(fp, " n             xn1                  |f(xn1)|\n");
	printf(" n             xn1                  |f(xn1)|\n");

	for (n = 0; n < Nmax; n++) {
		before = result;
		result = before - _sp_f(before) / _sp_fp(before);

		if (result < sp_DELTA)
			break;		
		difference = before - result;
		if (fabs(difference) < sp_EPSILON)
			break;

		fprintf(fp, "%03d   %.15e   %.15e\n", n, result, fabs(_sp_f(result)));
		printf("%03d   %.15e   %.15e\n", n, result, fabs(_sp_f(result)));
	}
	fprintf(fp, "\n");
	printf("\n");
}
