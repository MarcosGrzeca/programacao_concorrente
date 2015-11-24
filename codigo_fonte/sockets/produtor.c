#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"

#ifndef N
#define N 60
#endif

#ifndef PORTA
#define PORTA 2727
#endif

#ifndef CONEXOES
#define CONEXOES 5
#endif

int main(int argc, char **argv)
{
	struct sockaddr_in servidor, cliente;
	int serv, clnt;
	char str[N];
	double msg;

	if (argc != 2) {
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	serv = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &servidor, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(atoi(argv[1]));
	servidor.sin_addr.s_addr = INADDR_ANY;
	
	bind(serv, (struct sockaddr *)&servidor, sizeof(servidor));

	while (1) {
		int tamanho = sizeof(cliente);
		recvfrom(serv, str, N, 0, (struct sockaddr *) &cliente, &tamanho);
		printf("Produza\n");
		sleep(1);
		strcpy(str, "Item produzido");
		sendto(serv, str, strlen(str) + 1, 0, (struct sockaddr *) &cliente, tamanho);
		close(cliente);
	}
	
	return 0;
}