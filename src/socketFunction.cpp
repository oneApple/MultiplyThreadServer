/*
 * socketFunction.c
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include<stdlib.h>
//#include</usr/include/linux/socket.h>
#include</usr/include/i386-linux-gnu/sys/socket.h>
#include<fcntl.h>

#include"errorHandle.h"
#include"magicNum.h"

void ListenAndSetBlockNum(int fd, int backlog)
{
	char *ptr;
	if ((ptr = getenv("LISTENQ")) != NULL)
	{
		backlog = atoi(ptr);
	}
	if (listen(fd, backlog) < 0)
	{
		error_fatal("socketFunction.c:ListenAndSetBlockNum");
	}
}

int SetSocketNonblocking(int sock) //将文件描述符设置为非阻塞模式
{
	int opts;
	if((opts=fcntl(sock,F_GETFL)<0)){
		return CFAILED;
	}
	opts=opts|O_NONBLOCK;
	if(fcntl(sock,F_SETFL,opts)<0){
		return CFAILED;
	}
	return CFAILED;
}
