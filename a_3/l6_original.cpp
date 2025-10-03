#include <cstdlib>

double sqsum (double * __restrict__ a, int n) {
  double s = 0.0;
  for (int i=0; i<n; i++) {
    s += a[i]*a[i];
  }
  return s;
}

double sum;

int main () {
  int n = 8192;
  double *a = (double *)calloc(n, sizeof(double));
  for (int i=0; i<10000; i++) {
    sum = sqsum(a, n);
  }
  return 0;
}