/*
 * epollHandle.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef EPOLLHANDLE_H_
#define EPOLLHANDLE_H_

#include</usr/include/x86_64-linux-gnu/sys/epoll.h>
#include<unistd.h>
#include<errno.h>

#include"magicNum.h"


class handleEpollSocket{
protected:
	int _epfd;
	unsigned _maxNumOfEpollfd;
private:
	void getEpollFdlimit();
	void createEpollfd();
protected:
	handleEpollSocket():_maxNumOfEpollfd(magicnum::epollhandle::MAXNUMFD){}
	void initializeEpoll();
	void addEpollSocket(int fd);
public:
	void delEpollSocket(int fd);
	void modEpollSocket(int fd,bool rOrw);
	void sendData(int socket);
};


#endif /* EPOLLHANDLE_H_ */
