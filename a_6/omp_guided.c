#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void mxv(double *restrict y,
         double *restrict a,
         double *restrict x,
         int m, int n)
{
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < m; i++) {
        double temp = 0.0;
        for (int j = 0; j < n; j++)
            temp += a[i * n + j] * x[j];
        y[i] = temp;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "Usage: %s m n\n", argv[0]); return 1; }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    double *x = calloc(n, sizeof(double));
    double *y = calloc(m, sizeof(double));
    double *A = calloc(m*n, sizeof(double)); /* row-major: A[i*n + j] */

    if (!x || !y || !A) { fprintf(stderr, "alloc failed\n"); return 1; }

    for (int iter = 0; iter < 1000; iter++) {
        mxv(y, A, x, m, n);
    }

    /* print a checksum so compiler doesn't optimize the whole thing away */
    double s = 0.0;
    for (int i=0;i<m;i++) s += y[i];
    printf("checksum: %.6e\n", s);

    free(x); free(y); free(A);
    return 0;
}