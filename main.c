#include "main.h"

int main(int argc, char *argv[])
{
    Node *head1 = NULL;
    Node *tail1 = NULL;

    Node *head2 = NULL;
    Node *tail2 = NULL;

    Node *head_result = NULL;
    Node *tail_result = NULL;

    int i;

    if (argc != 4)
    {
        printf("Usage: ./apc operand1 operator operand2\n");
        return 1;
    }

    if (validate_operand(argv[1]) == 0)
    {
        printf("Invalid first operand\n");
        return 1;
    }

    if (validate_operator(argv[2]) == 0)
    {
        printf("Invalid operator\n");
        return 1;
    }

    if (validate_operand(argv[3]) == 0)
    {
        printf("Invalid second operand\n");
        return 1;
    }

    /* First operand */
    i = 0;

    if (argv[1][0] == '+' || argv[1][0] == '-')
        i = 1;

    while (argv[1][i] != '\0')
    {
        insert_at_end(&head1, &tail1, argv[1][i] - '0');
        i++;
    }

    /* Second operand */
    i = 0;

    if (argv[3][0] == '+' || argv[3][0] == '-')
        i = 1;

    while (argv[3][i] != '\0')
    {
        insert_at_end(&head2, &tail2, argv[3][i] - '0');
        i++;
    }

    /* Operation */
    switch (argv[2][0])
    {
        case '+':
            addition(tail1, tail2, &head_result, &tail_result);
            break;

        case '-':
            subtraction(tail1, tail2, &head_result, &tail_result);
            break;

        case 'x':
            multiplication(tail1, tail2, &head_result, &tail_result);
            break;

        case '/':
            division(tail1, tail2, &head_result, &tail_result);
            break;
    }

    if (head_result != NULL)
    {
        printf("Result : ");
        display_list(head_result);
    }

    return 0;
}


/* Insert at end */
void insert_at_end(Node **head, Node **tail, int data)
{
    Node *new = malloc(sizeof(Node));

    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }
}


/* Insert at beginning */
void insert_at_beginning(Node **head, Node **tail, int data)
{
    Node *new = malloc(sizeof(Node));

    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}


/* Display */
void display_list(Node *head)
{
    Node *temp = head;

    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }

    printf("\n");
}


/* Validate operand */
int validate_operand(const char *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 0;

    if (str[i] == '+' || str[i] == '-')
        i++;

    if (str[i] == '\0')
        return 0;

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;

        i++;
    }

    return 1;
}


/* Validate operator */
int validate_operator(const char *str)
{
    if (str == NULL)
        return 0;

    if (strlen(str) != 1)
        return 0;

    if (str[0] == '+' ||
        str[0] == '-' ||
        str[0] == 'x' ||
        str[0] == '/')
    {
        return 1;
    }

    return 0;
}