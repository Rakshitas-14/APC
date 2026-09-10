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
    int sign1 = 1;
    int sign2 = 1;
    int result_sign = 1;
    int cmp;

    if (argc != 4)
    {
        printf("Usage: ./apc operand1 operator operand2\n");
        return 1;
    }

    /* Validate first operand */
    if (validate_operand(argv[1]) == 0)
    {
        printf("Invalid first operand\n");
        return 1;
    }

    /* Validate operator */
    if (validate_operator(argv[2]) == 0)
    {
        printf("Invalid operator\n");
        return 1;
    }

    /* Validate second operand */
    if (validate_operand(argv[3]) == 0)
    {
        printf("Invalid second operand\n");
        return 1;
    }

    /* Get sign of operand 1 */

    i = 0;

    if (argv[1][0] == '-')
    {
        sign1 = -1;
        i = 1;
    }
    else if (argv[1][0] == '+')
    {
        i = 1;
    }

    /* Store operand 1 */

    while (argv[1][i] != '\0')
    {
        insert_at_end(&head1, &tail1, argv[1][i] - '0');
        i++;
    }

    /* Get sign of operand 2 */

    i = 0;

    if (argv[3][0] == '-')
    {
        sign2 = -1;
        i = 1;
    }
    else if (argv[3][0] == '+')
    {
        i = 1;
    }

    /* Store operand 2 */

    while (argv[3][i] != '\0')
    {
        insert_at_end(&head2, &tail2, argv[3][i] - '0');
        i++;
    }

    /*ADDITION*/

    if (argv[2][0] == '+')
    {
        if (sign1 == sign2)
        {
            /* Same sign -> Addition */

            addition(tail1, tail2,
                     &head_result, &tail_result);

            result_sign = sign1;
        }
        else
        {
            /* Different signs -> Subtraction */

            cmp = compare_numbers(head1, head2);

            if (cmp >= 0)
            {
                subtraction(tail1, tail2,
                            &head_result, &tail_result);

                result_sign = sign1;
            }
            else
            {
                subtraction(tail2, tail1,
                            &head_result, &tail_result);

                result_sign = sign2;
            }
        }
    }

    /* SUBTRACTION*/

    else if (argv[2][0] == '-')
    {
        if (sign1 != sign2)
        {
            /* Different signs -> Addition */

            addition(tail1, tail2,
                     &head_result, &tail_result);

            result_sign = sign1;
        }
        else
        {
            /* Same signs -> Subtraction */

            cmp = compare_numbers(head1, head2);

            if (cmp >= 0)
            {
                subtraction(tail1, tail2,
                            &head_result, &tail_result);

                result_sign = sign1;
            }
            else
            {
                subtraction(tail2, tail1,
                            &head_result, &tail_result);

                result_sign = -sign1;
            }
        }
    }

    /* MULTIPLICATION*/

    else if (argv[2][0] == 'x')
    {
        multiplication(tail1, tail2,
                       &head_result, &tail_result);

        if (sign1 == sign2)
            result_sign = 1;
        else
            result_sign = -1;
    }

    /*DIVISION*/

    else if (argv[2][0] == '/')
    {
        division(head1, tail1, head2, tail2,&head_result, &tail_result);

        if (sign1 == sign2)
            result_sign = 1;
        else
            result_sign = -1;
    }

    /* Display result*/

    if (head_result != NULL)
    {
        printf("Result : ");

        /* Don't print - for zero */

        if (!(head_result->data == 0 &&
              head_result->next == NULL))
        {
            if (result_sign == -1)
                printf("-");
        }

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


/* Compare two positive numbers */

int compare_numbers(Node *head1, Node *head2)
{
    Node *temp1;
    Node *temp2;
    int count1 = 0;
    int count2 = 0;

    temp1 = head1;
    temp2 = head2;

    /* Count digits */

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    /* More digits means larger number */

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    /* Same number of digits */

    temp1 = head1;
    temp2 = head2;

    while (temp1 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
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