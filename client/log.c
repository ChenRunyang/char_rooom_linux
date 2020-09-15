#include "myhead.h"

int log_c(Message *msg,int sockfd)
{
    char ch[LITLE_SIZE];
    int i;

        printf("please input yours user:");
        scanf("%s",msg->user);

        printf("please input yours passwd:");
        getchar();

        system("stty -icanon");
        system("stty -echo");
        for(i = 0; i < 6; i++)
        {
            ch[i] = getchar();
            msg->password[i] = ch[i];

            printf("*");
        }
        msg->password[i] = '\0';

        while((ch[i] = getchar()) != '\n')

        system("stty icanon");
        system("stty echo");

        msg->action = LOG;

        write(sockfd,msg,sizeof(Message));
}
