#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define SERVO 1

int main(){
	char str;
	if(wiringPiSetup() == -1) return -1;

	softPwmCreate(SERVO, 0, 200);

	while(1){
		fputs("Select c,r,l,q : ", stdout);
		scanf("%c", &str);
		getchar();
		if(str=='c') softPwmWrite(SERVO, 15);	// degree 0
		else if(str=='r') softPwmWrite(SERVO, 24);	// degree 90
		else if(str=='l') softPwmWrite(SERVO, 7); 	// degree -90
		else if(str=='q') return 0;
	}
	return 0;
}

