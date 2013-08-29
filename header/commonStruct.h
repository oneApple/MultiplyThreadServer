/*
 * commonStruct.h
 *
 *  Created on: 2013-8-17
 *      Author: keym
 */

#ifndef COMMONSTRUCT_H_
#define COMMONSTRUCT_H_

#include</usr/include/linux/types.h>

enum _epollEvent{WEVENT = 1,REVENT};
typedef enum _epollEvent enumEpollEvent;

struct _msghead{
	size_t msgtype;
	size_t msgbodysize;
};
typedef struct _msghead msghead;


#endif /* COMMONSTRUCT_H_ */
