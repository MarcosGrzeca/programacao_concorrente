#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

/*-------------------------------------------------------------------*/
#define KEY 8
#define N 50

/*-------------------------------------------------------------------*/

struct msg {
  long tipo;
  char texto[N];
};

typedef struct msg MSG;
/*-------------------------------------------------------------------*/

int main() {
    key_t chave = KEY;
    int fila;
    MSG mensagem;
    
    fila = msgget(chave, 0);
    
    msgrcv(fila, &mensagem, sizeof(mensagem.texto), 0, 0);
    
    printf("Recebi %s\n", mensagem.texto);
    
    mensagem.tipo = 2;
    strcat(mensagem.texto, "-pong");
    msgsnd(fila, &mensagem, sizeof(mensagem.texto), 0);

    //msgctl(fila, IPC_RMID, NULL);
}