#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"

int main(int argc, char const *argv[])
{
	struct sockaddr_in servidor;
	int soquete;
	soquete = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &servidor, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(80);
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(soquete, (struct sockaddr *) &servidor, sizeof(servidor));

	char str[2000];
	strcpy(str, "GET /index.html\n\n");
	send(soquete, str, strlen(str) + 1, 0);

	recv(soquete, str, 2000, 0);
	printf("RECEBI %s\n", str);
	
	close(soquete);
	/* code */
	return 0;
}