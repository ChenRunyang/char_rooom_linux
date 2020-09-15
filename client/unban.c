#include "myhead.h"

int unban(Message *msg,int sockfd)
{

        if(flag == FORCED_OFF_LINE)
        {
            printf("you are not online!\n");
            return FALSE;
        }
        if(flag == KICK)
        {
            printf("you have been kicked by admin!\n");
        }
        else
        {
            printf("please input you want unban name:");
            scanf("%s",msg->target);

            msg->action = UNBAN;

            write(sockfd,msg,sizeof(Message));
        }
}
