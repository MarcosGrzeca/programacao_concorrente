#include <stdio.h>

void teste() {
	static int i = 0;
	i++;
	printf("%d\n", i);

}

int main(int argc, char const *argv[])
{
	int i;
	for (i = 0; i <10; i++) {
		teste();
	}
	return 0;
}