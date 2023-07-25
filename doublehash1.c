#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct HashTable {
    int data[SIZE];
};

// Function to initialize the hash table
void initializeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < SIZE; i++) {
        hashTable->data[i] = -1;
    }
}

// Function to calculate the primary hash value for a given key
int calculatePrimaryHash(int key) {
    return key % SIZE;
}

// Function to calculate the secondary hash value for a given key
int calculateSecondaryHash(int key) {
    return 7 - (key % 7); // Using prime number 7 for double hashing
}

// Function to insert a number into the hash table using double hashing
void insert(struct HashTable* hashTable, int number) {
    int primaryIndex = calculatePrimaryHash(number);
    int secondaryIndex = calculateSecondaryHash(number);

    // Find the next available index using double hashing
    while (hashTable->data[primaryIndex] != -1) {
        primaryIndex = (primaryIndex + secondaryIndex) % SIZE;
    }

    // Insert the number at the index
    hashTable->data[primaryIndex] = number;
}

// Function to search for a number in the hash table using double hashing
int search(struct HashTable* hashTable, int number) {
    int primaryIndex = calculatePrimaryHash(number);
    int secondaryIndex = calculateSecondaryHash(number);

    // Find the number by probing until an empty slot or the number is found
    while (hashTable->data[primaryIndex] != -1) {
        if (hashTable->data[primaryIndex] == number) {
            return primaryIndex;
        }
        primaryIndex = (primaryIndex + secondaryIndex) % SIZE;
    }

    // Number not found
    return -1;
}

// Function to display the hash table
void display(struct HashTable* hashTable, FILE* file) {
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

int main() {
    // Initialize the hash table
    struct HashTable hashTable;
    initializeHashTable(&hashTable);

    // Open the input file in read mode
    FILE* inputFile = fopen("inputdoub.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    // Read numbers from the input file and insert them into the hash table
    int number;
    while (fscanf(inputFile, "%d", &number) != EOF) {
        insert(&hashTable, number);
    }

    // Close the input file
    fclose(inputFile);

    // Open the output file in write mode
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return 1;
    }

    // Display the hash table and write to the output file
    display(&hashTable, outputFile);

    // Close the output file
    fclose(outputFile);

    return 0;
}

