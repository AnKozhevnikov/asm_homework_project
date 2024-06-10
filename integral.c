#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>

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
extern double root(afunc *f, afunc *g, double a, double b, double eps1, int *counter);
extern double integral(afunc *f, double a, double b, double eps2);
double solve(afunc *f1, afunc *f2, afunc *f3, double eps1, double eps2);
int compare(const void *a, const void *b);



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
   if (argc == 1) {
      double ans = solve(f1, f2, f3, eps1, eps2);
      printf("Area: %lf\n", ans);
   }
   else {
      int c;
      while (1) {
         int option_index = 0;
         static struct option long_options[] = 
         {
            {"help", no_argument, 0, 'h'},
            {"root", no_argument, 0, 'r'},
            {"iterations", no_argument, 0, 'i'},
            {"test-root", required_argument, 0,  'R'},
            {"test-integral", required_argument, 0, 'I'},
            {0, 0, 0, 0}
         };
         c = getopt_long(argc, argv, "-:hriR:I:", long_options, &option_index);

         if (c==-1) break;

         switch (c) {
            case 'h':
               printf("Options:\n");
               printf(" --help, -h:                print this help\n");
               printf(" --root, -r:                print the roots of the functions\n");
               printf(" --iterations, -i:          print the number of iterations\n");
               printf(" --test-root, -R <arg>:     test the root function with argument like F1:F2:A:B:E:R\n");
               printf(" --test-integral, -I <arg>: test the integral function with argument like F:A:B:E:R\n");
               printf("Running with no options will print the area\n");
               break;
            case 'r':
               printf("Roots:\n");
               printf("f1 and f2: %lf\n", root(f1, f2, 0.01, 10, eps1, 0));
               printf("f2 and f3: %lf\n", root(f2, f3, 0.01, 10, eps1, 0));
               printf("f1 and f3: %lf\n", root(f1, f3, 0.01, 10, eps1, 0));
               break;
            case 'i':
               int iter1 = 0;
               int iter2 = 0;
               int iter3 = 0;
               root(f1, f2, 0.01, 10, eps1, &iter1);
               root(f2, f3, 0.01, 10, eps1, &iter2);
               root(f1, f3, 0.01, 10, eps1, &iter3);
               printf("Iterations:\n");
               printf("f1 and f2: %d\n", iter1);
               printf("f2 and f3: %d\n", iter2);
               printf("f1 and f3: %d\n", iter3);
               break;
            case 'R':
               //TODO: finish this
               break;
            case 'I':
               //TODO: finish this
               break;
            case '?':
               printf("unknown option %c\n", optopt);
               break;
            case 1:
               printf("unknown argument: %s\n", optarg);
               break;
            case ':':
               printf("option %c needs a value\n", optopt);
               break;
            default:
               printf("?? getopt returned character code 0%o ??\n", c);
               break;
         }
      }
   }

   return 0;
}
