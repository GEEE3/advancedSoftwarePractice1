#include "my_solver.h"

void program2_1() {
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/

	int num, i;
	double h, distance, length, sum = 0, temp;
	double** sampling;
	double* integral_table;

	fscanf(fp_r, "%d %lf", &num, &distance);
	sampling = (double**)malloc(sizeof(double*) * num);

	for (i = 0; i < num; i++)
		sampling[i] = (double*)malloc(sizeof(double) * 2);
	for (i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &sampling[i][0], &sampling[i][1]);

	temp = sampling[0][0];
	h = sampling[num - 1][0] - temp;
	length = double(1 / h);

	for (i = 0; i < num; i++) {
		sampling[i][0] = (sampling[i][0] - temp) * length;
	}

	integral_table = (double*)malloc(sizeof(double) * (num - 1));
	for (i = 0; i < num - 1; i++) {
		integral_table[i] = fabs(sampling[i + 1][0] - sampling[i][0]) * (sampling[i + 1][1] + sampling[i][1]) / 2;
		sum += integral_table[i];
	}
	for (i = 0; i < num - 1; i++) {
		integral_table[i] = integral_table[i] / sum;
	}

	fprintf(fp_w, "%d %lf\n", num, distance * length);

	for (i = 0; i < num; i++) {
		sampling[i][1] = sampling[i][1] / sum;
		fprintf(fp_w, "%lf %lf\n", sampling[i][0], sampling[i][1]);
	}

	printf("*** Integrating the pdf from 0.0 to 1.0 = %.6lf\n", calculate_integral(sampling, integral_table, num, 1) - calculate_integral(sampling, integral_table, num, 0));
	printf("*** Integrating the pdf from 0.0 to 0.25 = %.6lf\n", calculate_integral(sampling, integral_table, num, 0.25) - calculate_integral(sampling, integral_table, num, 0));
	printf("*** Integrating the pdf from 0.25 to 0.5 = %.6lf\n", calculate_integral(sampling, integral_table, num, 0.5) - calculate_integral(sampling, integral_table, num, 0.25));
	printf("*** Integrating the pdf from 0.5 to 0.75 = %.6lf\n", calculate_integral(sampling, integral_table, num, 0.75) - calculate_integral(sampling, integral_table, num, 0.5));
	printf("*** Integrating the pdf from 0.75 to 1.0 = %.6lf\n", calculate_integral(sampling, integral_table, num, 1) - calculate_integral(sampling, integral_table, num, 0.75));

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}

double calculate_integral(double** sampling, double* integral_table, int num, double x) {
	double sum = 0;
	int i;

	if (x == 0)
		return 0;

	for (i = 0; i < num; i++) {
		if (sampling[i][0] > x)
			break;
		sum += integral_table[i];
	}
	
	sum -= integral_table[i - 2];
	return sum;
}