#include"main.h"

Status validate_operands(char *str)
{
     for(int i=0;str[i]!='\0';i++)
     {
        if(!(str[i]>='0' && str[i] <='9'))
        {
            return FAILURE;
        }
     } 
     return SUCCESS;      
}
Status validate_operator(char *str)
{
    if(str[1]!='\0')
    {
        return FAILURE;
    }
    if(str[0]=='+' || str[0]=='-' || str[0]=='X' || str[0]== '/')
    {
        return SUCCESS;
    }
        return FAILURE;
}
Status convert_data(char *str, Slist **head)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        int digit = str[i] - '0';

        Slist *new = malloc(sizeof(Slist));

        if(new == NULL)
        {
            return FAILURE;
        }

        new->data = digit;
        new->prev = NULL;
        new->next = NULL;

        if(*head == NULL)
        {
            *head = new;
        }
        else
        {
            Slist *temp = *head;

            while(temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = new;
            new->prev = temp;
        }
    }

    return SUCCESS;
}
int main(int argc,char *argv[])
{
    Slist *head1 = NULL;
    Slist *head2 = NULL;
    //validate the command line arguments
    if(argc!=4)
    {
        return FAILURE;
    }
    int ret1=validate_operands(argv[1]);
    int ret2=validate_operands(argv[3]);
    int ret3=validate_operator(argv[2]);
        if(ret1==SUCCESS && ret2 == SUCCESS && ret3 == SUCCESS)
        {
            printf("arguments which are passed by user are valid \n");
            return SUCCESS;
        }
        else
        {
            printf("invalid arguments\n");
            return FAILURE;
        }
    convert_data(argv[1],&head1);
    convert_data(argv[3],&head2);
}