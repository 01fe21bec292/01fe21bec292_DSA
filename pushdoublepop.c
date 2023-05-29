#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int stack[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow.\n");
        return;
    }

    s->top++;
    s->stack[s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow.\n");
        return -1;
    }

    int value = s->stack[s->top];
    s->top--;

    return value;
}

int main() {
    Stack stack;
    initializeStack(&stack);

    int value;

    // Read input values from file and push to stack
    FILE *file = fopen("input_values.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%d", &value) != EOF) {
        push(&stack, value);
    }

    fclose(file);

    // Pop elements from stack and double their values
    file = fopen("doubled_values.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (!isEmpty(&stack)) {
        value = pop(&stack);
        int doubledValue = 2 * value;
        fprintf(file, "%d ", doubledValue);
    }

    fclose(file);

    printf("Values popped from stack and their doubled values saved to 'doubled_values.txt'.\n");

    return 0;
}

