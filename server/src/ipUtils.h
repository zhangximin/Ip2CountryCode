/*
 * ipUtils.h
 *
 *  Created on: Jan 20, 2016
 *      Author: simon
 */

#ifndef IPUTILS_H_
#define IPUTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

extern char *ip2str(unsigned long ip);
extern unsigned long ip2long(char *ip);

#endif /* IPUTILS_H_ */
