#include "myhead.h"

int chat_one(Message *msg,int sockfd)
{
    printf("chat_one flag = %d\n",flag);

        if(flag == FORCED_OFF_LINE)
        {
            printf("you are not online!\n");
            return FALSE;
        }
        if(flag == KICK)
        {
            printf("you have been kicked by admin,so you cannot chat to anyone!\n");
        }
        else
        {
            if(flag == BAN)
            {
                printf("you have been banned by admin\n");
            }
            else
            {
                printf("please input you want chat name:");
                scanf("%s",msg->target);

                printf("please input you want send message:");
                scanf("%s",msg->message);

                msg->action = CHAT_ONE;
                write(sockfd,msg,sizeof(Message));
            }
        }
}
