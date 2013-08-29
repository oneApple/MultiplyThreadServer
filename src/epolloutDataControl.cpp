/*
 * epolloutDataControl.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include"epolloutDataControl.h"
#include"guard.h"
#include<stdlib.h>

pthread_mutex_t epolloutDataControl::lock = PTHREAD_MUTEX_INITIALIZER;

void epolloutDataControl::packData(int sockfd,int datasize,char *pdata)
{
	guard g(&epolloutDataControl::lock);
	msgdata *pmsg = (msgdata*)malloc(sizeof(msgdata));
    pmsg->datasize = datasize;
    pmsg->databuf = pdata;
	this->_mapData.insert(std::pair<int, msgdata*>(sockfd, pmsg));
}

msgdata *epolloutDataControl::DequeData(int sockfd)
{
	guard g(&epolloutDataControl::lock);

	std::map<int,msgdata*>::iterator iter = this->_mapData.find(sockfd);
	if(iter == this->_mapData.end()) return 0;
	msgdata *pmsg = iter->second;
	printf("dequeue:%d,%d\n",*(int*)pmsg->databuf,pmsg->datasize);
	this->_mapData.erase(iter);
	return pmsg;
}
