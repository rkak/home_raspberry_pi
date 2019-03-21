//#undef UNICODE
//#undef _UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define _STDLIBRARY

#define BUFSIZE 512
#define PORT 1999


//#define IP 192.168.0.2

extern int ctrRPI(char * instructions[], int inst_len);

void ErrorHandling(char* str){
	fputs(str, stderr);
	fputc('\n', stderr);
	exit(1);
}


// int ctrRPI(char * instructions[], int inst_len);

int main(){
	int retval;

	int sock=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serverAddr, clientAddr;
	int addrLen;
	int sAddrLen;
	char buf_rpi[BUFSIZE+1];
	char buf_server[BUFSIZE+1];

	char sendInstruction[10];

	char * recieve_ins;
	char * instructions[10];
	enum instruction {A, B, C, D, E};
	enum instruction inst = 0;
	// create Socket
	if(sock==-1)
		ErrorHandling("socket() error");

	// Bind()
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// connect()
	retval = bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if(retval == -1)
		ErrorHandling("connect() error");

	// variable using in transporting data

	for(int i = 0; i < 10; i++){
		instructions[i] = (char*)malloc(sizeof(char*));
	}

	while(1){
		 
		// recieving data
		addrLen = sizeof(clientAddr);
		retval = recvfrom(sock, buf_rpi, BUFSIZE, 0,
				(struct sockaddr *)&clientAddr, &addrLen);
		if(retval == -1){
			ErrorHandling("recvfrom() error");
			//continue;
		}
		buf_rpi[retval] = '\n';
		printf("[RPI UDP %s:%d] %s\n", inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port), buf_rpi);
		recieve_ins = strtok(buf_rpi, ",");
		while(recieve_ins != NULL){
			printf("%s\n", recieve_ins);
			strcpy(instructions[inst], (recieve_ins + 0));
			printf("instructions[%d] : %c\n", inst, instructions[inst]);
			inst++;
			recieve_ins = strtok(NULL, ",");
		}

		/*
		// for test of ctrRPI. LED on and servo motor
		strcpy(instructions[0],"1");
		strcpy(instructions[1],"0");
		strcpy(instructions[2],"0");
		strcpy(instructions[3],"0");
		strcpy(instructions[4],"0");
		strcpy(instructions[5],"1");
		strcpy(instructions[6],"000000");
		*/

		inst = 0;

		
		/* for test
		for(int i=0; i<7; i++){
			printf("%d : %s\n", i,  instructions[i]);
		}
		*/

		// run control raspberry pi.
		
		if(ctrRPI(instructions, inst) == -1)
			return 0;

		inst = 0;
		// printf("2\n");
		// send data. now it doesn't work
		sendInstruction[0] = '1';
		strcpy(buf_server, sendInstruction);
		printf("clientaddr : %s\n", inet_ntoa(clientAddr.sin_addr));
		retval = sendto(sock, buf_server, BUFSIZE, 0,
				(struct sockaddr *)&clientAddr, sizeof(clientAddr));
		if(retval == -1){
			ErrorHandling("sendto() eror");
		}
	}
	
	close(sock);

	return 0;
}
