#include <unistd.h>
#include <stdio.h>

int main() {
	printf("pid= %d\n", getpid());
	printf("ppid= %d\n", getppid());
}
