#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};
struct node* createnode(int data)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
void inordertraversal(struct node* root, FILE* file)
 {
    if (root == NULL)
        return;

    inordertraversal(root->left, file);
    fprintf(file, "%d ", root->data);
    inordertraversal(root->right, file);
}
struct node* generate(int size)
{
    struct node* root = NULL;
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        {
        int data = rand() % 100;
        if (root == NULL)
            root = createnode(data);
        else {
            struct node* currentnode = root;
            struct node* parentnode = NULL;
            while (currentnode != NULL)
            {
                parentnode = currentnode;

                if (data < currentnode->data)
                    currentnode = currentnode->left;
                else
                    currentnode = currentnode->right;
            }
            struct node* newnode = createnode(data);
            if (data < parentnode->data)
                parentnode->left = newnode;
            else
                parentnode->right = newnode;
        }
    }

    return root;
}

int main()
{
    struct node* root = generate(10);
    FILE* inputFile = fopen("input.txt", "w");
    if (inputFile == NULL)
    {
        printf("Failed to open input file.\n");
        return 1;
    }
    inordertraversal(root, inputFile);
    fclose(inputFile);
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Failed to open output file.\n");
        return 1;
    }
    inordertraversal(root, outputFile);
    fclose(outputFile);
    return 0;
}

