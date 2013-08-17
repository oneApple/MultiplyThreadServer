/*
 * threadControl.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include</usr/src/linux-headers-3.2.0-51/include/linux/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>

#include"threadControl.h"

#include"socketFunction.h"
#include"errorHandle.h"
#include"configFile.h"


void threadControl::init_listenFd()
{
	if((this->_netListenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		error_fatal("threadControl::init_listenFd::14");
	}

	char port[10];
//	GetProfileString("server","port",port);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(port));
	addr.sin_addr.s_addr=INADDR_ANY;

	if(bind(this->_netListenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		error_fatal("threadControl::init_listenFd:bind");
	}
//	ListenAndSetBlockNum(this->_netListenfd,magicnum::epollhandle::MAXLISTENT);

	epollHandle::addEpollSocket(this->_netListenfd);
}

void init_epoll();
void create_threadPool(int threadnum);
void *thread_fun(void *arg);
