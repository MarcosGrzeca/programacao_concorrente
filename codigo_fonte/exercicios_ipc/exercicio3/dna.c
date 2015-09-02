#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------------------------*/
#define KEY 13
#define N 1000000
/*-------------------------------------------------------------------*/

struct msg {
  long tipo;
  int gc;
};

typedef struct msg MSG;
/*--------------------------------------------------------------*/
void  le_dna(char *arquivo, char *dna){

      char c;
      int i = 0;

      FILE *f = fopen(arquivo,"r"); 
      while ( ( c = fgetc(f) ) != EOF &&  c!='\n' ){
            dna[i++] = c;
      }     

      dna[i] = '\0';
}

/*--------------------------------------------------------------*/

int calcula(char *str, int inicio, int fim) {
      int i, total = 0, gc = 0;
      for (i = inicio; i< fim; i++ ){
            if ( str[i]=='C' || str[i]=='G'){ 
                  gc++; 
            }     
      }
      return gc;
}

int main(int argc, char **argv){ 

      int i, total = 0, gc = 0, pid1, pid2; 
      char str[N];

      le_dna("dna.txt",str);

      key_t chave = KEY;
      int fila;
      MSG mensagem;
    
      fila = msgget(chave, 0600 | IPC_CREAT);

      pid1 = fork();
      if (pid1 > 0) {
            pid2 = fork();
            if (pid2 > 0) {
                  msgrcv(fila, &mensagem, sizeof(int), 0, 0);
                  int count1 = mensagem.gc;
                  msgrcv(fila, &mensagem, sizeof(int), 0, 0);
                  int count2 = mensagem.gc;
                  printf("Conteudo GC: %.2f\n", (float) (count1 + count2)/strlen(str)); 
                  msgctl(fila, IPC_RMID, NULL);
            } else {
                  int gc = calcula(str, strlen(str)/2, strlen(str));
                  mensagem.tipo = 2;
                  mensagem.gc = gc;
                  msgsnd(fila, &mensagem, sizeof(int), 0);
            }
      } else {
            int gc = calcula(str, 0, strlen(str)/2);
            mensagem.tipo = 1;
            mensagem.gc = gc;
            msgsnd(fila, &mensagem, sizeof(int), 0);
      }
}