#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

/*--------------------------------------------------------------------*/
struct args {
       int id;
       int numthr;
       int numtermos;
       float x;
       float res;
};

typedef struct args ARGUMENTOS;

/*--------------------------------------------------------------------*/
void *calcula ( void * args){
     ARGUMENTOS *p = (ARGUMENTOS *) args;
     int i;
     int id = p->id;
     int nthr = p->numthr;
     int ntermos = p->numtermos;
     float x = p->x;
     float soma = 0;
    
     for( i=id+1 ; i<=ntermos ; i+=nthr ){
          soma += pow( (x-1.0)/x, i ) * 1.0/i;
     }

     p->res = soma;
}
/*--------------------------------------------------------------------*/
int main(){
    float x, soma = 0;
    int i, n, t;
    
    DWORD *thId;
    ARGUMENTOS *argumentos;
    HANDLE *hThread;
    
    printf("Digite o valor de x: ");
    scanf("%f",&x);

    printf("Digite o numero de termos: ");
    scanf("%d",&n);
    
    printf("Digite o numero de threads: ");
    scanf("%d",&t);
    
    thId = (DWORD *) malloc( t * sizeof(DWORD));
    argumentos = (ARGUMENTOS *) malloc( t* sizeof(ARGUMENTOS) );
    
    hThread = (HANDLE *) malloc ( t * sizeof(HANDLE) );
    
    for ( i=0 ; i<t ; i++ ){
        argumentos[i].id = i;
        argumentos[i].numthr = t;
        argumentos[i].numtermos = n;
        argumentos[i].x = x;
        argumentos[i].res = 0;
        
        hThread[i] = CreateThread(NULL, 0,( LPTHREAD_START_ROUTINE) calcula , (LPVOID) &argumentos[i] , 0, &thId[i]);
    }
    
    for ( i=0 ; i<t ; i++ ){
        WaitForSingleObject(hThread[i], INFINITE);
        soma += argumentos[i].res;
    }

    for ( i=0 ; i<t ; i++ ){
        CloseHandle( hThread[i] );
    }    
    
    printf("Resultado: %f\n", soma);
    system("PAUSE");
}
