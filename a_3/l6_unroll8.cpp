#include <cstdlib>

double sqsum (double * __restrict__ a, int n) {
  double s = 0.0;
  int i;
  // Unroll by factor of 8
  for (i = 0; i < n - 7; i += 8) {
    s += a[i]*a[i] + a[i+1]*a[i+1] + a[i+2]*a[i+2] + a[i+3]*a[i+3] + 
         a[i+4]*a[i+4] + a[i+5]*a[i+5] + a[i+6]*a[i+6] + a[i+7]*a[i+7];
  }
  // Handle remaining elements
  for (; i < n; i++) {
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
