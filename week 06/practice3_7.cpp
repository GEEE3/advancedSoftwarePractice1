#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_7(int* n, double* x, double* fvec, int* iflag) {
	/********************************/

	fvec[0] = 2.0 * x[0] * x[0] * x[0] - 12.0 * x[0] - x[1] - 1.0;
	fvec[1] = 3.0 * x[1] * x[1] - 6.0 * x[1] - x[0] - 3.0;

	/********************************/
}

void practice3_7(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/

	for (double op = -4.0; op < 4.0; op = op + 0.5) {
		for (double po = -5.0; po < 5.0; po = po + 0.5) {
			x[0] = op; x[1] = 5.0;
			hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);

			fprintf(fp_w, "info : %d\n", info);

			for (int i = 0; i < 2; i++)
				fprintf(fp_w, "x%d = %10f  fx= %10f\n", i + 1, x[i], fvec[i]);
		}
	}

	/********************************/

	fclose(fp_w);
}