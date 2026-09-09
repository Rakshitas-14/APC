#include "main.h"

void multiplication(Node *tail1, Node *tail2,
                    Node **head_result, Node **tail_result)
{
    int carry = 0;
    int product;
    int digit;
    int shift = 0;

    Node *temp1;
    Node *temp2;

    int result[100] = {0};
    int i = 0;
    int j = 0;

    /* Convert first number into an array */
    temp1 = tail1;

    while (temp1 != NULL)
    {
        temp1 = temp1->prev;
        i++;
    }

    /* Convert second number into an array */
    temp2 = tail2;

    while (temp2 != NULL)
    {
        temp2 = temp2->prev;
        j++;
    }

    int num1[100];
    int num2[100];

    temp1 = tail1;

    for (int k = i - 1; k >= 0; k--)
    {
        num1[k] = temp1->data;
        temp1 = temp1->prev;
    }

    temp2 = tail2;

    for (int k = j - 1; k >= 0; k--)
    {
        num2[k] = temp2->data;
        temp2 = temp2->prev;
    }

    /* Multiplication */
    for (int a = i - 1; a >= 0; a--)
    {
        for (int b = j - 1; b >= 0; b--)
        {
            result[a + b + 1] += num1[a] * num2[b];
        }
    }

    /* Handle carry */
    for (int k = i + j - 1; k > 0; k--)
    {
        result[k - 1] += result[k] / 10;
        result[k] = result[k] % 10;
    }

    /* Store result in linked list */
    int start = 0;

    while (start < i + j - 1 && result[start] == 0)
        start++;

    for (int k = start; k < i + j; k++)
    {
        insert_at_end(head_result, tail_result, result[k]);
    }
}