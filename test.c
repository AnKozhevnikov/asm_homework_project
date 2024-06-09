#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double afunc(double);

double f1(double x);
double f2(double x);
double f3(double x);
extern double root(afunc *f, afunc *g, double a, double b, double eps1, int *counter);
extern double integral(afunc *f, double a, double b, double eps2);

double f1(double x) {
    return pow(2,x)+1;
}

double f2(double x) {
    return pow(5,x);
}

double f3(double x) {
    return (1-x)/3;
}

int main(void) {
    printf("Testing root function...\n");
    double x1=root(f1, f2, -3, 2, 1e-6, 0);
    double x2=root(f2, f3, -3, 2, 1e-6, 0);
    double x3=root(f1, f3, -3, 2, 1e-6, 0);
    printf("Roots: %lf %lf %lf\n", x1, x2, x3);

    printf("Testing integral function...\n");
    x1=integral(f1, -2, 2, 1e-6);
    x2=integral(f2, -2, 2, 1e-6);
    x3=integral(f3, -2, 2, 1e-6);
    printf("Integrals of functions from -2 to 2: %lf %lf %lf\n", x1, x2, x3);
    return 0;
}