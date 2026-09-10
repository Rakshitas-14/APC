#include "main.h"

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

static void remove_leading_zeros(Node **head, Node **tail)
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

    if (*head != NULL)
    {
        *tail = *head;

        while ((*tail)->next != NULL)
            *tail = (*tail)->next;
    }
}

void division(Node *head1, Node *tail1,
              Node *head2, Node *tail2,
              Node **head_result, Node **tail_result)
{
    (void)tail1;
    Node *temp = head1;

    Node *temp_head = NULL;
    Node *temp_tail = NULL;

    Node *rem_head = NULL;
    Node *rem_tail = NULL;

    int count;

    /* Division by zero */
    if (head2->data == 0 && head2->next == NULL)
    {
        printf("Division by zero is not possible\n");
        return;
    }

    /* Traverse dividend */
    while (temp != NULL)
    {
        /* Add current digit to temporary list */
        insert_at_end(&temp_head, &temp_tail, temp->data);

        /* Remove leading zeros */
        remove_leading_zeros(&temp_head, &temp_tail);

        count = 0;

        /* Subtract divisor repeatedly */
        while (temp_head != NULL &&
               compare_numbers(temp_head, head2) >= 0)
        {
            subtraction(temp_tail, tail2,
                        &rem_head, &rem_tail);

            /* Delete old temporary list */
            free_list(temp_head);

            /* Swap remainder with temporary list */
            temp_head = rem_head;
            temp_tail = rem_tail;

            rem_head = NULL;
            rem_tail = NULL;

            count++;
        }

        /* Store quotient digit */
        insert_at_end(head_result, tail_result, count);

        /* Move to next dividend digit */
        temp = temp->next;
    }

    /* Remove leading zeros from quotient */
    remove_leading_zeros(head_result, tail_result);

    /* If quotient is empty, result is zero */
    if (*head_result == NULL)
    {
        insert_at_end(head_result, tail_result, 0);
    }

    /* Free temporary lists */
    free_list(temp_head);
    free_list(rem_head);
}