#include <stdio.h>
#include <math.h>

int main(){
	int i, n;
	float x, soma = 0;
	printf("Digite o valor de x: ");
	scanf("%f", &x);
	printf("Digite o numero de termos: ");
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		soma += pow((x-1.0)/x,i) * 1.0/i;
	}
	printf("Log natural: %f\n", soma);
}