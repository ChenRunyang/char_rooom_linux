#include "myhead.h"

int onlinefriend(Message *msg,int sockfd)
{
    printf("onlin\n");

        if(flag == FORCED_OFF_LINE)
        {
            printf("you are not online!\n");
            return FALSE;
        }
        if(flag == KICK)
        {
            printf("you have been kicked by admin, so you cannot check online friend!\n");
        }
        else
        {
            msg->action = CHECK_ONLINE_FRIEND;

            write(sockfd,msg,sizeof(Message));
        }
}
