#include "myhead.h"

int ban(Message *msg, int sockfd)
{
    printf("chat_all\n");

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
            printf("please input you want ban name:");
            scanf("%s",msg->target);

            msg->action = BAN;

            write(sockfd,msg,sizeof(Message));
        }
}
