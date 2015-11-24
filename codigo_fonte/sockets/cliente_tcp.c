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
	soquete = socket(AF_INET, SOCK_STREAM, 0);
	if (soquete < 0) {
		printf("Erro ao criar o socket\n");
		exit(0);
	}
	bzero((char *) &servidor, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = inet_addr(argv[1]);
	servidor.sin_port = htons(atoi(argv[2]));
	connect(soquete, (struct sockaddr *) &servidor, sizeof(servidor));

	char str[2000];
	// strcpy(str, "GET /index.html\n\n");
	// send(soquete, str, strlen(str) + 1, 0);

	recv(soquete, str, 2000, 0);
	printf("RECEBI %s\n", str);
	
	close(soquete);
	/* code */
	return 0;
}