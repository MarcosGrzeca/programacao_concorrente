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
   int fw, fr;
   char str[N];

   mkfifo("fifo_pai", 0666);
   mkfifo("fifo_filho", 0666);

   fw = open("fifo_filho", O_WRONLY);
   fr = open("fifo_pai", O_RDONLY);
   read(fr, str, N);
   strcat(str, " - pong");
   write(fw, str, strlen(str) + 1);
   close(fr);
   close(fw);
}