#include "my_solver.h"

// HOMEWORK
void program2_3() {
	double length, a, b, error, error_rate, max = 32767;
	int i, num;
	double** pdf;
	double pdf_sum[10];
	int result_a[10] = { 0, };
	int result_b[10] = { 0, };

	FILE* fp_r = fopen("pdf_table.txt", "r");
	FILE* fp_w = fopen("histogram.txt", "w");

	fscanf(fp_r, "%d %lf", &num, &length);
	pdf = (double**)malloc(sizeof(double*) * num);
	for (i = 0; i < num; i++)
		pdf[i] = (double*)malloc(sizeof(double) * 2);
	for (i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &pdf[i][0], &pdf[i][1]);


	pdf_sum[0] = calculate_cdf(pdf, num, 0.1, 0);
	for (i = 1; i < 9; i++)
		pdf_sum[i] = calculate_cdf(pdf, num, float(0.1 * (i + 1)), 0) - calculate_cdf(pdf, num, 0.1 * (i), 0);
	pdf_sum[9] = 1 - calculate_cdf(pdf, num, 0.9, 0);

	program2_2_a();
	program2_2_b();

	FILE* fp_a = fopen("random_event_table_a.txt", "r");
	FILE* fp_b = fopen("random_event_table_b.txt", "r");

	for (i = 0; i < 10000; i++) {
		fscanf(fp_a, "%lf", &a);
		fscanf(fp_b, "%lf", &b);
		result_a[int(a * 10)]++;
		result_b[int(b * 10)]++;
	}

	fprintf(fp_w, "interval:        0.0~0.1 0.1~0.2 0.2~0.3 0.3~0.4 0.4~0.5 0.5~0.6 0.6~0.7 0.7~0.8 0.8~0.9 0.9~1.0\n");

	fprintf(fp_w, "program2_2_a: ");
	for (i = 0; i < 10; i++) {
		fprintf(fp_w, "%8d", result_a[i]);
	}
	fprintf(fp_w, "\n");

	fprintf(fp_w, "program2_2_b: ");
	for (i = 0; i < 10; i++) {
		fprintf(fp_w, "%8d", result_b[i]);
	}
	fprintf(fp_w, "\n");

	fprintf(fp_w, "probability:     ");
	for (i = 0; i < 10; i++) {
		fprintf(fp_w, "%.4lf  ", pdf_sum[i]);
	}
	fprintf(fp_w, "\n");

	fprintf(fp_w, "error rate a:   ");
	for (i = 0; i < 10; i++) {
		error = fabs(result_a[i] - (pdf_sum[i] * 10000));
		error_rate = error / (pdf_sum[i] * 10000) * 100;
		fprintf(fp_w, "%6.3lf%% ", error_rate);
	}
	fprintf(fp_w, "\n");

	fprintf(fp_w, "error rate b:   ");
	for (i = 0; i < 10; i++) {
		error = fabs(result_b[i] - (pdf_sum[i] * 10000));
		error_rate = error / (pdf_sum[i] * 10000) * 100;
		fprintf(fp_w, "%6.3lf%% ", error_rate);
	}
	fprintf(fp_w, "\n");

	if (fp_r != NULL) fclose(fp_r);
	if (fp_a != NULL) fclose(fp_a);
	if (fp_b != NULL) fclose(fp_b);
}

// HOMEWORK
void program2_2_a() {
	__int64 start, freq, end;
	float resultTime = 0;
	FILE* fp_r, * fp_w;
	CHECK_TIME_START;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table_a.txt", "w");

	int num, i;
	double length, U, max = 32767;
	double** pdf;

	fscanf(fp_r, "%d %lf", &num, &length);
	pdf = (double**)malloc(sizeof(double*) * num);

	for (i = 0; i < num; i++)
		pdf[i] = (double*)malloc(sizeof(double) * 2);
	for (i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &pdf[i][0], &pdf[i][1]);

	srand(time(NULL));

	for (i = 0; i < 10000; i++) {
		U = rand() / max;
		fprintf(fp_w, "%.15lf\n", bisection(pdf, num, U));
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);
	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b() {
	__int64 start, freq, end;
	float resultTime = 0;
	FILE* fp_r, * fp_w;
	CHECK_TIME_START;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table_b.txt", "w");

	int num, i;
	double length, U, max = 32767;
	double** pdf;

	fscanf(fp_r, "%d %lf", &num, &length);
	pdf = (double**)malloc(sizeof(double*) * num);

	for (i = 0; i < num; i++)
		pdf[i] = (double*)malloc(sizeof(double) * 2);
	for (i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &pdf[i][0], &pdf[i][1]);

	srand(time(NULL));

	for (i = 0; i < 10000; i++) {
		U = rand() / max;
		fprintf(fp_w, "%.15lf\n", secant(pdf, num, U));
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);
	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}