#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "read_matrix.h"
#include <time.h>
#include <sys/time.h>
// A B
void naive_mat_mul(int **A, int **B, int **C, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += A[i][j] * B[j][k];
            }
            C[i][k] = sum;
            sum = 0;
        }
    }
}

typedef struct mat_mul_thread_args
{
    int **A;
    int **B;
    int **C;
    int A_row;
    int n;
    int z;
} mat_mul_thread_args;

// Thread function
void *mat_mul_threads_helper(void *args)
{
    mat_mul_thread_args *arg = (mat_mul_thread_args *)args;
    int **A = arg->A;
    int **B = arg->B;
    int **C = arg->C;
    int A_row = arg->A_row;
    int n = arg->n;
    int z = arg->z;
    // printf("Begin work on rows %d\n", A_row);

    if (A_row >= n)
    {
        free(arg);
        return NULL;
    }

    // keep computing rows according initial thread id "A_row", add z to A_row to get next row to compute
    while (A_row < n)
    {
        for (int k = 0; k < n; k++)
        {
            C[A_row][k] = 0;
            for (int j = 0; j < n; j++)
            {
                C[A_row][k] += A[A_row][j] * B[j][k];
            }
        }
        A_row += z;
    }

    free(arg); // Free allocated memory
    return NULL;
}

// Function to create and manage threads
void threads_mat_mul(int **A, int **B, int **C, int n, int z)
{
    pthread_t *threads = malloc(z * sizeof(pthread_t));

    // Spawn threads
    for (int t = 0; t < z; t++)
    {
        mat_mul_thread_args *args = malloc(sizeof(mat_mul_thread_args));
        if (args == NULL)
        {
            perror("Failed to allocate memory");
            exit(1);
        }

        // intialize the struct
        args->A = A;
        args->B = B;
        args->C = C;
        args->A_row = t;
        args->n = n;
        args->z = z;

        // printf("Creating thread %d\n", t);
        if (pthread_create(&threads[t], NULL, mat_mul_threads_helper, args) != 0)
        {
            perror("Failed to create thread");
            free(args);
            exit(1);
        }
    }

    // Join threads
    for (int t = 0; t < z; t++)
    {
        pthread_join(threads[t], NULL);
    }
}

// Transpose the matrix so we can access consecutive elements in row, not column
void transpose_matrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

// The function that each thread is running
void *transpose_threads_multiply_helper(void *args)
{
    mat_mul_thread_args *arg = (mat_mul_thread_args *)args;
    int **A = arg->A;
    int **B = arg->B;
    int **C = arg->C;
    int A_row = arg->A_row; // Start of the range of rows that this thread will calculate
    int n = arg->n;
    int z = arg->z;
    // printf("Begin work on rows %d\n", A_row);

    // If this thread is trying to calculate non-existent row, free args and return null (perform cleanup)
    if (A_row >= n)
    {
        free(arg);
        return NULL;
    }

    // Starting from A_row, solve every zth row
    while (A_row < n)
    {
        for (int k = 0; k < n; k++)
        {
            C[A_row][k] = 0; // Reset C matrix between each trial
            for (int j = 0; j < n; j++)
            {
                C[A_row][k] += A[A_row][j] * B[k][j];
            }
        }
        A_row += z;
    }

    free(arg); // Free allocated memory
    return NULL;
}

// Generates threads and assigns them to calculate for a specific row in A
void transpose_threads_mat_mul(int **A, int **B, int **C, int n, int z)
{
    pthread_t *threads = malloc(z * sizeof(pthread_t));

    // Spawn threads
    for (int t = 0; t < z; t++)
    {
        mat_mul_thread_args *args = malloc(sizeof(mat_mul_thread_args));
        if (args == NULL)
        {
            perror("Failed to allocate memory");
            exit(1);
        }

        args->A = A;
        args->B = B;
        args->C = C;
        args->A_row = t;
        args->n = n;
        args->z = z;

        // printf("Creating thread %d\n", t);
        if (pthread_create(&threads[t], NULL, transpose_threads_multiply_helper, args) != 0)
        {
            perror("Failed to create thread");
            free(args);
            exit(1);
        }
    }

    // Join threads
    for (int t = 0; t < z; t++)
    {
        pthread_join(threads[t], NULL);
    }
}

// Read in matricies, call and time parallel matrix multiplication
int main(int argc, char *argv[])
{
    // number of threads, dim of matrix
    int num_threads = 8;
    int n = 1024;

    if (argc == 3)
    {
        num_threads = atoi(argv[1]);
        n = atoi(argv[2]);
        // printf("Number of threads: %d\n", num_threads);
        // printf("Matrix dimension: %d\n", n);
    }

    // get the name of the matrices we read from
    char name1[20];
    char name2[20];
    sprintf(name1, "a%d.mat", n);
    sprintf(name2, "b%d.mat", n);
    sprintf(name1, "a%d.mat", n);
    sprintf(name2, "b%d.mat", n);

    int **A, **B;

    read_matrix_from_csv(name1, &A, &n);
    read_matrix_from_csv(name2, &B, &n);

    // printf("Successfully read matrices\n");

    int **C = (int **)malloc(n * sizeof(int *));

    // Initially tried allocating C as one ibg n * n chunk of memory, this appeared to have no effect

    // int *data = (int *)calloc(n * n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        // C[i] = data + i * (n);
        C[i] = (int *)calloc(n, sizeof(int));
    }

    struct timespec start, end;

    int trials = 3;

    // if we want to do the transpose method, use transpose_matrix on B

    transpose_matrix(B, n);

    clock_gettime(CLOCK_REALTIME, &start); // used to time latency of matrix multiply
    // the important line

    // run 3 trials
    for (int i = 0; i < trials; i++)
    {
        // threads_mat_mul(A, B, C, n, num_threads);
        transpose_threads_mat_mul(A, B, C, n, num_threads);
    }

    clock_gettime(CLOCK_REALTIME, &end);

    // char name3[20];
    // sprintf(name3, "c%d.mat", n);
    // write_matrix_to_csv(name3, C, n);

    // calculate the average elapsed time
    double elapsed_time;
    if (end.tv_nsec < start.tv_nsec)
    {
        elapsed_time = (end.tv_sec - start.tv_sec - 1) + (1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    }
    else
    {
        elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    }
    elapsed_time /= trials;

    long int num_ops = n * n * n;

    // print out the results, this will go into our csv
    printf("%d,%d,%ld,%f\n", num_threads, n, num_ops, elapsed_time);
}