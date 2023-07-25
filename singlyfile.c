#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head;
struct node* insert_at_beg(struct node *, int);
struct node* insert_at_end(struct node *, int);
struct node* delete_at_beg(struct node *);
struct node* delete_at_end(struct node *);
void display(struct node *);
void saveLinkedList(struct node *);
struct node* loadLinkedList();

int main()
{
    int ch, c, pos, d;
    head = loadLinkedList();

    while (1)
    {
        printf("1--insert at beginning\n");
        printf("2--insert at end\n");
        printf("3--delete from beginning\n");
        printf("4--delete from end\n");
        printf("5--display linked list\n");
        printf("6--save linked list\n");
        printf("7--exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
            {
                struct node *newnode = (struct node *)malloc(sizeof(struct node));
                printf("Enter data: ");
                scanf("%d", &newnode->data);
                head = insert_at_beg(head, newnode->data);
                break;
            }
            case 2:
            {
                struct node *newnode = (struct node *)malloc(sizeof(struct node));
                printf("Enter data: ");
                scanf("%d", &newnode->data);
                head = insert_at_end(head, newnode->data);
                break;
            }
            case 3:
            {
                if (head == NULL)
                    printf("Linked list is empty. Cannot delete.\n");
                else
                {
                    head = delete_at_beg(head);
                }
                break;
            }
            case 4:
            {
                if (head == NULL)
                    printf("Linked list is empty. Cannot delete.\n");
                else
                {
                    head = delete_at_end(head);
                }
                break;
            }
            case 5:
                display(head);
                break;
            case 6:
                saveLinkedList(head);
                printf("Linked list saved to file.\n");
                break;
            case 7:
                saveLinkedList(head);
                printf("Linked list saved to file. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
}

struct node* insert_at_beg(struct node *head, int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = head;
    return newnode;
}

struct node* insert_at_end(struct node *head, int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;

    if (head == NULL)
        return newnode;

    struct node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newnode;
    return head;
}

void display(struct node *head)
{
    if (head == NULL)
    {
        printf("The linked list is empty.\n");
        return;
    }

    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct node* delete_at_beg(struct node *head)
{
    struct node *temp = head;
    head = head->next;
    printf("Node deleted: %d\n", temp->data);
    free(temp);
    return head;
}

struct node* delete_at_end(struct node *head)
{
    if (head->next == NULL)
    {
        printf("Node deleted: %d\n", head->data);
        free(head);
        return NULL;
    }

    struct node *temp = head;
    struct node *temp1 = head->next;

    while (temp1->next != NULL)
    {
        temp = temp1;
        temp1 = temp1->next;
    }

    printf("Node deleted: %d\n", temp1->data);
    free(temp1);
    temp->next = NULL;
    return head;
}

void saveLinkedList(struct node *head)
{
    FILE *file = fopen("linkedlist.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct node *temp = head;
    while (temp != NULL)
    {
        fprintf(file, "%d ", temp->data);
        temp = temp->next;
    }

    fclose(file);
}

struct node* loadLinkedList()
{
    struct node *head = NULL;
    FILE *file = fopen("linkedlist.txt", "r");
    if (file == NULL)
    {
        printf("No existing linked list found.\n");
        return NULL;
    }

    int data;
    while (fscanf(file, "%d", &data) != EOF)
    {
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data = data;
        newnode->next = NULL;

        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            struct node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
        }
    }

    fclose(file);
    return head;
}

