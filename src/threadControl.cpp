/*
 * threadControl.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include</usr/include/linux/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>

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
	GetProfileString("server","port",port);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(port));
	addr.sin_addr.s_addr=INADDR_ANY;

	if(bind(this->_netListenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		error_fatal("threadControl::init_listenFd:bind");
	}
	ListenAndSetBlockNum(this->_netListenfd,magicnum::epollhandle::MAXLISTENT);

	epollHandle::addEpollSocket(this->_netListenfd);
}

void threadControl::init_epoll()
{
	epollHandle::initializeEpoll();
	this->init_listenFd();
}

void threadControl::create_threadPool(int threadnum)
{
	int i;
	pthread_t tid;
	for(i = 0;i < threadnum;++ i)
	{
		pthread_create(&tid,NULL,thread_fun,(void*)this);
		pthread_detach(tid);
	}
}

void *threadControl::thread_fun(void *arg)
{
	threadControl *pth = (threadControl*)arg;
	pth->communicateFun();
	return 0;
}

void threadControl::communicateFun()
{
	struct epoll_event events[this->_maxNumOfEpollfd + 1];
	int readbytes;
	char readbuf[magicnum::threadcontrol::MSGHEADSIZE];
	for(;;)
	{
		int nfds;
		if((nfds=epoll_wait(_epfd,events,this->_maxNumOfEpollfd,magicnum::threadcontrol::EPOLLTIMEOUT)) <= 0)
		{
			if (errno != EINTR)
			{
				error_fatal("threadControl::communicateFun::epoll_wait");
			}
			continue;
		}
		int i;
		for(i=0;i<nfds;i++)
		{
			int _eventfd = events[i].data.fd;
			if(_eventfd == this->_netListenfd)
			{
				int connfd;
				struct sockaddr_in clientaddr;
				socklen_t clilen = sizeof(clientaddr);
				if((connfd=accept(this->_netListenfd,(struct sockaddr*)&clientaddr,&clilen))<0)
				{
					if(errno == EINTR){continue;}
					error_fatal("threadControl::communicateFun::accept");
				}
				//不要加锁,惊群效率高
				epollHandle::addEpollSocket(connfd);
				continue;
			}
			else if(events[i].events&EPOLLIN)
			{
				memset(readbuf,0,magicnum::threadcontrol::MSGHEADSIZE);
				if((readbytes=recv(_eventfd,readbuf,magicnum::threadcontrol::MSGHEADSIZE,0)) < 0)
				{
					error_normal("threadControl::communicateFun::recv");
					//关闭或出错
					continue;
				}

				msghead *phead = (msghead*)readbuf;
				if((readbytes=recv(_eventfd,readbuf,phead->msgbodysize,0)) < 0)
				{
					error_normal("threadControl::communicateFun::recv");
					continue;
				}
				//消息处理;
			}
			else if(events[i].events&EPOLLOUT)
			{
				//通知的顺序与投递的顺序相同
				epollHandle::modEpollSocket(_eventfd,REVENT);
			}
			else if((events[i].events&EPOLLHUP)||(events[i].events&EPOLLERR))
			{
				epollHandle::delEpollSocket(_eventfd);
			}
		}
	}

}
