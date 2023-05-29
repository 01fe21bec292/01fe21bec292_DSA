#include <stdio.h>
int main() {
    int array[100];
    int n, i;
    FILE *file = fopen("input_array.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    bubblesort(array, n);

    file = fopen("sorted_array.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (i = 0; i <n; i++)
        {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);

    printf("Array sorted and saved to 'sorted_array.txt'.\n");

    return 0;
}

void bubblesort(int array[], int n) {
    int i, j;
    for (i = 0; i <n- 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

