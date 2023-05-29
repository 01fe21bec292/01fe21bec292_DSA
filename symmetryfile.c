#include <stdio.h>

int main() {
    int matrix[100][100];
    int rows, cols;
    int i, j;

    FILE *file = fopen("matrix.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d %d", &rows, &cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    int result = isSymmetric(matrix, rows, cols);

    if (result) {
        printf("The matrix is symmetric.\n");
    } else {
        printf("The matrix is not symmetric.\n");
    }

    return 0;
}


int isSymmetric(int matrix[100][100], int rows, int cols) {
    int i, j;

    if (rows != cols) {
        return 0;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return 0;
            }
        }
    }

    return 1;
}

