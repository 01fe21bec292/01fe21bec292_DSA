#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head, *temp, *temp1, *newnode;
struct node *insert_at_beg(struct node *);
struct node *insert_at_end(struct node *);
struct node *delete_at_beg(struct node *);
struct node *delete_at_end(struct node *);
void display(struct node *);
void saveLinkedList(struct node *);
struct node *loadLinkedList();

int main()
{
    head = loadLinkedList();
    int ch, c, pos, d;
    while (1)
    {
        printf("1 - Insert at beginning\n");
        printf("2 - Insert at end\n");
        printf("3 - Delete at beginning\n");
        printf("4 - Delete at end\n");
        printf("5 - Display\n");
        printf("6 - Save linked list\n");
        printf("7 - Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
            {
                newnode = (struct node *)malloc(sizeof(struct node));
                printf("Enter the data: ");
                scanf("%d", &newnode->data);
                head = insert_at_beg(newnode);
                break;
            }
            case 2:
            {
                newnode = (struct node *)malloc(sizeof(struct node));
                printf("Enter the data: ");
                scanf("%d", &newnode->data);
                head = insert_at_end(newnode);
                break;
            }
            case 3:
            {
                head = delete_at_beg(head);
                break;
            }
            case 4:
            {
                head = delete_at_end(head);
                break;
            }
            case 5:
            {
                display(head);
                break;
            }
            case 6:
            {
                saveLinkedList(head);
                printf("Linked list saved to file.\n");
                break;
            }
            case 7:
            {
                saveLinkedList(head);
                printf("Linked list saved to file. Exiting...\n");
                exit(0);
            }
            default:
            {
                printf("Invalid choice.\n");
                break;
            }
        }
    }
}

struct node *insert_at_beg(struct node *newnode)
{
    if (head == NULL)
    {
        head = newnode;
        newnode->next = head;
    }
    else
    {
        temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->next = head;
        head = newnode;
    }
    return (head);
}

struct node *insert_at_end(struct node *newnode)
{
    if (head == NULL)
    {
        head = newnode;
        newnode->next = head;
    }
    else
    {
        temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->next = head;
    }
    return (head);
}

struct node *delete_at_beg(struct node *head)
{
    if (head == NULL)
    {
        printf("CLL is empty--can't delete\n");
    }
    else
    {
        if (head->next == head)
        {
            printf("Node deleted = %d\n", head->data);
            free(head);
            head = NULL;
        }
        else
        {
            temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            printf("Node deleted = %d\n", head->data);
            temp1 = head->next;
            free(head);
            temp->next = temp1;
            head = temp1;
        }
    }
    return (head);
}

struct node *delete_at_end(struct node *head)
{
    if (head == NULL)
    {
        printf("CLL is empty--can't delete\n");
    }
    else
    {
        if (head->next == head)
        {
            printf("Node deleted = %d\n", head->data);
            free(head);
            head = NULL;
        }
        else
        {
            temp = head;
            while (temp->next != head)
            {
                temp1 = temp;
                temp = temp->next;
            }
            printf("Node deleted = %d\n", temp->data);
            free(temp);
            temp1->next = head;
        }
    }
    return (head);
}

void display(struct node *head)
{
    if (head == NULL)
    {
        printf("CLL is empty\n");
    }
    else
    {
        temp = head;
        while (temp->next != head)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("%d\n", temp->data);
    }
}

void saveLinkedList(struct node *head)
{
    FILE *file = fopen("linkedlist.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    if (head == NULL)
    {
        fclose(file);
        return;
    }

    struct node *temp = head;
    do
    {
        fprintf(file, "%d ", temp->data);
        temp = temp->next;
    } while (temp != head);

    fclose(file);
}

struct node *loadLinkedList()
{
    struct node *head = NULL;
    FILE *file = fopen("clinkedlist.txt", "r");
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
            newnode->next = head;
        }
        else
        {
            temp = head;
            while (temp->next != head)
                temp = temp->next;

            temp->next = newnode;
            newnode->next = head;
        }
    }

    fclose(file);
    return head;
}
