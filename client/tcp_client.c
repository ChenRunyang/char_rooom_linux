#if 0
#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#endif

#include "myhead.h"

int flag = 0;

void * read_msg(void *arg)
{
    int sockfd = *((int *)arg);

    Message msg;

    int n_read;

    while(1)
    {
        n_read = read(sockfd,&msg,sizeof(msg));

	if(n_read == -1)
	{
	    perror("tcp_cread error!\n");
        pthread_exit(NULL);
	}

	if(n_read == 0)
	{
	    printf("the server is close!\n");
	    pthread_exit(NULL);
	}
        
	switch(msg.action)
	{
	    case REG_SUCCESS:
	    {
	        printf("reg is ok!\n");
		    break;
	    }
	    case USER_EXIST:
	    {
	        printf("reg name is exist!\n");
		    break;
	    }
        case LOG_SUCCESS:
        {
            printf("log is ok!\n");
            flag = LOG_SUCCESS;
            printf("log is ok flag = %d\n",flag);
            break;
        }
        case LOGUSER_NOT_EXIST:
        {
            printf("log user not exist,please reg before log!\n");
            break;
        }
        case PASSWD_FALSE:
        {
            printf("passwd is not correct!\n");
            break;
        }
        case FORCED_OFF_LINE:
        {
            printf("yours account log in other local place,you forced off line!\n");
            flag = FORCED_OFF_LINE;
            break;
        }
        case CHAT_ONE:
        {
            printf("%s send to me msg:%s\n",msg.user,msg.message);
            break;
        }
        case CHAT_ALL:
        {
            printf("%s send to me msg:%s\n",msg.user,msg.message);
            break;
        }
        case FRIEND_NOT_ONLINE:
        {
            printf("friend not online!\n");
            break;
        }
        case CHECK_ONLINE_FRIEND:
        {
            printf("online_friend:%s\n",msg.target);
            break;
        }
        case BAN:
        {
            printf("you have been banned by admin\n");
            flag = BAN;
            break;
        }
        case UNBAN:
        {
            printf("you have been unbanned by admin\n");
            flag = UNBAN;
            break;
        }
        case NOT_ADMIN:
        {
            printf("sorry !you are not admin,so you cannot ban anyone!\n");
            break;
        }
        case KICK:
        {
            printf("you have been kicked by admin!\n");
            printf("please enter any key return log page or quit:\n");
            flag = KICK;
            break;
        }
	}
        

    }
}
int main(int argc, char *argv[]) 
{ 
	int sockfd; 
	char buffer[1024]; 
	struct sockaddr_in server_addr; 
	int nbytes; 

        /* 使用hostname查询host 名字 */
	if(argc!=2) 
	{ 
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	} 


	/* 客户程序开始建立 sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

	/* 客户程序填充服务端的资料 */ 
	bzero(&server_addr,sizeof(server_addr)); // 初始化,置0
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  // (将本机器上的short数据转化为网络上的short数据)端口号
	
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	/* 客户程序发起连接请求 */ 
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	}

    pthread_t id;

	pthread_create(&id,NULL,read_msg,(void *)&sockfd);

    printf("id = %d\n",id);

    //Message msg;

    //memset(&msg,0,sizeof(Message));

	while(1)
	{
        interface();
        Message msg;
        switch(choose_c(&msg))
        {
            case REG:
            {
                reg(&msg,sockfd);
                break;
            }
            case LOG:
            {
                log_c(&msg,sockfd);
                sleep(1);
                if(flag == LOG_SUCCESS)
                {
                    while(1)
                    {
                        interface();
                        switch(choose_c(&msg))
                        {
                            case CHAT_ONE:
                            {
                                chat_one(&msg,sockfd);
                                break;
                            }
                            case CHAT_ALL:
                            {
                                chat_all(&msg,sockfd);
                                break;
                            }
                            case CHECK_ONLINE_FRIEND:
                            {
                                onlinefriend(&msg,sockfd);
                                break;
                            }
                            case BAN:
                            {
                                ban(&msg,sockfd);
                                break;
                            }
                            case UNBAN:
                            {
                                unban(&msg,sockfd);
                                break;
                            }
                            case KICK:
                            {
                                kick(&msg,sockfd);
                                break;
                            }
                            case QUIT:
                            {
                                exit(SUCCESS);
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                        sleep(1.5);
                        if(flag == 0 || flag == KICK || flag == FORCED_OFF_LINE)
                        {
                            break;
                        }
                    }
                }
                break;
            }
        }
    }


	close(sockfd);

	exit(0); 
} 
