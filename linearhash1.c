#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct HashTable
{
    int data[SIZE];
};
void initializehashtable(struct HashTable* hashTable)
{
    for (int i = 0; i < SIZE; i++) {
        hashTable->data[i] = -1;
    }
}
int calculatehash(int key)
 {
    return key % SIZE;
}
void insert(struct HashTable* hashTable, int number)
{
    int index = calculatehash(number);
    while (hashTable->data[index] != -1)
    {
        index = (index + 1) % SIZE;
    }
    hashTable->data[index] = number;
}
int search(struct HashTable* hashTable, int number)
{
    int index = calculatehash(number);
    while (hashTable->data[index] != -1)
    {
        if (hashTable->data[index] == number)
        {
            return index;
        }
        index = (index + 1) % SIZE;
    }
    return -1;
}
void display(struct HashTable* hashTable, FILE* file)
 {
    fprintf(file, "Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hashTable->data[i] != -1) {
            fprintf(file, "[%d] -> %d\n", i, hashTable->data[i]);
        } else {
            fprintf(file, "[%d] -> Empty\n", i);
        }
    }
    fprintf(file, "\n");
}

int main()
{
    struct HashTable hashTable;
    initializehashtable(&hashTable);
    FILE* inputFile = fopen("inputlin.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }
    int number;
    while (fscanf(inputFile, "%d", &number) != EOF)
    {
        insert(&hashTable, number);
    }
    fclose(inputFile);
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Failed to open output file.\n");
        return 1;
    }
    display(&hashTable, outputFile);
    fclose(outputFile);

    return 0;
}

