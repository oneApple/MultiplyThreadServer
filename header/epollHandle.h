/*
 * epollHandle.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef EPOLLHANDLE_H_
#define EPOLLHANDLE_H_

//#include</usr/include/x86_64-linux-gnu/sys/epoll.h>
#include</usr/include/i386-linux-gnu/sys/epoll.h>
#include<unistd.h>
#include<errno.h>

#include"magicNum.h"
#include"commonStruct.h"


class epollHandle{
protected:
	int _epfd;
	unsigned _maxNumOfEpollfd;
private:
	void getEpollFdlimit();
	void createEpollfd();
protected:
	epollHandle():_maxNumOfEpollfd(magicnum::epollhandle::MAXNUMFD){}
	void initializeEpoll();
public:
	void addEpollSocket(int fd);
	void delEpollSocket(int fd);
	void modEpollSocket(int fd,enumEpollEvent event);
};


#endif /* EPOLLHANDLE_H_ */
