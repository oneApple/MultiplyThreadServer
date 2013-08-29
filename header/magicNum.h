/*
 * magicNum.h
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#ifndef MAGICNUM_H_
#define MAGICNUM_H_

#include"commonStruct.h"
//魔法数一定不要直接使用

#define CSUCCESS 0
#define CFAILED -1

enum keylen{ KEYVALLEN = 100};
#define CFGPATH "../cfg.data"

#ifdef __cplusplus

namespace magicnum{
const ssize_t SUCCESS = 0;
const ssize_t FAILED = -1;

namespace epollhandle{
const size_t MAXNUMFD = 2048;
const ssize_t MAXLISTENT = 10;
};

namespace threadcontrol{
const size_t LISTENBLOCKNUM = 10;
const ssize_t EPOLLTIMEOUT = -1;
const ssize_t MSGHEADSIZE = sizeof(msghead);
};

};

#endif
#endif /* MAGICNUM_H_ */
