#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 10

/*--------------------------------------------------------------------*/
void * funcao(void *args){
         printf("Alo mundo!!\n");
}


/*--------------------------------------------------------------------*/
int main(){
    int i;
    DWORD thId[N];
    HANDLE hThread[N];

    for ( i=0 ; i<N; i++ ){
            hThread[i] = CreateThread(NULL, 0,( LPTHREAD_START_ROUTINE) funcao , (LPVOID) i , 0, &thId[i]);

    }

    for ( i=0 ; i<N ; i++ ){
        WaitForSingleObject(hThread[i], INFINITE);
    }

    for ( i=0 ; i<N ; i++ ){
        CloseHandle( hThread[i] );
    }


}
