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

    findDuplicates(array, size);

    return 0;
}
void findDuplicates(int array[], int size) {
    int i, j;
    int frequency[100] = {0};

    FILE *duplicateFile = fopen("duplicates.txt", "w");
    if (duplicateFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(duplicateFile, "Duplicate elements:\n");

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (array[i] == array[j] && frequency[array[i]] == 0) {
                fprintf(duplicateFile, "%d ", array[i]);
                frequency[array[i]]++;
            }
        }
    }

    fclose(duplicateFile);

    printf("Duplicate elements written to 'duplicates.txt'.\n");

    printf("Frequency of numbers:\n");

    FILE *frequencyFile = fopen("frequency.txt", "w");
    if (frequencyFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (i = 0; i < size; i++) {
        if (frequency[array[i]] != 0) {
            fprintf(frequencyFile, "%d : %d\n", array[i], frequency[array[i]]);
            frequency[array[i]] = 0;
        }
    }

    fclose(frequencyFile);

    printf("Frequency of numbers written to 'frequency.txt'.\n");
}


