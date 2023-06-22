
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 10

int main(int argc, char **argv)
{
    int p[N + 1] = {0}; // Dimensions of the matrices
    int i, j, k, t;
    double start_time, end_time;
    double *A[N];                         // Matrices A1, A2, ..., An
    double *B;                            // Resulting matrix
    int nthreads = omp_get_max_threads(); // Number of threads

    // Initialize dimensions of the matrices
    for (i = 0; i <= N; i++)
    {
        p[i] = 4096 + i * 4096;
    }

    // Allocate memory for matrices A1, A2, ..., An
    for (i = 0; i < N; i++)
    {
        A[i] = (double *)malloc(p[i] * p[i + 1] * sizeof(double));
        for (j = 0; j < p[i]; j++)
        {
            for (k = 0; k < p[i + 1]; k++)
            {
                A[i][j * p[i + 1] + k] = rand() / (double)RAND_MAX; // Initialize matrix elements
            }
        }
    }

    omp_set_num_threads(1);

    // Allocate memory for resulting matrix
    B = (double *)malloc(p[0] * p[N] * sizeof(double));

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    gettimeofday(&tv1, &tz);

// Parallelize matrix multiplication
#pragma omp parallel for private(i, j, k, t)
    for (t = 0; t < p[0] * p[N]; t++)
    {
        i = t / p[N];
        j = t % p[N];
        B[t] = A[0][i * p[1]] * A[1][0 * p[2] + j];
        for (k = 1; k < N - 1; k++)
        {
            B[t] *= A[k][i * p[k + 1]] * A[k + 1][0 * p[k + 1] + j];
        }
        B[t] *= A[N - 1][i * p[N - 1] + j];
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("%f\t", elapsed);

    // Free memory
    for (i = 0; i < N; i++)
    {
        free(A[i]);
    }
    free(B);

    return 0;
}