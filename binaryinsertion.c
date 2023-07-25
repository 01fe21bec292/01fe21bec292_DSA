#include<stdio.h>
#include <stdlib.h>

typedef struct Node
 {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

void preOrder(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    fprintf(file, "%d ", root->data);
    preOrder(root->left, file);
    preOrder(root->right, file);
}

void postOrder(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left, file);
    postOrder(root->right, file);
    fprintf(file, "%d ", root->data);
}

void inOrder(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left, file);
    fprintf(file, "%d ", root->data);
    inOrder(root->right, file);
}

int main() {
    int n;
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &n);

    // Generate random numbers and insert into BST
    Node* root = NULL;
    FILE* inputFile = fopen("input.txt", "w");
    for (int i = 0; i < n; i++) {
        int num = rand() % 100; // Generate a random number between 0 and 99
        fprintf(inputFile, "%d ", num);
        root = insert(root, num);
    }
    fclose(inputFile);

    // Output pre-order traversal
    FILE* preOrderFile = fopen("preorder.txt", "w");
    preOrder(root, preOrderFile);
    fclose(preOrderFile);

    // Output post-order traversal
    FILE* postOrderFile = fopen("postorder.txt", "w");
    postOrder(root, postOrderFile);
    fclose(postOrderFile);

    // Output in-order traversal
    FILE* inOrderFile = fopen("inorder.txt", "w");
    inOrder(root, inOrderFile);
    fclose(inOrderFile);

    printf("Generated random numbers and traversal sequences have been saved to files.\n");

    return 0;
}
