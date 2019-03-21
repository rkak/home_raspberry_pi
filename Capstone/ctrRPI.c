#ifndef _STDLIBRARY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <wiringPi.h>
#include <softPwm.h>

#define LED1 4
#define LED2 5
#define LED3 6 
#define LED4 26
#define LED5 27
#define LED6 28

#define SERVO1 21
#define SERVO2 22

#define STEP1 23

#define PINCH 0
#define CW 1
#define CCW 2
#define LS 3
#define RS 4
#define COMPONENT 5
#define STATUS 6

#define PINCH_ON 1
#define PINCH_OFF 0
#define CW_ON 1
#define CW_OFF 0
#define CCW_ON 1 
#define CCW_OFF 0
#define LS_ON 1
#define LS_OFF 0
#define RS_ON 1
#define RS_OFF 0

// when pinch is on, it execute. if it fail to execute, return -1, else return 0
int doPinch(int component, int status);
// void undoPinch();

int doCw(int component, int status);
// void undoCw();

int doCcw(int component, int status);
// void undoCcw();

int doLs(int component, int status);
// void undoLs();

int doRs(int component, int status);
// void undoRs();

// void undo();

void moveServo();
int ledOn(int status);
int servoOn(int status);

//if error, return -1.
int ctrRPI(char * instructions[], int inst_len){
	// for printing instructions
	int pinch = 0;
	int cw = 0;
	int ccw = 0;
	int ls = 0;
	int rs = 0;
	int compo = 0;
	int status = 0;

	pinch = atoi(instructions[0]);
	cw = atoi(instructions[1]);
	ccw = atoi(instructions[2]);
	ls = atoi(instructions[3]);
	rs = atoi(instructions[4]);
	compo = atoi(instructions[5]);
	status = atoi(instructions[6]);

	if(wiringPiSetup() == -1) return -1;

	softPwmCreate(SERVO1, 0, 200);

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(LED5, OUTPUT);
	pinMode(LED6, OUTPUT);

	for(int i=0;i<7;i++){
		printf("instructions in ctrRPI %d : %s\n", i, instructions[i]);
	}

	printf("pinch_on : %d\n", pinch);	
	if(pinch == 1){
		doPinch(compo, status);
	}else if(strcmp(*(instructions + PINCH), "0") == 0){
//		undoPinch();
	}
	
	if(strcmp(*(instructions + CW), "1") == 0){
		doCw(compo, status);
	}else if(strcmp(*(instructions + CW), "0") == 0){
//		undoCw();
	}
	
	if(strcmp(*(instructions + CCW), "1") == 0){
		doCcw(compo, status);
	}else if(strcmp(*(instructions + CCW), "0") == 0){
//		undoCcw();
	}
	
	if(strcmp(*(instructions + LS), "1") == 0){
		doLs(compo, status);
	}else if(strcmp(*(instructions + LS), "0") == 0){
//		undoLs();
	}
	
	if(strcmp(*(instructions + RS), "1") == 0){
		doRs(compo, status);
	}else if(strcmp(*(instructions + RS), "0") == 0){
//		undoRs();
	}

	return 0;
}

// Servo. need some arguments
void moveServo(){
//	softPwmCreate(SERVO, 0, 200);

//	while(1){
//		softPwmWrite(SERVO, 15);
//	}
}

int doPinch(int component, int status){
	printf("doPinch compo : %d, status : %d\n", component, status);
	switch(component){
		case 1: ledOn(000000); // for initialization 
			ledOn(status); 
			break;
		case 2: 
			// status must be 0
			if(status != 0){
				printf("Error! Wrong status_doPinch()\n");
				break;
			}
			servoOn(status);
			break;
		case 3:
			ledOn(status);
			break;
		default:
			printf("Error! Wrong component_doPinch()\n");
			return -1;
	}	
}

