#include<stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation error!");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

struct Node* delete(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* successor = root->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        root->data = successor->data;
        root->right = delete(root->right, successor->data);
    }

    return root;
}

void inOrderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        inOrderTraversal(root->left, file);
        fprintf(file, "%d\n", root->data);
        inOrderTraversal(root->right, file);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, data;
    FILE* file = fopen("tree.txt", "a+");

    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    while (fscanf(file, "%d", &data) != EOF) {
        root = insert(root, data);
    }

    srand(time(NULL));

    while (1) {
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert Random Number\n");
        printf("2. Delete Number\n");
        printf("3. Search Number\n");
        printf("4. Print (in-order traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                data = rand() % 100;
                root = insert(root, data);
                fprintf(file, "%d\n", data);
                printf("Random number %d inserted into the tree.\n", data);
                break;
            case 2:
                printf("Enter the number to be deleted: ");
                scanf("%d", &data);
                if (search(root, data) != NULL) {
                    root = delete(root, data);
                    printf("Number %d deleted from the tree.\n", data);
                    fclose(file);
                    file = fopen("tree.txt", "w");
                    if (file == NULL) {
                        printf("Error opening file!");
exit(1);
                    }
                    inOrderTraversal(root, file);
                    fclose(file);
                    file = fopen("tree.txt", "a+");
                } else {
                    printf("Number %d not found in the tree.\n", data);
                }
                break;
            case 3:
                printf("Enter the number to be searched: ");
                scanf("%d", &data);
                if (search(root, data) != NULL) {
                    printf("Number %d found in the tree.\n", data);
                } else {
                    printf("Number %d not found in the tree.\n", data);
                }
                break;
            case 4:
                printf("Binary Search Tree (in-order traversal):\n");
                inOrderTraversal(root, stdout);
                break;
            case 5:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
