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
double seno (double ang, int n){
	double s = 0;
	int i;

	for (i=1; i<=n; i++){
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
	double ang, s;
	int n;

	printf("Digite o angulo: ");
	scanf("%lf", &ang);

	printf("Digite o numero de termos: ");
	scanf("%d", &n);

	ang = ang * PI / 180; 
		
	printf("Digite o angulo: %f\n", ang);
	s = seno(ang, n);

	printf("Seno: %.15f\n", s);	
}
/*--------------------------------------------------*/
