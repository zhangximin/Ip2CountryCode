/*
 * ipUtils.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: simon
 */

#include "ipUtils.h"

#define IS_SPACE(c)  (c == ' ' || c == '\t' || c == '\r')

char * fasttrim(char * str)
{
        char * start, * end = NULL;

        if(str == NULL)
                return NULL;

        //去掉头部的空格字符
        while( IS_SPACE(*str) ) str++;

        //start赋值，循环
        for(start = str; *str != '\0'; str++)
        {
                if ( IS_SPACE(*str) )
                {
                        //遇到非连续的第一个空格，上个位置就是可能的尾部
                        end = str++;

                        //去掉接下来连续的空格
                        while( IS_SPACE(*str) ) str++;

                        //没有到尾，还有其他的字符，上次记录的尾部无效
                        if(*str != '\0')
                                end = NULL;                //invalid end
                }
        }

        if(end) *end = '\0';

        return start;
}

char *ip2str(unsigned long ip) {
	ip = htonl(ip);
	struct in_addr addr;
	memcpy(&addr, &ip, 4);
	return inet_ntoa(addr);
}

///**
// *	Return value need to free.
// */
//char *ip2strEx(unsigned long ip) {
//	char *reValue = (char *)malloc(sizeof(char)*15);
//	union {
//		unsigned long ipLong;
//		unsigned char bytes[4];
//	}IPS;
//	IPS.ipLong = ip;
//	sprintf(reValue,"%d.%d.%d.%d",IPS.bytes[3],IPS.bytes[2],IPS.bytes[1],IPS.bytes[0]);
//	return reValue;
//}

unsigned long ip2long(char *ip) {
	ip = fasttrim(ip);
	return inet_network(ip);
}
//unsigned long ip2longEx(char *ip) {
//	ip = fasttrim(ip);
//	struct in_addr inp;
//	inet_aton(ip,&inp);
//	return ntohl(inp.s_addr);
//}

//int main(void){
//	printf("52.0.0.0:%lu\n",ip2long("52.0.0.0"));
////	printf("52.0.0.0:%lu\n",ip2longEx("52.0.0.0"));
//	char *t = ip2strEx(872415232);
//	printf("872415232:%s\n",t);
//	if(t)
//		free(t);
////	printf("52.31.255.124:%lu\n",ip2long("52.31.255.124"));
////	printf("52.31.255.124:%lu\n",ip2longEx("52.31.255.124"));
//
//	return 0;
//}
