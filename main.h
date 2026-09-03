#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum
{
    SUCCESS,    
    FAILURE
}status;
typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}Slist;

//validating operands function 
Status validate_operands(char *str);
Status validate_operator(char *str);
Status convert_data(char *str);
#endif