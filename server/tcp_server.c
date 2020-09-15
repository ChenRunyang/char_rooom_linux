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

online *head = NULL;

void * read_msg(void *arg)
{
    int new_fd = *((int *)arg);
    int ret;
    sqlite3 *db;
    char *ErrMsg;
    char sql[MID_SIZE];

    if((ret = sqlite3_open("user.db",&db)) != SQLITE_OK)
    {
        fprintf(stderr,"user.db open error:%s\n",sqlite3_errmsg(db));
        exit(1);
    }

    //printf("link success!\n");

    memset(sql,0,sizeof(sql));

    sprintf(sql,"create table user(account text primary key,passwd text);");

    if((ret = sqlite3_exec(db,sql,0,0,&ErrMsg)) != SQLITE_OK)
    {
        fprintf(stderr,"create user table error:%s\n",ErrMsg);
        sqlite3_free(ErrMsg);
    }

    Message msg;

    //struct online * new_user;

    int n_read;
    int find_fd;

    while(1)
    {
        memset(sql,0,sizeof(sql));
        n_read = read(new_fd,&msg,sizeof(msg));

	    if(n_read == -1)
	    {
	        perror("tcp_sread error!\n");
            pthread_exit(NULL);
	    }

	    if(n_read == 0)
	    {
	        printf("the client is close!\n");
	        pthread_exit(NULL);
	    }

	    switch(msg.action)
	    {
	        case REG:
	        {
                 sprintf(sql,"insert into user(account,passwd) values('%s','%s');",msg.user,msg.password);

                 if((ret = sqlite3_exec(db,sql,NULL,NULL,&ErrMsg)) != SQLITE_OK)
                 {
                     fprintf(stderr,"insert user error:%s\n",ErrMsg);
                     msg.action = USER_EXIST;
                     write(new_fd,&msg,sizeof(msg));
                 }
                 else
                 {
                     msg.action = REG_SUCCESS;
                     write(new_fd,&msg,sizeof(msg));
                 }

                 //check name; "select * from user where name = 'msg.name'";
		         //Y:msg.action = -1; write(fd,&msg,sizeof(msg));
                 //N:"insert into user(name,passwd) values('msg.name','msg.passwd')"
		        break;
	        }
            case LOG:
            {
                login(db,new_fd,&msg,&head);
            }
            case CHAT_ONE:
            {
                pack_msg(new_fd,&head,&msg);
                break;
            }
            case CHAT_ALL:
            {
                pack_msg(new_fd,&head,&msg);
                break;
            }
            case CHECK_ONLINE_FRIEND:
            {
                onlinefriend(&msg,new_fd,&head);
                break;
            }
            case BAN:
            {
                stat(&msg,new_fd,&head);
                break;
            }
            case UNBAN:
            {
                printf("unban = %d\n",msg.action);
                stat(&msg,new_fd,&head);
                break;
            }
            case KICK:
            {
                stat(&msg,new_fd,&head);
                break;
            }
            /*
            case QUIT:
            {
                printf("sb\n");
                out_online(&head,&msg,new_fd);
                break;
            }
            */
#if 0
	        case 2:
	        {
	            //check reg:"select * from user where name = 'msg.name'"
		        //N:msg.action = -2; write(fd,&msg,sizeof(msg));
		        //Y:check passwd:"select passwd from user where name = 'msg.name'"
		        //strcmp(passwd,'msg.passwd') == 0;
		        //N:msg.action = -3; write(fd,&msg,sizeof(msg));
		        //Y:check log:"select new_fd from online where name = 'msg.name'"
		        //Y:msg.action = -4;write(new_fd,&msg,sizeof(msg));
		        //N:log:insert into online(new_fd,name) values(fd,msg.name);
		        //msg.action = 2,write(fd,&msg,sizeof(msg));
		
                 new_user = (struct online *)malloc(sizeof(struct online));
		         new_user->fd = fd;
		         strcpy(new_user->name,msg.name);

		         insert_user(new_user);
                 

		         msg.action = 2;

		         write(fd,&msg,sizeof(msg));

		         break;
	        }

	        case 3:
	    {
	        int to_fd = find_fd(msg.toname);

		if(to_fd == -1)
		{
		    msg.action = -5;

		    write(fd,&msg,sizeof(msg));
		}
		else
		{
		    msg.action = 3;

		    write(to_fd,&msg,sizeof(msg));
		}
	    }
#endif
	}

    }
}

int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	pthread_t id;
	int opt = 1;

	/* 服务器端开始建立sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
    { 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	//server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port=htons(portnumber);         // (将本机器上的short数据转化为网络上的short数据)端口号
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	/* 捆绑sockfd描述符到IP地址 */ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/* 设置允许连接的最大客户端数 */ 
	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	while(1) 
	{ 
		/* 服务器阻塞,直到客户程序建立连接 */ 
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		} 
		fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr)); // 将网络地址转换成.字符串
	        
        pthread_create(&id,NULL,read_msg,(void *)&new_fd);

		/* 循环下一个 */ 
	} 

	/* 结束通讯 */ 
	close(sockfd); 
	exit(0); 
} 
