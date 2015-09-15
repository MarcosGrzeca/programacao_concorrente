#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*-----------------------------------------------------*/
#define N 100
/*-----------------------------------------------------*/
int main(int argc, char **argv){
   

   int f;
   char fifo[N];
   char str[N] = "Alo mundo";

   if (argc != 2) {
   		printf("%s < figo >\n", argv[0]);
   		exit(0);
   }

   strcpy(fifo, argv[1]);
   mkfifo(fifo, 0666);

   f = open(fifo, O_WRONLY);
   write(f, str, strlen(str) + 1);
   close(f);
   unlink(fifo);
}