#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

int evaluatePostfix(char *expression) {
    Stack stack;
    initialize(&stack);
    int i = 0;

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            push(&stack, expression[i] - '0');
        } else {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            int result;

            switch (expression[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator\n");
                    return 0;
            }

            push(&stack, result);
        }
        i++;
    }

    return pop(&stack);
}

int main()
{
    FILE *file = fopen("expression.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char expression[MAX_SIZE];
    if (fgets(expression, sizeof(expression), file) == NULL) {
        printf("Failed to read the expression from the file.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    int result = evaluatePostfix(expression);
    printf("Result: %d\n", result);

    return 0;
}

