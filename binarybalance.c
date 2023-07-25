#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to allocate a new node with the given data
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
struct Node* insert(struct Node* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return (newNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Duplicate keys are not allowed
        return node;
}
void storeInOrder(struct Node* root, FILE* file)
 {
    if (root == NULL)
        return;

    storeInOrder(root->left, file);
    fprintf(file, "%d ", root->data);
    storeInOrder(root->right, file);
}
int findMaxLevel(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftLevel = findMaxLevel(root->left);
        int rightLevel = findMaxLevel(root->right);
        return (leftLevel > rightLevel) ? (leftLevel + 1) : (rightLevel + 1);
    }
}

// Function to print nodes at a given level in a binary tree
void printNodesAtLevel(struct Node* root, int level, FILE* output_file) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        fprintf(output_file, "%d ", root->data);
    } else if (level > 1) {
        printNodesAtLevel(root->left, level - 1, output_file);
        printNodesAtLevel(root->right, level - 1, output_file);
    }
}

// Function to display final output of nodes at each level in a binary tree
void displayLevels(struct Node* root, FILE* output_file) {
    int maxLevel = findMaxLevel(root);
    int i;
    for (i = 1; i <= maxLevel; i++) {
        fprintf(output_file, "Level %d: ", i);
        printNodesAtLevel(root, i, output_file);
        fprintf(output_file, "\n");
    }
}
int main() {
    FILE* input_file = fopen("input.txt", "w");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Failed to open files!\n");
        return 1;
    }

    // Generate random numbers and store them in the file
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        int num = rand() % 100; // Generate a random number between 0 and 99
        fprintf(input_file, "%d ", num);
    }

    fclose(input_file); // Close the input file

    input_file = fopen("input.txt", "r"); // Reopen the input file for reading

    struct Node* root = NULL;
    int num;

    // Read numbers from the file and build the AVL tree
    while (fscanf(input_file, "%d", &num) != EOF) {
        root = insert(root, num);
    }
// Perform user-defined operations on the AVL tree
    int choice, search_key, delete_key;
    while (1) {
        printf("1. Insert\n2. Exit\n3.display\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number to insert: ");
                scanf("%d", &num);
                root = insert(root, num);
                break;

            case 2:
                // Store the final output in a file
                storeInOrder(root, output_file);

                // Close files
                fclose(input_file);
                fclose(output_file);

                return 0;
            case 3:
                 displayLevels(root, output_file);
                 break;

            default:
                printf("Invalid choice!\n");
                break;
        }

        printf("\n");
    }
}
