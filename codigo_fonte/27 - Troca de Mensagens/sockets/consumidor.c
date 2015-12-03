#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"

#ifndef N
#define N 10
#endif

int main(int argc, char const *argv[])
{
	int i;
	struct sockaddr_in servidor;
	double msg = 0;

	if (argc != 3) {
		printf("%s <ip> <porta>\n", argv[0]);
		exit(0);
	}

	int soquete;
	soquete = socket(AF_INET, SOCK_DGRAM, 0);
	if (soquete < 0) {
		printf("Erro ao criar o socket\n");
		exit(0);
	}
	bzero((char *) &servidor, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = inet_addr(argv[1]);
	servidor.sin_port = htons(atoi(argv[2]));

	char str[2000];
	strcpy(str, "");
	for (i = 0; i < N; i ++) {
		msg = i;
		sendto(soquete, &msg, sizeof(msg), 0, (struct sockaddr *) &servidor, sizeof(servidor));	
	}
	while (1) {
		recvfrom(soquete, &msg, sizeof(double), 0, NULL, NULL);
		printf("Recebi o item %f \n", msg);
		sendto(soquete, &msg, sizeof(double), 0, (struct sockaddr *) &servidor, sizeof(servidor));	
	}
	
	
	
	close(soquete);
	/* code */
	return 0;
}