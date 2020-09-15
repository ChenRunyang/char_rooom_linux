#include "myhead.h"

void onlinefriend(Message *msg,int new_fd,online **head)
{
    online *temp = *head;

    while(temp != NULL)
    {
        if(strcmp(temp->name,msg->user) != 0)
        {
            strcpy(msg->target,temp->name);
            write(new_fd,msg,sizeof(Message));
        }

        temp = temp->next;
    }
}
