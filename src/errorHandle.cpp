/*
 * errorHandle.c
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */

#include"errorHandle.h"
#include<stdio.h>
#include<stdlib.h>

void error_fatal(const char *msg)
{
	printf("fatal_error:");
	perror(msg);
	exit(0);
}

void error_normal(const char *msg)
{
	printf("fatal_error:");
	perror(msg);
}
