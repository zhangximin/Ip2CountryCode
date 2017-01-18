/*
 * timer.c
 *
 *  Created on: Jan 20, 2016
 *      Author: simon
 */

#include "timer.h"

void timerStart(void){
	gettimeofday(&tStart,NULL);
}
unsigned long timerStop(void){
	gettimeofday(&tEnd,NULL);
	return 1000000 * (tEnd.tv_sec-tStart.tv_sec)+ tEnd.tv_usec-tStart.tv_usec;
}
