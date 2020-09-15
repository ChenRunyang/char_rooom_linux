
#include "myhead.h"

int pack_msg(int new_fd,online **head,Message *msg)
{
    online *temp = *head;

    if(msg->action == CHAT_ONE)
    {
        while(temp != NULL)
        {
            if(strcmp(msg->target,temp->name) == 0)
            {
                write(temp->new_fd,msg,sizeof(Message));

                return SUCCESS;
            }

            temp = temp->next;
        }

        msg->action = FRIEND_NOT_ONLINE;
        write(new_fd,msg,sizeof(Message));

        return FALSE;
    }

    else if(msg->action == CHAT_ALL)
    {
        while(temp != NULL)
        {
            if(strcmp(msg->user,temp->name) != 0)
            {
                write(temp->new_fd,msg,sizeof(Message));
            }

            temp = temp->next;
        }

        return SUCCESS;
    }
}
