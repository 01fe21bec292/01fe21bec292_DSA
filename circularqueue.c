#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

void enqueue(int data);
int dequeue();
int isQueueEmpty();
int isQueueFull();
void displayQueue();

int main() {
    FILE *file = fopen("circular_queue.txt", "w+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int choice, data;

    do {
        printf("\nCircular Queue Operations\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isQueueFull()) {
                    printf("Queue is full.\n");
                } else {
                    printf("Enter the element to enqueue: ");
                    scanf("%d", &data);
                    enqueue(data);
                }
                break;
            case 2:
                if (isQueueEmpty()) {
                    printf("Queue is empty.\n");
                } else {
                    data = dequeue();
                    printf("Dequeued element: %d\n", data);
                }
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    fclose(file);
    return 0;
}

void enqueue(int data) {
    FILE *file = fopen("circular_queue.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    fprintf(file, "%d\n", data);

    fclose(file);
}

int dequeue() {
    FILE *file = fopen("circular_queue.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    int data, dequeuedData;
    fseek(file, 0, SEEK_SET);
    fscanf(file, "%d", &data);
    dequeuedData = data;

    fseek(file, 0, SEEK_SET);
    while (fscanf(file, "%d", &data) != EOF) {
        fprintf(file, "%d\n", data);
    }
    fflush(file);
    ftruncate(fileno(file), ftell(file));

    fclose(file);
    return dequeuedData;
}

int isQueueEmpty() {
    FILE *file = fopen("circular_queue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int isEmpty = fgetc(file) == EOF;

    fclose(file);
    return isEmpty;
}

int isQueueFull() {
    FILE *file = fopen("circular_queue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int count = 0;
    int data;
    while (fscanf(file, "%d", &data) != EOF) {
        count++;
    }

    fclose(file);
    return count >= MAX_SIZE;
}

void displayQueue() {
    FILE *file = fopen("circular_queue.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int data;
    printf("Queue elements: ");
    while (fscanf(file, "%d", &data) != EOF) {
        printf("%d ", data);
    }
    printf("\n");

    fclose(file);
}

