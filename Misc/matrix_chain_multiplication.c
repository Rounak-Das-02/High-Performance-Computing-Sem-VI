#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int MAX = 99999999;

int min_mult(int p[], int n)
{
    int m[MAX][MAX], s[MAX][MAX], i, j, k, l, q;

#pragma omp parallel shared(m, s) private(i, j, k, l, q)
    {
#pragma omp for schedule(dynamic)
        for (i = 1; i < n; i++)
        {
            m[i][i] = 0;
        }

        for (l = 2; l < n; l++)
        {
#pragma omp for schedule(dynamic)
            for (i = 1; i < n - l + 1; i++)
            {
                j = i + l - 1;
                m[i][j] = 1000000000;

#pragma omp for schedule(dynamic)
                for (k = i; k <= j - 1; k++)
                {
                    q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (q < m[i][j])
                    {
                        m[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
    }

    return m[1][n - 1];
}

int main()
{
    int p[MAX], n, i;

    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions of the matrices: ");
    for (i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    printf("Minimum number of multiplications: %d\n", min_mult(p, n + 1));

    return 0;
}
