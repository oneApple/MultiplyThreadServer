/*
 * epolloutDataControl.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef DATACONTROL_H_
#define DATACONTROL_H_

#include<queue>
#include<pthread.h>

class epolloutDataControl{
private:
	std::queue<char*> _queData;
	static pthread_mutex_t lock;
public:
	void packData(char *pdata);
	char* DequeData();
};

#endif /* DATACONTROL_H_ */
