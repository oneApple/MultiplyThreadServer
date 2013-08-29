/*
 * epolloutDataControl.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef DATACONTROL_H_
#define DATACONTROL_H_
#include<deque>

class epolloutDataControl{
private:
	deque<void*> _queData;
public:
	void packData();
	void DequeData();
};

#endif /* DATACONTROL_H_ */
