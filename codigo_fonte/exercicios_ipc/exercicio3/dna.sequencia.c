#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------------------*/
#define N 1000000

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

int main(int argc, char **argv){ 

	int i, total = 0, gc = 0; 
	char str[N];

	le_dna("dna.txt",str);

 	for ( i=0; i<strlen(str); i++ ){
		if ( str[i]=='C' || str[i]=='G'){ 
			gc++;	
		}	
		total++;	 
	}

	printf("Conteudo GC: %.2f\n", (float)gc/total); 

} 
