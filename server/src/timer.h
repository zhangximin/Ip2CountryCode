/*
 * timer.h
 *
 *  Created on: Jan 20, 2016
 *      Author: simon
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <sys/time.h>

struct timeval tStart;
struct timeval tEnd;

extern void timerStart(void);
extern unsigned long timerStop(void);

#endif /* TIMER_H_ */
