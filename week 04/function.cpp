#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return pow(x, 2) - 4*x + 4 - log(x);
}

double _fp1(double x) {
	return 2*x - 4 - 1/x;
}

double _f2(double x) {
	return x + 1 - (2*sin(M_PI*x));
}

double _fp2(double x) {
	return 1 - (M_PI*2*cos(M_PI*x));
}

double _f3(double x) {
	return pow(x, 4) - 11.0*pow(x, 3) + 42.35*pow(x, 2) - 66.55*x + 35.1384;
}

double _fp3(double x) {
	return 4*pow(x, 3) - 33.0*pow(x, 2) + 84.70*x - 66.55;
}

double _f_sqrt(double x) {
	return x*x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0*x;
}

double _f_vehicle(double x) {
	double A = 17.7437461631;
	double B = 87.2132987113;
	double C = 9.65670874875;
	double E = 47.4642399035;
	double X = x * M_PI/180;
	return A * sin(X)*cos(X) + B*sin(X)*sin(X) - C*cos(X) - E*sin(X);
}

double _fp_vehicle(double x) {
	double A = 17.7437461631;
	double B = 87.2132987113;
	double C = 9.65670874875;
	double E = 47.4642399035;
	double X = x * M_PI/180;
	return A * cos(X)*cos(X) - A*sin(X)*sin(X) + 2*B*sin(X)*cos(X) + C*sin(X) - E*cos(X);
}

double _f_comp(double x) {
	return log(x) - 1;
}

double _fp_comp(double x) {
	return 1/x;
}
