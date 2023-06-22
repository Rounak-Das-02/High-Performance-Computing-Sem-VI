#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{

	freopen(argv[5], "a", stdout);

	int order = atoi(argv[1]);		   // 512, 1024, 2048
	int n = atoi(argv[2]);			   // 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
	int no_of_threads = atoi(argv[3]); // 1, 2, 4, 6, 8, 10, 12, 14, 16

	int block_size = atoi(argv[4]);

	struct timeval tv1,
		tv2;
	struct timezone tz;
	double elapsed;

	int maxThreads = omp_get_max_threads(); // Getting the maximum number of threads

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

	omp_set_num_threads(no_of_threads);
	int i = 0, j = 0;

	gettimeofday(&tv1, &tz);

#pragma omp parallel for
	for (i = 0; i < n; i++)
	{
		for (int jj = 0; jj < order; jj = jj + block_size)
		{
			for (int kk = 0; kk < order; kk = kk + block_size)
			{
				for (i = 0; i < order; i++)
				{
					for (j = jj; j < ((jj + block_size) > order ? order : (jj + block_size)); j++)
					{
						float temp = 0.0;
						for (int k = kk; k < ((kk + block_size) > order ? order : (kk + block_size)); k++)
						{
							temp += A[i][k] * B[j][k];
						}
						result[i][j] += temp;
					}
				}
			}
		}
	}

	gettimeofday(&tv2, &tz);
	elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
	printf("%f\t", elapsed);

	return 0;
}