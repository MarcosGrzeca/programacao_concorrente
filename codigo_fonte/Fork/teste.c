#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int id1, id2, id3, id4;

	id1 = fork();
	if (id1 > 0) {
		id2 = fork();
		if (id2 > 0) {
			id4 = fork();
			if (id4 > 0) {
				printf("Processo pai %d %d	 pid=%d\n", id1, id2, getpid());
			} else {
				printf("Processo filho 3 %d pid=%d\n", id4, getpid());
			}
		} else {
			printf("Processo filho 2 %d pid=%d\n", id2, getpid());
		}
	} else {
		id3 = fork();
		if (id3 > 0) {
			printf("Processo filho %d pid=%d\n", id1, getpid());
		} else {
			printf("Processo neto %d pid=%d\n", id3, getpid());
		}
	}

	/*while(1) {
		sqrt(pow(rand() %10,rand() %10));
	}*/
}



