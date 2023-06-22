#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    freopen(argv[4], "a", stdout);

    int order = atoi(argv[1]);         // 512, 1024, 2048
    int n = atoi(argv[2]);             // 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
    int no_of_threads = atoi(argv[3]); // 1, 2, 4, 6, 8, 10, 12, 14, 16

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    int maxThreads = omp_get_max_threads(); // Getting the maximum number of threads
    // printf("Maximum Number of Threads Available : %d\n", maxThreads);

    double *A[order]; // Matrix
    for (int i = 0; i < order; i++)
        A[i] = (double *)malloc(order * sizeof(double));

    double *B[order]; // Copy of matrix A
    for (int i = 0; i < order; i++)
        B[i] = (double *)malloc(order * sizeof(double));

    double *result[order]; // Temporary matrix to store values
    for (int i = 0; i < order; i++)
        result[i] = (double *)malloc(order * sizeof(double));

    // initialise
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            A[i][j] = ((double)rand()) / RAND_MAX; // Numbers between 0 and 1
            B[i][j] = A[i][j];
            result[i][j] = 0;
        }
    }

    // THIS IS SEQUENTIAL MATRIX MULTIPLICATION ...
    // gettimeofday(&tv1, &tz);

    // for (int z = 1; z <= n - 1; z++)
    // {
    //     for (int i = 0; i < order; i++)
    //     {
    //         for (int j = 0; j < order; j++)
    //         {
    //             for (int k = 0; k < order; k++)
    //             {
    //                 result[i][j] += A[i][k] * B[k][j];
    //             }
    //         }
    //     }

    //     for (int i = 0; i < order; i++)
    //     {
    //         for (int j = 0; j < order; j++)
    //         {
    //             A[i][j] = result[i][j];
    //             result[i][j] = 0;
    //         }
    //     }
    // }

    // gettimeofday(&tv2, &tz);
    // elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    // printf("elapsed time = %4.2lf seconds.\n", elapsed);

    // initialise
    // for (int i = 0; i < order; i++)
    // {
    //     for (int j = 0; j < order; j++)
    //     {
    //         A[i][j] = B[i][j];
    //         result[i][j] = 0;
    //     }
    // }

    omp_set_num_threads(no_of_threads);
    int i = 0, j = 0;

    gettimeofday(&tv1, &tz);

    for (int z = 1; z <= n - 1; z++)
    {
#pragma omp parallel for collapse(2)
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                for (int k = 0; k < order; k++)
                {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }

#pragma omp parallel for collapse(2)
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                A[i][j] = result[i][j];
                result[i][j] = 0;
            }
        }
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("%f\t", elapsed);

    return 0;
}