#include <stdio.h>
#include <wiringPi.h>

#define LED1 4
#define LED2 5

int main(void){
	if(wiringPiSetup() == -1)
		return 1;
	pinMode (LED1, OUTPUT);
	pinMode (LED2, OUTPUT);
	
	for(;;){
		digitalWrite(LED1, 1);
		digitalWrite(LED2, 1);
		
		delay(1000); // ms
	
		digitalWrite(LED1, 0);
		digitalWrite(LED2, 0);

		delay(1000);
	}
	return 0;
}
