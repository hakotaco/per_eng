#include <iostream>
#include <cstdlib>
#include <ctime>
#include <arm_neon.h>

__attribute__((used)) void matVecMul1(double *A, double *x, double *y, int N) {
  for (int i=0; i < N; i++) {
    double sum = 0;
    for (int j=0; j < N; j++) {
      sum = sum + A[i * N + j] * x[j];
    }
    y[i] = sum;
  }
}

__attribute__((used)) void matVecMul2(double *A, double *x, double *y, int N) {
  for (int i=0; i < N; i++) {
    double sum = 0;
    for (int j=0; j < N; j+=4) {
      sum = sum + A[i * N + j] * x[j];
      sum = sum + A[i * N + j+1] * x[j+1];
      sum = sum + A[i * N + j+2] * x[j+2];
      sum = sum + A[i * N + j+3] * x[j+3];
    }
    y[i] = sum;
  }
}

__attribute__((used)) void matVecMul3(double *A, double *x, double *y, int N) {
  for (int i=0; i < N; i++) {
    float64x2_t sum = vdupq_n_f64(0);
    for (int j=0; j < N; j+=2) {
      float64x2_t AVec = vld1q_f64(&A[i * N + j]);
      float64x2_t xVec = vld1q_f64(&x[j]);
      sum = vfmaq_f64(sum, AVec, xVec);
    }
    y[i] = vaddvq_f64(sum);
  }
}

int main() {
  int N = 1024;

  double *A = (double*)aligned_alloc(16, N * N * sizeof(double));
  double *x = (double*)aligned_alloc(16, N * sizeof(double));
  double *y = (double*)aligned_alloc(16, N * sizeof(double));
  
  srand(time(NULL));
  for (int i = 0; i < N * N; i++) {
    A[i] = (double)rand() / RAND_MAX;
  }
  for (int i = 0; i < N; i++) {
    x[i] = (double)rand() / RAND_MAX;
    y[i] = 0.0;
  }
  
  //matVecMul1(A, x, y, N);
  //matVecMul2(A, x, y, N);
  matVecMul3(A, x, y, N);
  
  
  free(A);
  free(x);
  free(y);
  
  return 0;
}