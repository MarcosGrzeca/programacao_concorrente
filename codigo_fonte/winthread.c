#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 10

struct argumentos {
       int ini;
       int nthreads;
       int ntermos;
       int x;
       float n;
       float resultado;
};

typedef struct argumentos ARGUMENTOS;


/*--------------------------------------------------------------------*/
void * funcao(void *args){
	 ARGUMENTOS *p = (ARGUMENTOS *) args;
	 int i;
	 float res = 0;
	 float valor = 0;
     for (i = p->ini; i < p->ntermos; i += p->nthreads) {
         valor = p->x / (i * 2 -1) ;
         if (!(i & 1)) {
            valor = valor - 1;
         }
         res += valor;
     }
     p->resultado = res;
     printf("Resultado %f\n", res);
}

/*--------------------------------------------------------------------*/
int main(){
    int i, x;
    int nthreads, ntermos;
    DWORD *thId;
    HANDLE *hThread;
    ARGUMENTOS *args;
    
    printf("Digite o numero de threads:\n");
    scanf("%d", &nthreads);
    printf("Digite o numero de termos:\n");
    scanf("%d", &ntermos);
    
    printf("Digite X:\n");
    scanf("%d", &x);
    
    thId = (DWORD *) malloc(nthreads * sizeof(DWORD));
    hThread = (HANDLE *) malloc(nthreads * sizeof(HANDLE));
    args = (ARGUMENTOS *)malloc(nthreads *sizeof(ARGUMENTOS));

    for ( i=0 ; i<nthreads; i++ ){
        args[i].ini = i + 1;
        args[i].nthreads = nthreads;
        args[i].ntermos = ntermos;
        args[i].x = x;
        args[i].resultado = 0;
        hThread[i] = CreateThread(NULL, 0,( LPTHREAD_START_ROUTINE) funcao , (LPVOID) &args[i] , 0, &thId[i]);
    }

    for ( i=0 ; i<nthreads ; i++ ){
        WaitForSingleObject(hThread[i], INFINITE);
    }

    for ( i=0 ; i<nthreads ; i++ ){
        CloseHandle( hThread[i] );
    }

    system("pause");
}
