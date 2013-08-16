/*
 * errorHandle.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef ERRORHANDLE_H_
#define ERRORHANDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

int ListenAndSetBlockNum(int fd, int backlog) ;
int SetSocketNonblocking(int sock) ; //将文件描述符设置为非阻塞模式

#ifdef __cplusplus
}
#endif

#endif /* ERRORHANDLE_H_ */
