#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h> 

/*--------------------------------------------------*/
float log_natural(float x, int ini, int fim){
	float soma = 0; 
	int i;
	for(i=ini;i<=fim;i++){ 
		soma += pow((x-1.0)/x,i) * 1.0/i; 
	} 
	return(soma);

}
/*--------------------------------------------------*/
int main(){ 
	int n; 
	int pid;
	float x, soma, soma1, soma2;
    	int fd1, fd2;
	
	printf("Digite o valor de x: "); 
	scanf("%f", &x); 

	printf("Digite o numero de termos: "); 
	scanf("%d",&n); 

	mkfifo("fifo1", 0666);

        mkfifo("fifo2", 0666);

        pid = fork();

        if ( pid > 0 ){
		
	    pid = fork();

	    if ( pid > 0 ){
			fd1 = open("fifo1", O_RDONLY);
			read(fd1, &soma1, sizeof(float));
			fd2 = open("fifo2", O_RDONLY);
		 	read(fd2, &soma2, sizeof(float));

			soma = soma1 + soma2;

			printf("Log natural: %f\n", soma);
			
			close("fifo1");			
			close("fifo2");			
						
			unlink("fifo1");
  		        unlink("fifo2");
	    }
	    else {
	  	fd2 = open("fifo2", O_WRONLY);
          	soma2 = log_natural(x, n/2+1, n); 
	  	write(fd2, &soma2, sizeof(float));
	  	close(fd2);
	   }        
    }
    else{
	  fd1 = open("fifo1", O_WRONLY);
          soma1 = log_natural(x, 1, n/2);
	  write(fd1, &soma1, sizeof(float));  
	  close(fd1);
    }
}

