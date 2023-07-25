#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

bool isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int element) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++(stack->top)] = element;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[(stack->top)--];
}

void performAction(Stack *stack, int action) {
    if (action == 0) {
        if (!isEmpty(stack)) {
            int poppedValue = pop(stack);
            printf("Undo Action: Pop %d\n", poppedValue);
        } else {
            printf("Undo Action: No elements to undo\n");
        }
    } else {
        push(stack, action);
        printf("Action: Push %d\n", action);
    }
}

int main() {
    FILE *file = fopen("actions.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    Stack stack;
    initialize(&stack);

    int action;
    while (fscanf(file, "%d", &action) != EOF) {
        performAction(&stack, action);
    }

    fclose(file);
    return 0;
}
