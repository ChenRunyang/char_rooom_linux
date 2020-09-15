#include "myhead.h"

int chat_all(Message *msg, int sockfd)
{
    printf("chat_all flag = %d\n",flag);
    //sleep(0.5);
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
                printf("you have been banned by admin!\n");
            }
            else
            {
                printf("please input you want send message:");
                scanf("%s",msg->message);

                msg->action = CHAT_ALL;

                write(sockfd,msg,sizeof(Message));
            }
        }
}
