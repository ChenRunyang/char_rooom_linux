#include "myhead.h"

int choose_c(Message *msg)
{
    char cmd[LITLE_SIZE];

    memset(cmd,0,sizeof(cmd));
    printf("please input yours cmd:");
    scanf("%s",cmd);

   if(strcmp(cmd,"reg") == 0)
   {
       msg->action = REG;

       return REG;
   }
   else if(strcmp(cmd,"log") == 0)
   {
       msg->action = LOG;

       return LOG;
   }
   else if(strcmp(cmd,"chat_one") == 0)
   {
       msg->action = CHAT_ONE;

       return CHAT_ONE;
   }
   else if(strcmp(cmd,"chat_all") == 0)
   {
       msg->action = CHAT_ALL;

       return CHAT_ALL;
   }
   else if(strcmp(cmd,"linefriend") == 0)
   {
       msg->action = CHECK_ONLINE_FRIEND;

       return CHECK_ONLINE_FRIEND;
   }
   else if(strcmp(cmd,"ban") == 0)
   {
       msg->action = BAN;

       return BAN;
   }
   else if(strcmp(cmd,"unban") == 0)
   {
       msg->action = UNBAN;

       return UNBAN;
   }
   else if(strcmp(cmd,"kick") == 0)
   {
       msg->action = KICK;

       return KICK;
   }
   else if(strcmp(cmd,"quit") == 0)
   {
       msg->action = QUIT;
       return QUIT;
   }

   return FALSE;
}
