#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define ALIVE 1
#define DEAD 0

int count_live_neighbors(int r, int c, int row, int col, int **board)
{
    int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++)
    {
        for (j = c - 1; j <= c + 1; j++)
        {
            if ((i == r && j == c) || (i < 0 || j < 0) || (i >= row || j >= col))
            {
                continue;
            }
            if (board[i][j] == 1)
            {
                count++;
            }
        }
    }
    return count;
}

void update_board(int rows, int cols, int **board, int **new_board)
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int live_neighbors = count_live_neighbors(i, j, rows, cols, board);
            if (board[i][j] == 1)
            {
                if (live_neighbors < 2 || live_neighbors > 3)
                {
                    new_board[i][j] = 0;
                }
                else
                {
                    new_board[i][j] = 1;
                }
            }
            else
            { // dead cell
                if (live_neighbors == 3)
                {
                    new_board[i][j] = 1;
                }
                else
                {
                    new_board[i][j] = 0;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{

    freopen(argv[1], "r", stdin);
    freopen(argv[5], "w", stdout);

    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    int steps = atoi(argv[4]);

    int *board[rows];
    for (int i = 0; i < rows; i++)
        board[i] = (int *)malloc(cols * sizeof(int));

    int *new_board[rows];
    for (int i = 0; i < rows; i++)
        new_board[i] = (int *)malloc(cols * sizeof(int));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }

    omp_set_num_threads(16);

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    gettimeofday(&tv1, &tz);

    while (steps--)
    {
        update_board(rows, cols, board, new_board);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                board[i][j] = new_board[i][j];
            }
        }
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("%f\t", elapsed);

    return 0;
}