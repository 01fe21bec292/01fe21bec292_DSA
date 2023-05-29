#include <stdio.h>
int main() {
    int matrix[100][100];
    int row, col;
    int i, j;

    FILE *file = fopen("matrix.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d %d", &row, &col);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    transposematrix(matrix, row, col);

    printf("Matrix transposed and saved to 'transposed_matrix.txt'.\n");

    return 0;
}


void transposematrix(int matrix[100][100], int row, int col) {
    int transposedmatrix[100][100];
    int i, j;

    for (i = 0; i < col; i++)
        {
        for (j = 0; j < row; j++) {
            transposedmatrix[i][j] = matrix[j][i];
        }
    }

    FILE *file = fopen("transposed_matrix.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d %d\n", col, row);

    for (i = 0; i < col; i++) {
        for (j = 0; j < row; j++) {
            fprintf(file, "%d ", transposedmatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

