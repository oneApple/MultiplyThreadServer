/*
 * epollHandle.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include</usr/include/x86_64-linux-gnu/sys/resource.h>
#include</usr/include/x86_64-linux-gnu/sys/socket.h>

#include<unistd.h>
#include<exception>
#include<iostream>
#include<stdio.h>
#include"handleEpollSocket.h"
#include"commondata/commontype.h"
#include"mempool/fixmemorypool.h"
#include"mempool/mempool.h"

static bool flag = true;

void handleEpollSocket::getEpollFdlimit()
{
	rlimit limit;
	getrlimit(RLIMIT_FSIZE,&limit);
	if(limit.rlim_cur > magicnum::processmanage::MAXNUMPROCESS)
	{
		this->_maxNumOfEpollfd = limit.rlim_cur;
	}
	this->_maxNumOfEpollfd = 2048;
	//描述符数目不能太大，有限制
}

void handleEpollSocket::createEpollfd()
{
	if((this->_epfd=epoll_create(this->_maxNumOfEpollfd))<0)
	{
		perror("epoll_create:");
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:epoll_create"<<this->_maxNumOfEpollfd<<std::endl;
		throw std::exception();
	}
}

void handleEpollSocket::initializeEpoll()
{
	getEpollFdlimit();
	createEpollfd();
}

void handleEpollSocket::addEpollSocket(int fd)
{
	if(SetSocketNonblocking(fd) == magicnum::FAILIED)
	{
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:SetSocketNonblocking"<<std::endl;
		throw std::exception();
	}
	struct epoll_event ev;
	ev.data.fd=fd;
	//ev.events=EPOLLIN|EPOLLET;
	ev.events=EPOLLIN;
	epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
}

void handleEpollSocket::delEpollSocket(int fd)
{
	close(fd);
	epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,NULL);
}

void handleEpollSocket::modEpollSocket(int fd,bool rTow)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	//ev.events=EPOLLIN|EPOLLET;
	if(rTow)
	{
		ev.events=EPOLLOUT|EPOLLET;
	}
	epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&ev);
}

void handleEpollSocket::packData(void *pdata)
{
	this->_ddataToSend.push_back((dataInfo*)pdata);
}

void handleEpollSocket::sendData(int sendfd)
{
	dataInfo *pdataInfo = this->_ddataToSend[0];
	this->_ddataToSend.pop_front();
	if(RepeatSend(sendfd,pdataInfo->_pdata,pdataInfo->_size) == magicnum::FAILIED)
	{
		if(flag)
		{
			flag = false;
			perror("handleEpollSocket::sendData");
		}
	}
	//delete []pdataInfo->_pdata;
	MemPool::getInstance()->freeMem(pdataInfo->_pdata);
	delete pdataInfo;
	//fixmemorypool<dataInfo>::getInstance()->mem_pool_release(pdataInfo);
}
