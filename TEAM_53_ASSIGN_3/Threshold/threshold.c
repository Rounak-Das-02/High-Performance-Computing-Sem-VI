#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

int main(int argc, char *argv[])
{

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    int n = atoi(argv[1]);

    freopen(argv[2], "r", stdin);
    freopen(argv[3], "w", stdout);

    int *M[n];
    for (int i = 0; i < n; i++)
        M[i] = (int *)malloc(n * sizeof(int));

    // int B[n][n];
    float p = 0.1;

    // printf("DEBUG");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &M[i][j]);
        }
    }

    omp_set_num_threads(8);

    gettimeofday(&tv1, &tz);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int count = 0;

#pragma omp parallel for reduction(+ \
                                   : count)
            for (int k = 0; k < n; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    if (M[k][l] < M[i][j])
                    {
                        count++;
                    }
                }
            }

            if ((count) > n * n * p)
            {
                // B[i][j] = 1;
                printf("1 ");
            }
            else
            {
                // B[i][j] = 0;
                printf("0 ");
            }
        }
        printf("\n");
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("%f\t", elapsed);

    return 0;
}