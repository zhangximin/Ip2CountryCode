/*
 * esocket.h
 *
 *  Created on: Jan 21, 2016
 *      Author: simon
 */

#ifndef ESOCKET_H_
#define ESOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "judyData.h"

#define MAXEVENTS 64
//#define SOCKET_PORT "/tmp/ip2contry.sock"
#define SOCKET_PORT "8033"

extern int socket_start(char *PortNo);

#endif /* ESOCKET_H_ */
