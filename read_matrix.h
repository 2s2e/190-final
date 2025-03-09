#ifndef MATRIX_CSV_UTILS_H
#define MATRIX_CSV_UTILS_H

#include <stdio.h>
#include <stdlib.h>

void read_matrix_from_csv(const char *filename, int ***matrix, int *n);
void write_matrix_to_csv(const char *filename, int **matrix, int n);
void print_matrix(int **matrix, int n);
void free_matrix(int **matrix);

#endif // MATRIX_CSV_UTILS_H
