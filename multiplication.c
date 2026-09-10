#include "main.h"

/* Multiply one number with one digit */
static void multiply_by_digit(Node *tail1, int digit,
                              Node **head, Node **tail)
{
    int carry = 0;
    int product;
    int result_digit;

    while (tail1 != NULL)
    {
        product = (tail1->data * digit) + carry;

        result_digit = product % 10;
        carry = product / 10;

        insert_at_beginning(head, tail, result_digit);

        tail1 = tail1->prev;
    }

    while (carry != 0)
    {
        insert_at_beginning(head, tail, carry % 10);
        carry = carry / 10;
    }

    if (*head == NULL)
    {
        insert_at_end(head, tail, 0);
    }
}


/* Add two linked lists */
static void add_lists(Node *tail1, Node *tail2,
                      Node **head_result, Node **tail_result)
{
    int carry = 0;
    int sum;
    int digit;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum = sum + tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum = sum + tail2->data;
            tail2 = tail2->prev;
        }

        digit = sum % 10;
        carry = sum / 10;

        insert_at_beginning(head_result, tail_result, digit);
    }
}


/* Free linked list */
static void free_list(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


/* Remove leading zeros */
static void remove_leading_zeros(Node **head)
{
    Node *temp;

    while (*head != NULL &&
           (*head)->data == 0 &&
           (*head)->next != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}


/* Multiplication */
void multiplication(Node *tail1, Node *tail2,
                     Node **head_result, Node **tail_result)
{
    Node *partial_head = NULL;
    Node *partial_tail = NULL;

    Node *new_head = NULL;
    Node *new_tail = NULL;

    int shift = 0;
    int i;

    /* Start result with zero */
    insert_at_end(head_result, tail_result, 0);

    /* Take each digit from second number */
    while (tail2 != NULL)
    {
        /* Multiply first number by current digit */
        multiply_by_digit(tail1, tail2->data,
                          &partial_head, &partial_tail);

        /* Shift partial result */
        for (i = 0; i < shift; i++)
        {
            insert_at_end(&partial_head, &partial_tail, 0);
        }

        /* Add partial result to final result */
        add_lists(*tail_result, partial_tail,
                  &new_head, &new_tail);

        /* Delete old result */
        free_list(*head_result);

        *head_result = new_head;
        *tail_result = new_tail;

        new_head = NULL;
        new_tail = NULL;

        /* Delete partial result */
        free_list(partial_head);

        partial_head = NULL;
        partial_tail = NULL;

        shift++;

        tail2 = tail2->prev;
    }

    remove_leading_zeros(head_result);
}