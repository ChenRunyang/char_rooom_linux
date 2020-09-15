#include "myhead.h"

extern int flag;

void interface()
{
    sleep(1);
    printf("interface flag = %d\n",flag);
    if(flag == 0 || flag == KICK)
    {
        printf("+------------------------------------+\n");
        printf("|                                    |\n");
        printf("|                                    |\n");
        printf("|         1:reg      2:log           |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
    }
    else if(flag == LOG_SUCCESS || flag == BAN || flag == UNBAN)
    {
        printf("............chat_one[群聊].。........\n");
        printf("..............chat_all[私聊].........\n");
        printf("......onlinefriend[查看在线好友].....\n");
        printf(".............ban[禁言]...............\n");
        printf(".............unban[解禁].............\n");
        printf("..............kick[踢人].............\n");
    }
}
