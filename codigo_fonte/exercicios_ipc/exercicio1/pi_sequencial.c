#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define w 1.0/N

void main (){
      float pi= 0.0, x;
      int i;
      for (i = 1; i < (N+1); i++){
            x = w * (i - 0.5);
            pi = pi + 4.0 / (1.0 + (x * x));
      }
      pi = pi * w;
      printf("pi é aproximadamente: %f\n", pi);
}
