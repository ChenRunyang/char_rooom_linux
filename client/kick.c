#include "myhead.h"

int kick(Message *msg,int sockfd)
{

        if(flag == FORCED_OFF_LINE)
        {
            printf("you are not online!\n");
            return FALSE;
        }
        if(flag == KICK)
        {
            printf("you have been kicked by admin!and you are not the admin!\n");
        }
        else
        {
            printf("please input you want kick name:");
            scanf("%s",msg->target);

            msg->action = KICK;

            write(sockfd,msg,sizeof(Message));
        }
}
