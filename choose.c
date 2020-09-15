
#include "myhead.h"

extern int flag;

int choose(int sockfd,Message *msg)
{
    interface();
    char cmd[LITLE_SIZE];
    int i;
    char ch[LITLE_SIZE];

    //memset(&msg,0,sizeof(msg));
    memset(cmd,0,sizeof(cmd));
    sleep(1);
    printf("please input yours choose:");
    scanf("%s",cmd);

    if(strcmp(cmd,"reg") == 0)
    {
        printf("please input account:");
        scanf("%s",msg->user);
        getchar();

        printf("please input passwd:");
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

        msg->action = REG;

        write(sockfd,msg,sizeof(Message));
    }
    else if(strcmp(cmd,"log") == 0)
    {
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
    else if(strcmp(cmd,"chat_one") == 0)
    {
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

    else if(strcmp(cmd,"chat_all") == 0)
    {
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
    else if(strcmp(cmd,"linefriend") == 0)
    {
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
    else if(strcmp(cmd,"ban") == 0)
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
            printf("please input you want ban name:");
            scanf("%s",msg->target);

            msg->action = BAN;

            write(sockfd,msg,sizeof(Message));
        }
    }
    else if(strcmp(cmd,"unban") == 0)
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
    else if(strcmp(cmd,"kick") == 0)
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
}
