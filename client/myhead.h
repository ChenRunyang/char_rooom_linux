
#ifndef MYHEAD_H_
#define MYHEAD_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <fcntl.h>
#include <sqlite3.h>

#define portnumber 3333
#define MAX_SIZE   1024
#define MID_SIZE   100
#define LITLE_SIZE 20

typedef struct _Message
{
    int action; /* 动作，具体的值已在宏中定义 */
    int stat;
    char message[MAX_SIZE]; /* 存放聊天的内容 */
    char user[LITLE_SIZE]; /* 存放用户名 */
    char target[LITLE_SIZE]; /* 存放聊天的目标，具体为某个在线的用户名或all */
    char password[LITLE_SIZE]; /* 存放密码 */
}Message;

typedef struct online
{
    int new_fd;
    char name[20];

    struct online *next;
}online;

extern int flag;

#define REG         0
#define REG_SUCCESS 1
#define LOG         2
#define LOG_SUCCESS 3
#define CHAT_ONE    4
#define CHAT_ALL    5
#define SUCCESS     6
#define CHECK_ONLINE_FRIEND  7
#define FRIEND_NOT_ONLINE    8
#define BAN                  10
#define KICK                 9
#define USER_EXIST -1
#define LOGUSER_NOT_EXIST -2
#define PASSWD_FALSE   -3
#define FALSE        -4
#define UNBAN        -5
#define FORCED_OFF_LINE -6
#define NOT_ADMIN       -7
#define QUIT           -8

#endif
