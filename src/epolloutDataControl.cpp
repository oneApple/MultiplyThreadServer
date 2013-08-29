/*
 * epolloutDataControl.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include"epolloutDataControl.h"
#include"guard.h"

pthread_mutex_t epolloutDataControl::lock = PTHREAD_MUTEX_INITIALIZER;

void epolloutDataControl::packData(char *pdata)
{
	guard g(&epolloutDataControl::lock);
	this->_queData.push(pdata);
}

char *epolloutDataControl::DequeData()
{
	guard g(&epolloutDataControl::lock);
	if(this->_queData.size() == 0) return 0;

	char *pdata = this->_queData.front();
	this->_queData.pop();
	return pdata;
}
