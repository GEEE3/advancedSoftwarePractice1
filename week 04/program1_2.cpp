#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/

void program1_2(FILE* fp) {
	double temp, left, right, difference, result, before;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Enter Your Initial Guess: ");
	scanf("%lf %lf", &left, &right);

	if (left > right) {
		temp = left;
		left = right;
		right = temp;
	}

	before = left;
	result = right;
	fprintf(fp, " n             xn1                  |f(xn1)|\n");
	printf(" n             xn1                  |f(xn1)|\n");

	for (n = 0; n < Nmax; n++) {
		temp = result;
		result = result - _f(result) * (result - before) / (_f(result) - _f(before));

		if (result < DELTA)
			break;
		difference = temp - result;
		if (fabs(difference) < EPSILON)
			break;

		before = temp;
		fprintf(fp, "%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
		printf("%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
	}
	fprintf(fp, "\n");
	printf("\n");
}
