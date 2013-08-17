/*
 * configFile.h
 *
 *  Created on: 2013-8-17
 *      Author: keym
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#ifdef __cplusplus
extern "C" {
#endif

int GetProfileString(const char *AppName,const char *KeyName,char *KeyVal );

#ifdef __cplusplus
}
#endif


#endif /* CONFIGFILE_H_ */
