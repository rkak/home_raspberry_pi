#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define LED1 4
#define LED2 5

int main(){
	if(wiringPiSetup() == -1) return -1;
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	while(1){
		digitalWrite(LED1, 1);
		digitalWrite(LED2, 1);
		delay(1000);
		digitalWrite(LED1, 0);
		digitalWrite(LED2, 0);
		delay(1000);
	}

}
