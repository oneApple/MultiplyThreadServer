/*
 * threadControl.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef THREADCONTROL_H_
#define THREADCONTROL_H_

#include"epollHandle.h"

class threadControl : public epollHandle{
private:
	int _netListenfd;
private:
	static void *thread_fun(void *arg);
	void init_listenFd();
	void init_epoll();
public:
	threadControl():epollHandle(){}
	void create_threadPool(int threadnum);
};

#endif /* THREADCONTROL_H_ */
