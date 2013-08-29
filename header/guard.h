/*
 * guard.h
 *
 *  Created on: 2013-8-29
 *      Author: keym
 */

#ifndef GUARD_H_
#define GUARD_H_

//释放互斥锁
#include<pthread.h>
#include<stdio.h>

class guard{
private:
	pthread_mutex_t *m;
public:
	guard(pthread_mutex_t *mutex)
	{
		this->m = mutex;
		pthread_mutex_lock(this->m);
	}

	~guard()
	{
		pthread_mutex_unlock(m);
	}
};

#endif /* GUARD_H_ */
