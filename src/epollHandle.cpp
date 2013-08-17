/*
 * epollHandle.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

//#include</usr/include/x86_64-linux-gnu/sys/resource.h>
//#include</usr/include/x86_64-linux-gnu/sys/socket.h>
#include</usr/src/linux-headers-3.2.0-51/include/linux/socket.h>
#include</usr/include/i386-linux-gnu/sys/resource.h>

#include"epollHandle.h"

#include"socketFunction.h"
#include"errorHandle.h"
#include"commonStruct.h"

void epollHandle::getEpollFdlimit()
{
	rlimit limit;
	getrlimit(RLIMIT_NOFILE,&limit);

	if(limit.rlim_cur > magicnum::epollhandle::MAXNUMFD)
	{
		this->_maxNumOfEpollfd = limit.rlim_cur;
	}
	//描述符数目不能太大，有限制
}

void epollHandle::createEpollfd()
{
	if((this->_epfd=epoll_create(this->_maxNumOfEpollfd))<0)
	{
		error_fatal("handleEpollSocket::createEpollfd");
	}
}

void epollHandle::initializeEpoll()
{
	getEpollFdlimit();
	createEpollfd();
}

void epollHandle::addEpollSocket(int fd)
{
//	if(SetSocketNonblocking(fd) == magicnum::FAILED)
//	{
//		error_normal("handleEpollSocket::addEpollSocket");
//		return;
//	}
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
}

void epollHandle::delEpollSocket(int fd)
{
	close(fd);
	epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,NULL);
}

void epollHandle::modEpollSocket(int fd,enumEpollEvent event = WEVENT)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	switch(event)
	{
	case WEVENT:
	{
		ev.events=EPOLLOUT;
		break;
	}
	case REVENT:
	{
		ev.events=EPOLLIN;
		break;
	}
	}
	epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&ev);
}

