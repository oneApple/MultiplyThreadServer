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

void error_fatal(const char *msg);
void error_normal(const char *msg);

#ifdef __cplusplus
}
#endif

#endif /* ERRORHANDLE_H_ */
