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
	int connfd;
	int readbytes;
	char readbuf[magicnum::epollhandle::MAXNUMFD];
	for(;;)
	{
		int nfds;
		if((nfds=epoll_wait(_epfd,events,this->_maxNumOfEpollfd,magicnum::parentprocess::EPOLLTIMEOUT)) <= 0)
		{
			if (errno != EINTR)
			{
				std::cerr<<"parentProcess::CommunicationHandle:epoll_wait"<<std::endl;
				throw std::exception();
			}
			continue;
		}
		int i;
		for(i=0;i<nfds;i++)
		{
			if(events[i].data.fd == this->_netListenfd)
			{
				struct sockaddr_in clientaddr;
				socklen_t clilen = sizeof(clientaddr);
				if((connfd=accept(this->_netListenfd,(struct sockaddr*)&clientaddr,&clilen))<0)
				{
					if(errno == EINTR){continue;}
					std::cerr<<"parentProcess::CommunicationHandle:accept"<<std::endl;
					throw std::exception();
				}
				this->acceptNewConnection(connfd);
				continue;
			}
			else if(events[i].events&EPOLLIN)
			{
				memset(readbuf,0,magicnum::MSGHEADSIZE);
				int _childSocketfd = events[i].data.fd;
				if((readbytes=RepeatRecv(_childSocketfd,readbuf,sizeof(commontype::headInfo))) == magicnum::FAILIED)
				{
					this->relEpollSocket(_childSocketfd,ERR);
					continue;
				}
				messageHandle::getInstance()->msgHandle(readbuf,_childSocketfd,this);
			}
			else if(events[i].events&EPOLLOUT)
			{
				//通知的顺序与投递的顺序相同
				handleEpollSocket::sendData(events[i].data.fd);
				if(this->_dnewConnectSocket.size() != 0)
				{
					this->sendNewConnection(events[i].data.fd);
				}
				handleEpollSocket::modEpollSocket(events[i].data.fd,false);
			}
			else if((events[i].events&EPOLLHUP)||(events[i].events&EPOLLERR))
			{
				this->relEpollSocket(events[i].data.fd,ERR);
			}
		}
	}

}
