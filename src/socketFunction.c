/*
 * socketFunction.c
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include<stdlib.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<exception>

void ListenAndSetBlockNum(int fd, int backlog)
{
	char *ptr;
	if ((ptr = getenv("LISTENQ")) != NULL)
	{
		backlog = atoi(ptr);
	}
	if (listen(fd, backlog) < 0)
	{
		perror("listen error:");

	}
	return magicnum::SUCCESS;
}

int SetSocketNonblocking(int sock) //将文件描述符设置为非阻塞模式
{
	int opts;
	if((opts=fcntl(sock,F_GETFL)<0)){
		//perror("fcntl get");
		return magicnum::FAILIED;
	}
	opts=opts|O_NONBLOCK;
	if(fcntl(sock,F_SETFL,opts)<0){
		//perror("fcntl set");
		return magicnum::FAILIED;
	}
	return magicnum::SUCCESS;
}
