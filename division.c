#include "main.h"

/* Compare two numbers
   1  -> first number is greater
   0  -> equal
  -1  -> first number is smaller
*/
int compare_lists(Node *head1, Node *head2)
{
    int count1 = 0;
    int count2 = 0;
    Node *temp1 = head1;
    Node *temp2 = head2;

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

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}


/* Delete complete list */
void delete_list(Node **head, Node **tail)
{
    Node *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}


/* Remove leading zeros */
void remove_leading_zeros(Node **head, Node **tail)
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

    if (*head == NULL)
        *tail = NULL;
}


/* Division */
void division(Node *tail1, Node *tail2,
              Node **head_result, Node **tail_result)
{
    Node *temp = NULL;
    Node *temp_tail = NULL;

    Node *rem = NULL;
    Node *rem_tail = NULL;

    Node *divisor_head = tail2;

    int count;

    /* Find head of divisor */
    while (divisor_head != NULL &&
           divisor_head->prev != NULL)
    {
        divisor_head = divisor_head->prev;
    }

    /* Start from head of dividend */
    while (tail1 != NULL &&
           tail1->prev != NULL)
    {
        tail1 = tail1->prev;
    }

    while (tail1 != NULL)
    {
        /* Insert current digit into Temp */
        insert_at_end(&temp, &temp_tail, tail1->data);

        remove_leading_zeros(&temp, &temp_tail);

        count = 0;

        /* Repeated subtraction */
        while (compare_lists(temp, divisor_head) >= 0)
        {
            rem = NULL;
            rem_tail = NULL;

            subtraction(temp_tail, tail2,
                        &rem, &rem_tail);

            delete_list(&temp, &temp_tail);

            temp = rem;
            temp_tail = rem_tail;

            count++;
        }

        /* Insert quotient digit */
        insert_at_end(head_result, tail_result, count);

        /* Move to next dividend digit */
        tail1 = tail1->next;
    }

    /* Remove leading zeros from quotient */
    remove_leading_zeros(head_result, tail_result);

    /* If quotient is empty, result is 0 */
    if (*head_result == NULL)
    {
        insert_at_end(head_result, tail_result, 0);
    }

    delete_list(&temp, &temp_tail);
}