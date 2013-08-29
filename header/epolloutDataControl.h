/*
 * epolloutDataControl.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef DATACONTROL_H_
#define DATACONTROL_H_

#include<map>
#include<pthread.h>
#include"commonStruct.h"

class epolloutDataControl{
private:
	std::multimap<int,msgdata*> _mapData;
	static pthread_mutex_t lock;
public:
	void packData(int sockfd,int datasize,char *pdata);
	msgdata* DequeData(int sockfd);
};

#endif /* DATACONTROL_H_ */
