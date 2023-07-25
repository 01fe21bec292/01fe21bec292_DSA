#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value)
 {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

int countSiblings(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL && current->data != key) {
        parent = current;
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return 0; // Key not found
    }

    struct Node* sibling = (current == parent->left) ? parent->right : parent->left;

    return (sibling != NULL) ? 1 : 0;
}

void printInorder(struct Node* root, FILE* outputFile) {
    if (root != NULL) {
        printInorder(root->left, outputFile);
        fprintf(outputFile, "%d ", root->data);
        printInorder(root->right, outputFile);
    }
}

int main()
{
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file.\n");
        return 1;
    }

    struct Node* root = NULL;
    int value;

    while (fscanf(inputFile, "%d", &value) != EOF)
    {
        root = insert(root, value);
    }

    printInorder(root, outputFile);

    int key;
    printf("Enter the key to count siblings: ");
    scanf("%d", &key);

    int siblings = countSiblings(root, key);
    printf("Number of siblings for key %d: %d\n", key, siblings);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

