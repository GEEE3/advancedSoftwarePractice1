#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/

void program1_3(FILE *fp)
{
	double temp;
	double difference, middle, result, before, left, right;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Enter Your Initial Guess: ");
	scanf("%lf %lf", &left, &right);
	if (_f(left) * _f(right) >= 0) {
		printf("input value error\n\n");
		return;
	}

	if (left > right) {
		temp = left;
		left = right;
		right = temp;
	}

	middle = (left + right) / 2;
	before = _f(left);
	fprintf(fp, " n             xn1                  |f(xn1)|\n");
	printf(" n             xn1                  |f(xn1)|\n");

	for (n = 0; n < Nmax; n++) {
		if (_f(left) * _f(middle) < 0) {
			right = middle;
			middle = (left + right) / 2;
			result = middle;
		}
		else {
			left = middle;
			middle = (left + right) / 2;
			result = middle;
		}

		if (result < DELTA)
			break;
		difference = before - result;
		if (fabs(difference) < EPSILON)
			break;

		before = result;
		fprintf(fp, "%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
		printf("%03d   %.15e   %.15e\n", n, result, fabs(_f(result)));
	}
	fprintf(fp, "\n");
	printf("\n");
}
