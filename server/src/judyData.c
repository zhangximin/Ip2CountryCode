/*
 * judyData.c
 *
 *  Created on: Jan 21, 2016
 *      Author: simon
 */

#include "judyData.h"

Pvoid_t PJLArray = (Pvoid_t) NULL; // initialize JudyL array

void out_of_memory(void) {
	printf("Fatal error:Out of memory!");
	exit(EXIT_FAILURE);
}

void initData(FILE *ffp) {

	Word_t Index;                     // array index
	Word_t Value = 0;                     // array element value
	Word_t * PValue;                    // pointer to array element value

	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	if (ffp == NULL)
		return;

	while ((read = getline(&line, &len, ffp)) != -1) {

//		printf("Retrieved line of length %zu :\n", read);
//		printf("%s", line);

		if (line != NULL && strstr(line, "|") > 0) {
			char** tokens;
			tokens = str_split(line, '|');
			if (tokens) {
				int i;
				char ipStart[16];
				int skip = 0;
				struct pValue *v = malloc(sizeof(struct pValue));
				for (i = 0; *(tokens + i); i++) {
					if (i == 1) {
						if (strncmp(*(tokens + i), "*",1) && strncmp(*(tokens + i), "#",1))
							strncpy(v->CountryCode, *(tokens + i),2);
						else
							skip = 1;
					}
					if (i == 2 && skip == 0) {
						if (strncmp(*(tokens + i), "ipv4", 4))
							skip = 1;
					}
					if (i == 3 && skip == 0) {
						if (strcmp(*(tokens + i), ".") > 0)
							strcpy(ipStart, *(tokens + i));
						else
							skip = 1;
					}
					if (i == 4 && skip == 0) {
						v->endIp = strtol(*(tokens + i), NULL, 10);
					}
					if (i == 6 && skip == 0) {
						if (!strncmp(*(tokens + i), "allocated",9) || !strncmp(*(tokens + i), "assigned",8)) {
							Index = ip2long(ipStart);
							v->endIp += Index;
							Value = (Word_t) v;
						} else
							skip = 1;
					}
					free(*(tokens + i));
				}
				if (skip == 0) {
					JLI(PValue, PJLArray, Index);
					if (PValue == PJERR)
						//goto process_malloc_failure;
						out_of_memory();
					*PValue = Value;                 // store new value
				} else
					free(v);
				free(tokens);
			}
		}
	}

	if (line)
		free(line);
}

int buildJudyData(void) {
	char *filenames[5] = { "./delegated-afrinic-extended-latest", "./delegated-apnic-extended-latest",
			"./delegated-arin-extended-latest", "./delegated-lacnic-extended-latest",
			"./delegated-ripencc-extended-latest" };
	int i;
	for (i = 0; i < 5; i++) {
		FILE * fp;
		fp = fopen(filenames[i], "r");
		initData(fp);
		fclose(fp);
	}

	if (PJLArray == NULL) {
		printf("No data find!\n");
		return -1;
	}
	return 0;
}

Word_t getJudyListCount(void) {
	//print data count
	Word_t Rc_word;
	JLC(Rc_word, PJLArray, 0, -1);
	//printf("Records:%lu\n",Rc_word);
	return Rc_word;
}

void getCountryCode(char* ip,int bufferSize) {
	Word_t Index;                     // array index
	Word_t * PValue;                    // pointer to array element value
	int finded = 0;

	// Next, visit all the stored indexes in sorted order, first ascending,
	// then descending, and delete each index during the descending pass.
	timerStart();

	Word_t ipl = ip2long(ip);
	memset(ip,0,bufferSize);
	//printf("ipl:%lu\n",ipl);

	Index = 0;
	JLF(PValue, PJLArray, Index);
	while (PValue != NULL) {
		//printf("%lu %lu\n", Index, *PValue);
		if (ipl >= Index) {
			struct pValue *tp = (struct pValue *) *PValue;
			if (tp->endIp >= ipl) {
				//printf("find:%lu %s\n", Index, tp->CountryCode);
				strncpy(ip, tp->CountryCode, 2);
				strcat(ip,"\n");
				finded = 1;
				break;
			}
		}
		JLN(PValue, PJLArray, Index);
	}
	if(finded)
		printf("Time for find %lu us\n", timerStop());
	else
		strcpy(ip,"NOTFOUND\n");
}

void destroyJudyData(void) {
	Word_t Index;                     // array index
	Word_t * PValue;                    // pointer to array element value
	int Rc_int;                    // return code
	Index = -1;
	JLL(PValue, PJLArray, Index);
	while (PValue != NULL) {
		//printf("%lu %lu\n", Index, *PValue);
		struct pValue *p = (struct pValue *) *PValue;
		if (p != NULL)
			free(p);
		JLD(Rc_int, PJLArray, Index);
		if (Rc_int == JERR)
			//goto process_malloc_failure;
			out_of_memory();

		JLP(PValue, PJLArray, Index);
	}
}
