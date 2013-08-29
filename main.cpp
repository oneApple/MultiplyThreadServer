/*
 * main.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: keym
 */
#include<stdio.h>
#include"threadControl.h"

int main()
{
	threadControl t;

	t.create_threadPool(10);
	for(;;)
		pause();
	return 0;
}
