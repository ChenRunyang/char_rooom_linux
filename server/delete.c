#include "myhead.h"

int out_online(online **head,Message *msg,int new_fd)
{
    online *temp = *head;

    if(strcmp(temp->name,msg->target) == 0)
    {
        write(temp->new_fd,msg,sizeof(Message));
        *head = (*head)->next;
        free(temp);
        temp = NULL;
        return SUCCESS;
    }

    online *temp1 = (*head)->next;

    while(temp1 != NULL)
    {
        if(strcmp(temp1->name,msg->target) == 0)
        {
            write(temp1->new_fd,msg,sizeof(Message));
            temp->next = temp1->next;
            free(temp1);
            temp1 = NULL;
            return SUCCESS;
        }

        temp = temp1;
        temp1 = temp1->next;
    }

    return FALSE;
}
