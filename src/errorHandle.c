/*
 * errorHandle.c
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include"errorHandle.h"
#include<stdio.h>
#include<stdlib.h>

int error_fatal(char *msg)
{
	printf("fatal_error:");
	perror(msg);
	exit(0);
}
