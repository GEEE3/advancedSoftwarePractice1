#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void program2_2() {
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int num, i;
	double length, U, max = 32767;
	double** pdf;

	fscanf(fp_r, "%d %lf", &num, &length);
	pdf = (double**)malloc(sizeof(double*) * num);
	
	for (i = 0; i < num; i++)
		pdf[i] = (double*)malloc(sizeof(double) * 2);

	for (i = 0; i < num; i++) {
		fscanf(fp_r, "%lf %lf", &pdf[i][0], &pdf[i][1]);
	}

	srand(time(NULL));
	for (i = 0; i < 50; i++) {
		U = rand() / max;
		fprintf(fp_w, "%.15lf\n", bisection(pdf, num, U));
	}

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}

double bisection(double** pdf, int num, double U) {
	double difference, middle, result, beforeResult;
	double left = 0.005, right = 0.995;
	int n = 0;

	middle = (left + right) / 2;
	beforeResult = left;

	for (n = 0; n < Nmax; n++) {
		if (calculate_cdf(pdf, num, left, U) * calculate_cdf(pdf, num, middle, U) < 0) {
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
		difference = calculate_cdf(pdf, num, beforeResult, U) - calculate_cdf(pdf, num, result, U);
		if (fabs(difference) < EPSILON) {
			break;
		}

		beforeResult = result;
	}
	return fabs(result);
}

double secant(double** pdf, int num, double U) {
	double temp, difference, result, before, left = 0.05, right = 0.95;
	int n = 0;

	before = left;
	result = right;

	for (n = 0; n < Nmax; n++) {
		if (result < 0.005)
			result = 0.005;
		if (before < 0.005)
			before = 0.005;
		if (result > 0.995)
			result = 0.995;
		if (before > 0.995)
			before = 0.995;

		temp = result;
		result = result - calculate_cdf(pdf, num, result, U) * (result - before) / (calculate_cdf(pdf, num, result, U) - calculate_cdf(pdf, num, before, U));

		if (result < DELTA)
			break;
		difference = temp - result;
		if (fabs(difference) < EPSILON)
			break;

		before = temp;
	}
	return fabs(result);
}

double calculate_cdf(double** pdf, int num, double x, double U) {
	double sum = 0;
	double* integral_table;
	int i;

	if (x == 0)
		return 0;

	integral_table = (double*)malloc(sizeof(double) * (num - 1));
	for (i = 0; i < num - 1; i++)
		integral_table[i] = fabs(pdf[i + 1][0] - pdf[i][0]) * (pdf[i + 1][1] + pdf[i][1]) / 2;

	for (i = 0; i < num; i++) {
		sum += integral_table[i];
		if (pdf[i][0] > x)
			break;
	}
	i -= 1;
	sum += (pdf[i][1] + ((pdf[i + 1][1] - pdf[i][1]) / (pdf[i + 1][0] - pdf[i][0])) * (x - pdf[i][0]) / 2) * (x - pdf[i][0]);
	return sum - U;
}