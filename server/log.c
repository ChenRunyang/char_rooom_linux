#include "myhead.h"

int insert_user(online *new_user,online **head)
{
    printf("insert\n");
    new_user->next = *head;
    *head = new_user;
}
#if 0

int find_fd(char *toname)
{
    if(head == NULL)
    {
        return FALSE;
    }

    online *temp = head;
    
    while(temp != NULL)
    {
        if(strcmp(temp->name,toname) == 0)
	    {
	        return temp->fd;
	    }

	    temp = temp->next;
    }

    return FALSE;
}
#endif
int find_name(int new_fd,Message *msg,online **head)
{
    if(head == NULL)
    {
        return FALSE;
    }
    online *temp = *head;

    while(temp != NULL)
    {
        if(strcmp(msg->user,temp->name) == 0)
        {
            msg->action = FORCED_OFF_LINE;
            write(temp->new_fd,msg,sizeof(Message));

            temp->new_fd = new_fd;

            msg->action = LOG_SUCCESS;
            write(temp->new_fd,msg,sizeof(Message));

            return SUCCESS;
        }
        temp = temp->next;
    }
    return FALSE;

}

void display(online **head)
{
    printf("display\n");
    online *temp = *head;

    while(temp != NULL)
    {
        printf("temp->name = %s\n",temp->name);
        printf("temp->new_fd = %d\n",temp->new_fd);
        temp = temp->next;
    }
}

int login(sqlite3 *db, int new_fd,Message *msg,online **head)
{
    int fd;
    char sql[MID_SIZE];
    char *ErrMsg = 0;

    memset(sql,0,sizeof(sql));

    char **result = NULL;
    int rowcount;
    int columncount;
    int index;
    int ret;

    sprintf(sql,"select * from user where account = '%s';",msg->user);
    printf("sql = %s\n",sql);

    if((ret = sqlite3_get_table(db,sql,&result,&rowcount,&columncount,&ErrMsg)) != SQLITE_OK)
    {
        fprintf(stderr,"sql_get_bable error:%s\n",ErrMsg);
        
        //exit(1);
    }
    else
    {
        if(rowcount == 0)
        {
            msg->action = LOGUSER_NOT_EXIST;
            write(new_fd,msg,sizeof(Message));

            return FALSE;
        }

        index = columncount + 1;

        printf("pass = %s\n",result[index]);

        if(strcmp(msg->password,result[index]) == 0)
        {
            online *new_user = (online *)malloc(sizeof(online));
            new_user->new_fd = new_fd;

            strcpy(new_user->name,msg->user);

            if((fd = find_name(new_fd,msg,head)) == SUCCESS)
            {
                display(head);
                return SUCCESS;
            }
            else
            {
                insert_user(new_user,head);

                display(head);
                msg->action = LOG_SUCCESS;

                write(new_fd,msg,sizeof(Message));
            }
        }
        else
        {
            msg->action = PASSWD_FALSE;

            write(new_fd,msg,sizeof(Message));
        }
        
    }

    sqlite3_free_table(result);

    return 0;

}
