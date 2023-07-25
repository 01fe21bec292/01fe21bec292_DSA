#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *getnode()
{
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    printf("Enter the data of the linked list: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    newnode->prev = NULL;
    return (newnode);
};

struct node *insert_beg(struct node *head)
{
    struct node *temp, *temp1;
    if (head == NULL)
    {
        head = getnode();
        return (head);
    }
    else
    {
        temp = head;
        temp1 = getnode();
        temp1->next = temp;
        temp1->prev = NULL;
        temp->prev = temp1;
        head = temp1;
        return (head);
    }
};

struct node *insert_end(struct node *head)
{
    struct node *temp, *temp1;
    if (head == NULL)
    {
        head = getnode();
        return (head);
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp1 = getnode();
        temp->next = temp1;
        temp1->prev = temp;
        temp1->next = NULL;
        return (head);
    }
};

void display(struct node *head)
{
    struct node *temp;
    temp = head;
    while (temp != NULL)
    {
        printf("<-%d->", temp->data);
        temp = temp->next;
    }
}

struct node *delete_beg(struct node *head)
{
    struct node *temp;
    if (head == NULL)
    {
        printf("Linked list is empty\n");
    }
    else
    {
        temp = head->next;
        temp->prev = NULL;
        head->next = NULL;
        free(head);
        head = temp;
        return (head);
    }
};

struct node *delete_end(struct node *head)
{
    struct node *temp, *temp1;
    if (head == NULL)
    {
        printf("Linked list is empty\n");
    }
    else
    {
        temp1 = head;
        temp = head->next;
        while (temp->next != NULL)
        {
            temp1 = temp;
            temp = temp->next;
        }
        temp1->next = NULL;
        temp->prev = NULL;
        free(temp);
        return (head);
    }
};

void saveLinkedList(struct node *head)
{
    FILE *file = fopen("doubly_linkedlist.txt", "w");
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
    while (temp != NULL)
    {
        fprintf(file, "%d ", temp->data);
        temp = temp->next;
    }

    fclose(file);
}

struct node *loadLinkedList()
{
    struct node *head = NULL;
    FILE *file = fopen("doubly_linkedlist.txt", "r");
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
        newnode->prev = NULL;

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
            newnode->prev = temp;
        }
    }

    fclose(file);
    return head;
}

int main()
{
    int ch;
    struct node *head;
    head = NULL;

    while (1)
    {
        printf("\n1. Insert at the end");
        printf("\n2. Insert at the beginning");
        printf("\n3. Display");
        printf("\n4. Delete from the beginning");
        printf("\n5. Delete from the end");
        printf("\n6. Save linked list to file");
        printf("\n7. Load linked list from file");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            head = insert_end(head);
            break;
        case 2:
            head = insert_beg(head);
            break;
        case 3:
            display(head);
            break;
        case 4:
            head = delete_beg(head);
            break;
        case 5:
            head = delete_end(head);
            break;
        case 6:
            saveLinkedList(head);
            printf("Linked list saved to file.\n");
            break;
        case 7:
            head = loadLinkedList();
            printf("Linked list loaded from file.\n");
            break;
        default:
            exit(0);
        }
    }

    return 0;
}
