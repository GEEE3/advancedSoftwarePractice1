#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);

#define DELTA 0.000001
#define Nmax 500
#define EPSILON 0.000001

void program2_1();
void program2_2();

double calculate_integral(double** sampling, double* integral_table, int num, double x);
double bisection(double** pdf, int num, double U);
double secant(double** pdf, int num, double U);
double calculate_cdf(double** pdf, int num, double x, double U);

// HOMEWORK
void program2_2_a(void);
void program2_2_b(void);
void program2_3(void);

#endif  // __MY_SOLVER_H__