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
int main(){
   int fw, fr;
   char str[N] = "ping";

   mkfifo("fifo_pai", 0666);
   mkfifo("fifo_filho", 0666);

   fw = open("fifo_pai", O_WRONLY);
   fr = open("fifo_filho", O_RDONLY);
   write(fw, str, strlen(str) + 1);
   read(fr, str, N);
   printf("Pai recebeu %s\n", str);
   close(fw);
   close(fr);
   unlink("fifo_pai");
   unlink("fifo_filho");
}