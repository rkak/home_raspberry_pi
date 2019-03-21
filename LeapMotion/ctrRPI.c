#ifndef _STDLIBRARY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <wiringPi.h>

#define LED1 4
#define LED2 5

//if error, return 1.
int ctrRPI(char * instructions, int inst_len){
	// for printing instructions
	for(int i = 0; i < inst_len; i++){
		printf("ctrRPI instructions[%d] : %c\n", i, *(instructions + i));
	}
	if(wiringPiSetup() == -1) return 1;
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);

	if(*(instructions + 0) == '1'){
		digitalWrite(LED1, 1);
	}
	else if(*(instructions + 0) == '0'){
		digitalWrite(LED1, 0);
	}
	if(*(instructions + 1) == '1'){
		digitalWrite(LED2, 1);
	}
	else if(*(instructions + 1) == '0'){
		digitalWrite(LED2, 0);
	}
	return 0;
}
