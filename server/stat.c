
#include "myhead.h"

int stat(Message *msg,int new_fd,online **head)
{
    online *temp = *head;
    printf("msg->action = %d\n",msg->action);
    if(msg->action == BAN)
    {
        if(strcmp(msg->user,"admin") == 0)
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
        }
        else
        {
            msg->action = NOT_ADMIN;
            write(new_fd,msg,sizeof(Message));
        }
    }

    else if(msg->action == UNBAN)
    {
        if(strcmp(msg->user,"admin") == 0)
        {
            while(temp != NULL)
            {
                printf("msg->target = %s\n",msg->target);
                printf("temp->name = %s\n",temp->name);
                if(strcmp(msg->target,temp->name) == 0)
                {
                    write(temp->new_fd,msg,sizeof(Message));
                    return SUCCESS;
                }

                temp = temp->next;
            }

            return FALSE;
        }
        else
        {
            msg->action = NOT_ADMIN;
            write(new_fd,msg,sizeof(Message));
        }

        return FALSE;
    }
    else if(msg->action == KICK)
    {
        if(strcmp(msg->user,"admin") == 0)
        {
            out_online(head,msg);
            /*
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
            */
        }
        else
        {
            msg->action = NOT_ADMIN;
            write(new_fd,msg,sizeof(Message));
        }
    }

    return FALSE;
}
