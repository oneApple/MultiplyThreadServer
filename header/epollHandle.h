/*
 * epollHandle.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef EPOLLHANDLE_H_
#define EPOLLHANDLE_H_

#include</usr/include/x86_64-linux-gnu/sys/epoll.h>

#include"commonfunction/localSocketFun.h"
#include"commonfunction/netSocketFun.h"
#include"commondata/magicNum.h"
#include"commondata/dataInfo.h"
#include<unistd.h>
#include<errno.h>

#include<deque>

class handleEpollSocket{
protected:
	int _epfd;
	unsigned _maxNumOfEpollfd;
	std::deque<dataInfo*> _ddataToSend;
private:
	void getEpollFdlimit();
	void createEpollfd();
protected:
	handleEpollSocket():_maxNumOfEpollfd(magicnum::processmanage::MAXNUMPROCESS){}
	void initializeEpoll();
	void addEpollSocket(int fd);
public:
	void delEpollSocket(int fd);
	void modEpollSocket(int fd,bool rOrw);
	void packData(void *pdata);
	void sendData(int socket);
};


#endif /* EPOLLHANDLE_H_ */
