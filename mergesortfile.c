#include <stdio.h>
int main() {
    int array[100];
    int size, i;
        FILE *file = fopen("input_array.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d", &size);

    for (i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    mergeSort(array, size);

    file = fopen("sorted_array.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);

    printf("Array sorted and saved to 'sorted_array.txt'.\n");

    return 0;
}


void merge(int array[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = array[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = array[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(array, left, mid, right, size - mid);
}

