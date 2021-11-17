#include "my_solver.h"

void practice3_2() {
	char readfile[256];
	char writefile[256];
	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	for (int t = 1; t <= 6; t++) {
		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);

		/********************************/

		int j, x;

		for (i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &poly[i]);
		}

		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);

		fprintf(fp_w, "zeror : \n");
		for (i = 0; i < DEGREE; i++) {
			fprintf(fp_w, "%.15lf ", zeror[i]);
		}
		fprintf(fp_w, "\n");

		fprintf(fp_w, "zeroi : \n");
		for (i = 0; i < DEGREE; i++) {
			fprintf(fp_w, "%.15lf ", zeroi[i]);
		}
		fprintf(fp_w, "\n");

		for (i = 0; i < DEGREE; i++) {
			if (zeroi[i] == 0) {
				x = 0;
				
				for (j = 0; j < DEGREE; j++)
					x += poly[j] * pow(zeror[i], DEGREE - j);
				x += poly[j];
				x = fabs(x);
				fprintf(fp_w, "|f(%.15lf)| = %.15lf \n", zeror[i], x);
			}
		}

		/********************************/

		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}