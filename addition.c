#include "main.h"

void addition(Node *tail1, Node *tail2,
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