#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ANSI_RED "\x1b[31m" 
#define ANSI_GREEN "\x1b[32m" 
#define ANSI_RESET "\x1b[0m" 

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
    double eps=1e-6;
    double r1=0.56389552425993647949;
    double r2=-0.45121875216658734957;
    double r3=-2.52222342435525457678;
    double i1=9.41010640333361;
    double i2=15.5085199666079;
    double i3=1.33333333333333;
    printf("Epsilon: %lf\n\n", eps);
    printf("Analytically calculated roots: %lf, %lf, %lf\n", r1, r2, r3);
    printf("Testing root function...\n");
    double x1=root(f1, f2, -3, 2, eps, 0);
    double x2=root(f2, f3, -3, 2, eps, 0);
    double x3=root(f1, f3, -3, 2, eps, 0);
    printf("Roots: %lf %lf %lf\n", x1, x2, x3);
    printf("Mistakes: %lf %lf %lf\n", fabs(x1-r1), fabs(x2-r2), fabs(x3-r3));
    if (fabs(x1-r1)<eps && fabs(x2-r2)<eps && fabs(x3-r3)<eps) {
        printf(ANSI_GREEN "Root function test passed\n\n" ANSI_RESET);
    } else {
        printf(ANSI_RED "Root function test failed\n\n" ANSI_RESET);
    }

    printf("Analytically calculated integrals from -2 to 2: %lf, %lf, %lf\n", i1, i2, i3);
    printf("Testing integral function...\n");
    x1=integral(f1, -2, 2, 1e-6);
    x2=integral(f2, -2, 2, 1e-6);
    x3=integral(f3, -2, 2, 1e-6);
    printf("Integrals of functions from -2 to 2: %lf %lf %lf\n", x1, x2, x3);
    printf("Mistakes: %lf %lf %lf\n", fabs(x1-i1), fabs(x2-i2), fabs(x3-i3));
    if (fabs(x1-i1)<eps && fabs(x2-i2)<eps && fabs(x3-i3)<eps) {
        printf(ANSI_GREEN "Integral function test passed\n\n" ANSI_RESET);
    } else {
        printf(ANSI_GREEN "Integral function test failed\n\n" ANSI_RESET);
    }
    return 0;
}