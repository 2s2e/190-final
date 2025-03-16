

#include <stdio.h>
#include <stdlib.h>


// Reads matrix from .mat files into an array our program can use
void read_matrix_from_csv(const char *filename, int ***matrix, int *np)
{
    // Open .mat files containing matrix
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // First, determine the matrix size by counting commas in the first row
    // char line[4096];
    // if (fgets(line, sizeof(line), file) == NULL)
    // {
    //     perror("Error reading file");
    //     fclose(file);
    //     exit(EXIT_FAILURE);
    // }

    int n = 1;
    // for (char *p = line; *p; p++)
    // {
    //     if (*p == ',')
    //         n++;
    // }
    //*np = n;
    n = *np;

    // Initializes a pointer to a 2D array, which we will return at the end for the calling program to use
    *matrix = (int **)malloc(n * sizeof(int *));
    
    // Allocate memory for the matrix as a contiguous block
    // int *data = (int *)malloc(*n * *n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        (*matrix)[i] = (int *)malloc(n * sizeof(int));
        //(*matrix)[i] = data + i * *n;
    }

    // Rewind file and read the entire matrix
    rewind(file);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Read in a value at a time from the file into our output matrix
            // If we read in more than one value for this matrix entry, error
            // %*c is discard one character
            if (fscanf(file, "%d%*c", &((*matrix)[i][j])) != 1)
            {
                perror("Error reading matrix");
                fclose(file);
                // free(data);
                // for (int i = 0; i < *n; i++)
                //     free((*matrix)[i]);
                // free(*matrix);

                exit(EXIT_FAILURE);
            }
            // if (j == 0)
            //     printf("Demo: %d %d: %d, n is %d\n", i, j, (*matrix)[i][j], n);
        }
    }

    fclose(file);
}

// Takes a matrix generated from our program, and writes it to a CSV file for analysis
void write_matrix_to_csv(const char *filename, int **matrix, int n)
{

    // Prepare a file to be written to
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Write every element in the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%d", matrix[i][j]);

            // If this is NOT the last element in the row, add a comma to separate each column
            if (j < n - 1)
            {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Prints the matrix passed in, up to dimension n
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

// Frees the matrix passed in
// NOT USED
void free_matrix(int **matrix)
{
    free(matrix[0]); // Free the contiguous block
    free(matrix);    // Free the row pointers
}
