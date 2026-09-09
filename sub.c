#include "main.h"

void subtraction(Node *tail1, Node *tail2,
                 Node **head_result, Node **tail_result)
{
    int borrow = 0;
    int diff;

    while (tail1 != NULL)
    {
        diff = tail1->data - borrow;

        if (tail2 != NULL)
        {
            diff = diff - tail2->data;
            tail2 = tail2->prev;
        }

        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insert_at_beginning(head_result, tail_result, diff);

        tail1 = tail1->prev;
    }

    /* Remove leading zeros */
    while (*head_result != NULL &&
           (*head_result)->data == 0 &&
           (*head_result)->next != NULL)
    {
        Node *temp = *head_result;
        *head_result = (*head_result)->next;
        (*head_result)->prev = NULL;
        free(temp);
    }
}