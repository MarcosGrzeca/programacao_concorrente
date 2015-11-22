#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------------------------*/
#define KEY 9
#define N 50

/*-------------------------------------------------------------------*/

struct msg {
  long tipo;
  float valor;
};

typedef struct msg MSG;
/*-------------------------------------------------------------------*/

int main() {

  float a,b,c, res1, res2, raiz1, raiz2;
  int id, id2;

  key_t chave = KEY;
  int fila;
  MSG mensagem;

  fila = msgget(chave, 0600 | IPC_CREAT);

  printf("Digite os valores: ");
  scanf("%f %f %f", &a, &b, &c);

  id = fork();
  
  if (id > 0) {

    id2 = fork();

    if (id2 > 0) {	  
     msgrcv(fila, &mensagem, sizeof(float), 1, 0);
     raiz1 = mensagem.valor;
     msgrcv(fila, &mensagem, sizeof(float), 2, 0);
     raiz2 = mensagem.valor;
     printf("As raizes sao %f %f \n", raiz1, raiz2);

     msgctl(fila, IPC_RMID, NULL);
   } else {
     raiz2 = (-b - sqrt(b*b -4*a*c))/(2*a);
     mensagem.tipo = 2;
     mensagem.valor = raiz2;
     msgsnd(fila, &mensagem, sizeof(float), 0);
   }
 } else {
  raiz1 = (-b + sqrt(b*b -4*a*c))/(2*a);
  mensagem.tipo = 1;
  mensagem.valor = raiz1;
  msgsnd(fila, &mensagem, sizeof(float), 0);

}


    /*
    mensagem.tipo = 1;
    strcpy(mensagem.texto, "ping");
 
    
    msgsnd(fila, &mensagem, sizeof(mensagem.texto), 0);
    msgrcv(fila, &mensagem, sizeof(mensagem.texto), 2, 0);
    printf("Recebi %s\n", mensagem.texto);
    
    msgctl(fila, IPC_RMID, NULL);*/
  }