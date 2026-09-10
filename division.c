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
    Node *temp = head1;

    Node *temp_head = NULL;
    Node *temp_tail = NULL;

    Node *rem_head = NULL;
    Node *rem_tail = NULL;

    int count;

    /* Check division by zero */
    if (head2->data == 0 && head2->next == NULL)
    {
        printf("Division by zero is not possible\n");
        return;
    }

    /* Traverse through T1 */
    while (temp != NULL)
    {
        /* Insert H->data into Temph */
        insert_at_end(&temp_head, &temp_tail, temp->data);

        remove_leading_zeros(&temp_head, &temp_tail);

        count = 0;

        /* Compare Temph and head2 */
        while (compare_numbers(temp_head, head2) >= 0)
        {
            /* Call subtraction */
            subtraction(temp_tail, tail2,
                        &rem_head, &rem_tail);

            /* Delete list Temph */
            free_list(temp_head);

            temp_head = NULL;
            temp_tail = NULL;

            /* Swap Remh and Temph */
            temp_head = rem_head;
            temp_tail = rem_tail;

            rem_head = NULL;
            rem_tail = NULL;

            /* Increment Count */
            count++;
        }

        /* Insert Count into Result */
        insert_at_end(head_result, tail_result, count);

        /* Reset Count */
        count = 0;

        /* Update temp to next */
        temp = temp->next;
    }

    /* Remove leading zeros */
    remove_leading_zeros(head_result, tail_result);

    /* If result is empty */
    if (*head_result == NULL)
        insert_at_end(head_result, tail_result, 0);

    free_list(temp_head);
    free_list(rem_head);
}