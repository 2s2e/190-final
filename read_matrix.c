

#include <stdio.h>
#include <stdlib.h>

void read_matrix_from_csv(const char *filename, int ***matrix, int *n)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // First, determine the matrix size by counting commas in the first row
    char line[4096];
    if (fgets(line, sizeof(line), file) == NULL)
    {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    *n = 1;
    for (char *p = line; *p; p++)
    {
        if (*p == ',')
            (*n)++;
    }

    // Allocate memory for the matrix as a contiguous block
    *matrix = (int **)malloc(*n * sizeof(int *));
    // int *data = (int *)malloc(*n * *n * sizeof(int));
    for (int i = 0; i < *n; i++)
    {
        (*matrix)[i] = (int *)malloc(*n * sizeof(int));
        //(*matrix)[i] = data + i * *n;
    }

    // Rewind file and read the entire matrix
    rewind(file);
    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            if (fscanf(file, "%d%*c", &((*matrix)[i][j])) != 1)
            {
                perror("Error reading matrix");
                fclose(file);
                // free(data);
                for (int i = 0; i < *n; i++)
                    free((*matrix)[i]);
                free(*matrix);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
}

void write_matrix_to_csv(const char *filename, int **matrix, int n)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%d", matrix[i][j]);
            if (j < n - 1)
            {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void print_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int **matrix)
{
    free(matrix[0]); // Free the contiguous block
    free(matrix);    // Free the row pointers
}
