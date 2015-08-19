#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int id;
	id = fork();

	if (id > 0) {
		id = fork();
		id = fork();
	}

	while(1);
}
