#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_matrix.h"
// A B
int naive(int **A, int **B, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += A[i][k] * B[k][j];
            }
        }
    }
    return sum;
}

int main()
{
    char *name1 = "a50.mat";
    char *name2 = "b50.mat";

    int **A, **B;
    int n = 50;
    read_matrix_from_csv(name1, &A, &n);
    read_matrix_from_csv(name2, &B, &n);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int sum = naive(A, B, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Naive: %d\n", sum);
    printf("Time: %f\n", cpu_time_used);
}