#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*--------------------------------------------------------------------*/
struct args {
       int id;
       int numthr;
       int numtermos;
       float resultado;
};

typedef struct args ARGUMENTOS;

/*--------------------------------------------------------------------*/

double fatorial(int n){
       int i;
       double f = 1;
       
       for( i=1; i<=n; i++ ){
           f*=i;      
       }
       return(f);
}

/*--------------------------------------------------------------------*/
void *calcula ( void * args){
     ARGUMENTOS *p = (ARGUMENTOS *) args;
     int i;
     int id = p->id;
     int nthr = p->numthr;
     int ntermos = p->numtermos;
     double soma = 0;
    
     for( i=id ; i<=ntermos ; i+=nthr ){
          soma += 1/fatorial(i);
     }
     p->resultado = soma;
}
/*--------------------------------------------------------------------*/
int main(){
    double soma = 0;
    int i, ntermos, nthreads;
    
    DWORD *thId;
    ARGUMENTOS *argumentos;
    HANDLE *hThread;
    
    printf("Digite o numero de termos: ");
    scanf("%d",&ntermos);
    
    printf("Digite o numero de threads: ");
    scanf("%d",&nthreads);
    
    thId = (DWORD *) malloc( nthreads * sizeof(DWORD));
    argumentos = (ARGUMENTOS *) malloc( nthreads* sizeof(ARGUMENTOS) );
    
    hThread = (HANDLE *) malloc ( nthreads * sizeof(HANDLE) );
    
    for ( i=0 ; i<nthreads; i++ ){
        argumentos[i].id = i;
        argumentos[i].numthr = nthreads;
        argumentos[i].numtermos = ntermos;
        argumentos[i].resultado = 0;
       
        hThread[i] = CreateThread(NULL, 0,( LPTHREAD_START_ROUTINE) calcula , (LPVOID) &argumentos[i] , 0, &thId[i]);
    }
    
    for ( i=0 ; i<nthreads ; i++ ){
        WaitForSingleObject(hThread[i], INFINITE);
        soma += argumentos[i].resultado;
    }

    for ( i=0 ; i<nthreads ; i++ ){
        CloseHandle( hThread[i] );
    }    
    
    printf("Resultado: %.15f\n", soma);
    system("PAUSE");
}
