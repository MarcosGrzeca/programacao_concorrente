#include <stdio.h>
#include <math.h>

/*--------------------------------------------------*/
#define PI 3.14159265359

/*--------------------------------------------------*/
double fatorial(int n){
	int i;
	double f = 1;
	
	for( i=1; i<=n; i++ ){
		f*=i;
	}

	return(f);
}

/*--------------------------------------------------*/
double seno (double ang, int ini, int fim){
	double s = 0;
	int i;

	for (i=ini; i<=fim; i++){
		if ( i & 1 ){
			s += pow(ang, 2*i-1)/fatorial(2*i-1);
		}
		else{
			s -= pow(ang, 2*i-1)/fatorial(2*i-1);
		} 	
	}
	return(s);
}

/*--------------------------------------------------*/
int main(){
	double ang, s, s1, s2;
	int pid;	
	int n;
	int pipe1[2], pipe2[2];

	printf("Digite o angulo: ");
	scanf("%lf", &ang);

	printf("Digite o numero de termos: ");
	scanf("%d", &n);

	ang = ang * PI / 180; 

	pipe(pipe1);

	pid = fork();

	if ( pid > 0 ){
		
		pipe(pipe2);

		pid = fork();

		if ( pid > 0 ){
			close(pipe1[1]);
			close(pipe2[1]);
						
			read(pipe1[0],&s1,sizeof(double));
			read(pipe2[0],&s2,sizeof(double));
			s = s1 + s2;
			printf("Seno: %f\n", s);			

			close(pipe1[0]);
			close(pipe2[0]);
			wait(NULL);
			wait(NULL);
		}	
		else{
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			s2 = seno(ang,n/2+1,n);			
			write(pipe2[1],&s2,sizeof(double));
			close(pipe2[1]);
		}
	}
	else{
		close(pipe1[0]);
		s1 = seno(ang,1,n/2);			
		write(pipe1[1],&s1,sizeof(double));
		close(pipe1[1]);
	}
}
/*--------------------------------------------------*/

