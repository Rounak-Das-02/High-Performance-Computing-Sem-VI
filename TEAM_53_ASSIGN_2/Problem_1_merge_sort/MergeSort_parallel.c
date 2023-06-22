#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <sys/time.h>

#define MX_SIZE 40000000

void MSort(int *array, int *arr2, int size);
void Merging(int *arr, int *arr2, int start, int mid, int end);
void inser_Sort(int *arr, int start, int end);

void MSort(int *arr, int *arr2, int size)
{
    int i, stride = 100;
    int mxlimit = size - stride;
#pragma omp parallel for
    for (i = 0; i < mxlimit; i = i + stride)
    {
        inser_Sort(arr, i, i + stride - 1);
    }
    // for(i=0;i<mxlimit;i=i+stride);//
    i = (int)(mxlimit / stride) * stride;
    if (i < size)
    {
        inser_Sort(arr, i, size - 1);
    }

    mxlimit = size - (2 * stride);
    while (stride < size)
    {
#pragma omp parallel for
        for (i = 0; i < mxlimit; i = i + 2 * stride)
        {
            Merging(arr, arr2, i, i + stride, i + 2 * stride - 1);
        }
        // for(i=0;i<mxlimit;i=i+2*stride);//
        i = (int)(mxlimit / (2 * stride)) * (2 * stride);
        if (i + stride < size)
        {
            Merging(arr, arr2, i, i + stride, size - 1);
        }
        stride = 2 * stride;
        mxlimit = size - (2 * stride);
    }
}

void inser_Sort(int *arr, int start, int end)
{
    for (int pos = start + 1; pos <= end; pos++)
    {
        int temp = arr[pos];
        while (pos > start && arr[pos - 1] > temp)
        {
            arr[pos] = arr[pos - 1];
            pos = pos - 1;
        }
        if (pos >= start)
        {
            arr[pos] = temp;
        }
    }
}

void Merging(int *dest, int *src, int start, int mid, int end)
{
    int i = start;   // start index of the first array
    int j = mid + 1; // start index of the second array
    int k = 0;       // start index of the destination array

    // Merge the two arrays into the destination array
    while (i <= mid && j <= end)
    {
        if (src[i] <= src[j])
        {
            dest[k] = src[i];
            i++;
        }
        else
        {
            dest[k] = src[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from the first array to the destination array
    while (i <= mid)
    {
        dest[k] = src[i];
        i++;
        k++;
    }

    // Copy any remaining elements from the second array to the destination array
    while (j <= end)
    {
        dest[k] = src[j];
        j++;
        k++;
    }

    // Copy the merged elements from the destination array back to the source array
    for (i = start, k = 0; i <= end; i++, k++)
    {
        src[i] = dest[k];
    }
}
int main()
{
    struct timeval time1, time2;
    struct timezone timez;
    double elapsed;
    int threads;
    scanf("%d", &threads);
    omp_set_num_threads(threads);
    int i;
    int *arr, *arr2;
    arr = (int *)malloc(MX_SIZE * sizeof(int));
    arr2 = (int *)malloc(MX_SIZE * sizeof(int));
    srand(time(NULL));
    // generate random numbers for int type array
    for (i = 0; i < MX_SIZE; i++)
    {
        arr[i] = rand();
    }
    // sort int type array
    gettimeofday(&time1, &timez);

    MSort(arr, arr2, MX_SIZE);
    gettimeofday(&time2, &timez);

    elapsed = (double)(time2.tv_sec - time1.tv_sec) + (double)(time2.tv_usec - time1.tv_usec) * 1.e-6;
    printf("elapsed time = %lf seconds.\n", elapsed);
}