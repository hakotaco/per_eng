/* matvec_blocked.c
    Simple cache-blocked matvec that accepts N and B as command-line args.
    Allocates arrays on the heap (safe for large N).
*/
#include <stdio.h>
#include <stdlib.h>

void matVecMul_blocked(double *A, double *x, double *y, int N, int B) {
     int nb = N / B;
     for (int ib = 0; ib < nb; ib ++) {
          for (int i = 0; i < B; i++)
                y[ib*B+i] = 0.0;
          for (int jb = 0; jb < nb; jb ++)
                for (int i = 0; i < B; i++)
                     for (int j = 0; j < B; j++) {
                          int ii = ib*B + i;
                          int jj = jb*B + j;
                          y[ii] += A[ii*N + jj] * x[jj];
                     }
     }
}

int main(int argc, char **argv) {
     if (argc < 3) { fprintf(stderr, "Usage: %s N B\n", argv[0]); return 1; }
     int N = atoi(argv[1]);
     int B = atoi(argv[2]);

     double *x = calloc(N, sizeof(double));
     double *y = calloc(N, sizeof(double));
     double *A = calloc(N*N, sizeof(double)); /* row-major: A[i*N + j] */

     if (!x || !y || !A) { fprintf(stderr, "alloc failed\n"); return 1; }

     matVecMul_blocked(A, x, y, N, B);

     /* print a checksum so compiler doesn't optimize the whole thing away */
     double s = 0.0;
     for (int i=0;i<N;i++) s += y[i];
     printf("checksum: %.6e\n", s);

     free(x); free(y); free(A);
     return 0;
}