/*
 * socketFunction.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef SOCKETFUNCTION_H_
#define SOCKETFUNCTION_H_

#include</usr/src/linux-headers-3.2.0-51/include/linux/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int ListenAndSetBlockNum(int fd, int backlog) ;
int SetSocketNonblocking(int sock) ; //将文件描述符设置为非阻塞模式

#ifdef __cplusplus
}
#endif


#endif /* SOCKETFUNCTION_H_ */
