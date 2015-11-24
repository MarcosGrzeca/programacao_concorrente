#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"

int main(int argc, char const *argv[])
{
	struct sockaddr_in servidor;

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
	strcpy(str, "ping\n");
	sendto(soquete, str, strlen(str) + 1, 0, (struct sockaddr *) &servidor, sizeof(servidor));
	recvfrom(soquete, str, 2000, 0, NULL, NULL);
	printf("%s\n", str);
	close(soquete);
	/* code */
	return 0;
}