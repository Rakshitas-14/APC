#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Node;

/* Validation */
int validate_operand(const char *str);
int validate_operator(const char *str);

/* Linked list */
void insert_at_end(Node **head, Node **tail, int data);
void insert_at_beginning(Node **head, Node **tail, int data);
void display_list(Node *head);

/* Arithmetic */
void addition(Node *tail1, Node *tail2,
              Node **head_result, Node **tail_result);

void subtraction(Node *tail1, Node *tail2,
                 Node **head_result, Node **tail_result);

void multiplication(Node *tail1, Node *tail2,
                    Node **head_result, Node **tail_result);

void division(Node *tail1, Node *tail2,
              Node **head_result, Node **tail_result);

#endif