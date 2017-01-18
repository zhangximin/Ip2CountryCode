/*
 ============================================================================
 Name        : t3.c
 Author      : Simon Cheung
 Version     :
 Copyright   : Copy Left.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(argc == 3) {
		if (!strcmp(argv[2],"debug"))
			setbuf(stdout,NULL);
	}

	if (buildJudyData()) {
		printf("load data error!");
		destroyJudyData();
		return EXIT_FAILURE;
	}

	printf("Ip2Country Service Listening at port:%s \n",argv[1]);
	socket_start(argv[1]);

	destroyJudyData();
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
