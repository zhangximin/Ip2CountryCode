/*
 * judyData.h
 *
 *  Created on: Jan 21, 2016
 *      Author: simon
 */

#ifndef JUDYDATA_H_
#define JUDYDATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <Judy.h>
#include "strSplit.h"
#include "ipUtils.h"
#include "timer.h"

struct pValue{
	Word_t endIp;
	char CountryCode[3];
};

extern Pvoid_t PJLArray;

extern int buildJudyData(void);
extern Word_t getJudyListCount(void);
extern void getCountryCode(char* ip,int length);
extern void destroyJudyData(void);

#endif /* JUDYDATA_H_ */
