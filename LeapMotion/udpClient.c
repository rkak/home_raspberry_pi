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

extern int ctrRPI(char * instructions, int inst_len);

void ErrorHandling(char* str){
	fputs(str, stderr);
	fputc('\n', stderr);
	exit(1);
}

int ctrRPI(char * instructions, int inst_len);

int main(){
	int retval;

	int sock=socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serverAddr, clientAddr;
	int addrLen;
	char buf_rpi[BUFSIZE+1];
	char * recieve_ins;
	char instructions[10];
	enum instruction {A, B, C, D, E};
	enum instruction inst = 0;
	// create Socket
	if(sock==-1)
		ErrorHandling("socket() error");

	// Bind()
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);;

	// connect()
	retval = bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if(retval == -1)
		ErrorHandling("connect() error");

	// variable using in transporting data

	while(1){
		// recieving data
		addrLen = sizeof(clientAddr);
		retval = recvfrom(sock, buf_rpi, BUFSIZE, 0,
				(struct sockaddr *)&clientAddr, &addrLen);
		if(retval == -1){
			ErrorHandling("recvfrom() error");
			continue;
		}
		buf_rpi[retval] = '\n';
		printf("[RPI UDP %s:%d] %s\n", inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port), buf_rpi);
		recieve_ins = strtok(buf_rpi, ",");
		while(recieve_ins != NULL){
			printf("%s\n", recieve_ins);
			instructions[inst] = *(recieve_ins + 0);
			printf("instructions[%d] : %c\n", inst, instructions[inst]);
			inst++;
			recieve_ins = strtok(NULL, ",");
		}
		ctrRPI(instructions, inst);
		inst = 0;
	}
	
	close(sock);

	return 0;
}
