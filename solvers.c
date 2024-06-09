#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double afunc(double);

double root(afunc *f, afunc *g, double a, double b, double eps, int *counter);
double integral(afunc *f, double a, double b, double eps);

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