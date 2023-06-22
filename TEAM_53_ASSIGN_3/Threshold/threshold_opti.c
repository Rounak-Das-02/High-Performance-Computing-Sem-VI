#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    int n = atoi(argv[1]);

    freopen(argv[2], "r", stdin);
    freopen(argv[3], "w", stdout);

    int M[n][n];

    int *pixel_count = (int *)malloc(sizeof(int) * 301);

    float p = 0.1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &M[i][j]);
            // pixel_count[M[i][j]]++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pixel_count[M[i][j]]++;
        }
    }

    gettimeofday(&tv1, &tz);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int count = 0;
            for (int k = 0; k < M[i][j]; k++)
            {
                count += pixel_count[k];
            }

            if ((p * n * n) < count)
            {
                printf("1 ");
            }
            else
                printf("0 ");
        }
        printf("\n");
    }

    // freopen(stdout, "w", stdout);

    gettimeofday(&tv2, &tz);
    elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("%f\t", elapsed);

    return 0;
}