int ledOn(int status){
	short led1 = 0;
	short led2 = 0;
	short led3 = 0;
	short led4 = 0;
	short led5 = 0;
	short led6 = 0;

	led1 = status / 100000;
	status -= (led1 * 100000);
	led2 = status / 10000;
	status -= (led2 * 10000);
	led3 = status / 1000;
	status -= (led3 * 1000);
	led4 = status / 100;
	status -= (led4 * 100);
	led5 = status / 10;
	status -= (led5 * 10);
	led6 = status / 1;
	status -= (led6 * 1);

	digitalWrite(LED1, led1);
	digitalWrite(LED2, led2);
	digitalWrite(LED3, led3);
	digitalWrite(LED4, led4);
	digitalWrite(LED5, led5);
	digitalWrite(LED6, led6);

	// for checking LED on
	printf("LED on!\n");
	/*
	printf("LED1 : %d\n", led1);
	printf("LED2 : %d\n", led2);
	printf("LED3 : %d\n", led3);
	printf("LED4 : %d\n", led4);
	printf("LED5 : %d\n", led5);
	printf("LED6 : %d\n", led6);
	*/
	return 1; // right executation
}


/*
void undoPinch(){
	digitalWrite(LED1, 0);
	digitalWrite(LED2, 0);
	digitalWrite(LED3, 0);
	digitalWrite(LED4, 0);
	digitalWrite(LED5, 0);
	digitalWrite(LED6, 0);
}
*/

int doCw(int component, int status){
	switch(component){
		case 1:
			break;
		case 2:
			// status must be 1
			if(status != 1){
				printf("Error! Wrong status_doCw()\n");
				break;
			}
			servoOn(status);
			break;
		default :
			printf("Error! Wrong component_doCw()\n");
			return -1;
	}	

}

int servoOn(int status){
	printf("servoOn - status : %d\n", status);
	//delay(1000);
	switch(status){
		case 0 :
		       printf("softPwmWrie servo1,15\n");	
			softPwmWrite(SERVO1, 15); // degree 0
			break;
		case 1 :
			softPwmWrite(SERVO1, 24); // degree 90
			break;
		case 2 :
			softPwmWrite(SERVO1, 7); // degree -90
			break;
		default :
			printf("Error! wrong status_servoOn()\n");
			return -1;
	}
	//delay(1000);
}

/*
void undoCw(){

}
*/

int doCcw(int component, int status){
	switch(component){
		case 1:
			break;
		case 2:
			// status must be 2
			if(status != 2){
				printf("Error! Wrong status_doCcw()\n");
				break;
			}
			servoOn(status);
			break;
		default :
			printf("Error! Wrong component_doCcw()\n");
			return -1;
	}	
}

/*
void undoCcw(){

}
*/

int doLs(int component, int status){
	switch(component){
		case 1:
		       	ledOn(000000);
			ledOn(100000);
			delay(1000);
			ledOn(010000);
			delay(1000);
			ledOn(001000);
			delay(1000);
			ledOn(000100);
			delay(1000);
			ledOn(000010);
			delay(1000);
			ledOn(000001);
			delay(1000);
			ledOn(000000);
			break;
		case 2:
			break;
		default :
			printf("Error! Wrong component_doLs()\n");
			return -1;
	}	
}

/*
void undoLs(){

}
*/

int doRs(int component, int status){
	switch(component){
		case 1:
		       	ledOn(000000);
			ledOn(000001);
			delay(1000);
			ledOn(000010);
			delay(1000);
			ledOn(000100);
			delay(1000);
			ledOn(001000);
			delay(1000);
			ledOn(010000);
			delay(1000);
			ledOn(100000);
			delay(1000);
			ledOn(000000);
			break;
		case 2:
			break;
		default :
			printf("Error! Wrong component_doRs()\n");
			return -1;
	}	
}


/*
void undoRs(){

}

void undo(){
	undoPinch();
	undoCw();
	undoCcw();
	undoLs();
	undoRs();
}
*/
