#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double afunc(double);

const double eps1=1e-6;
const double eps2=1e-6;

struct Point {
   double x;
   afunc *f1;
   afunc *f2;
};

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
double root(afunc *f, afunc *g, double a, double b, double eps1, int *counter);
double integral(afunc *f, double a, double b, double eps2);
double solve(afunc *f1, afunc *f2, afunc *f3, double eps1, double eps2);
int compare(const void *a, const void *b);

double root(afunc *f, afunc *g, double a, double b, double eps, int *counter) {
   if (counter!=NULL) (*counter)++;
   double c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/((f(b)-g(b))-(f(a)-g(a)));
   
   int flag1 = (f(a)-g(a)) < 0;
   int flag2 = (f((a+b)/2)-g((a+b)/2)) < ((f(a)-g(a))+(f(b)-g(b)))/2;

   if (flag1==flag2) {
      if ((f(c)-g(c)) * (f(c+eps)-g(c+eps)) >= 0) {
         return root(f,g,c,b,eps, counter);
      }
      else return c;
   } else {
      if ((f(c)-g(c)) * (f(c-eps)-g(c-eps)) >= 0) {
         return root(f,g,a,c,eps, counter);
      }
      else return c;
   }
}

double integral(afunc *f, double a, double b, double eps) {
   int n = 2;
   double h = (b-a)/n;
   double ilast = 0;
   double i = 0;
   do {
      ilast = i;
      i = 0;

      n *= 2;
      h = (b-a)/n;

      i+=f(a);
      i+=f(b);
      for (int j=1; j<n; j++) {
         i += f(a+j*h)*(j%2==0?2:4);
      }
      i*=h;
      i/=3;
   } while (fabs(i-ilast)/15 > eps);
   return i;
}

int compare(const void *a, const void *b) {
   double x = ((struct Point*)a)->x - ((struct Point*)b)->x;
   if (x < 1e-6) return 0;
   else if (x>0) return 1;
   else return -1;
}

double solve(afunc *f1, afunc *f2, afunc *f3, double eps1, double eps2) {
   double x1 = root(f1, f2, 0.01, 10, eps1, 0);
   double x2 = root(f2, f3, 0.01, 10, eps1, 0);
   double x3 = root(f1, f3, 0.01, 10, eps1, 0);
   struct Point p1={x1, f1, f2};
   struct Point p2={x2, f2, f3};
   struct Point p3={x3, f1, f3};
   struct Point points[3]={p1, p2, p3};
   qsort(points, 3, sizeof(struct Point), compare);

   double area = 0;
   afunc *l1 = points[0].f1;
   afunc *l2 = points[0].f2;
   for (int i=1; i<3; i++) {
      double a = points[i-1].x;
      double b = points[i].x;
      area+=fabs(integral(l1, a, b, eps2)-integral(l2, a, b, eps2));

      if (l1==points[i].f1) {
         l1 = points[i].f2;
      }
      else if (l1==points[i].f2) {
         l1 = points[i].f1;
      }
      else if (l2==points[i].f1) {
         l2 = points[i].f2;
      }
      else if (l2==points[i].f2) {
         l2 = points[i].f1;
      }
   }

   return area;
}

int main(int argc, char* argv[]) {
   double ans = solve(f1, f2, f3, eps1, eps2);
   printf("%lf\n", ans);

   return 0;
}
