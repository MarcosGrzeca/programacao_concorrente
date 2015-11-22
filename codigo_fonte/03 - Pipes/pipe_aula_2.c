#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main() {
  float a,b,c, res1, res2, raiz1, raiz2;
  int id, id2;
  int pipe1[2], pipe2[2];
  
  printf("Digite os valores: ");
  scanf("%f %f %f", &a, &b, &c);
  
  pipe(pipe1);
  id = fork();
  
  if (id > 0) {

    pipe(pipe2);
    id2 = fork();
    
    if (id2 > 0) {
      close(pipe1[1]);
      close(pipe2[1]);

      read(pipe1[0], &raiz1, sizeof(float));
      read(pipe2[0], &raiz2, sizeof(float));

      printf("As raizes sao %f %f \n", raiz1, raiz2);

      close(pipe1[0]);
      close(pipe2[0]);

    } else {
      close(pipe2[0]);
      raiz2 = (-b - sqrt(b*b -4*a*c))/(2*a);
      write(pipe2[1], &raiz2, sizeof(float));
      close(pipe2[1]);
    }
  } else {
    close(pipe1[0]);
    raiz1 = (-b + sqrt(b*b -4*a*c))/(2*a);
    write(pipe1[1], &raiz1, sizeof(float));
    close(pipe1[1]);
  }
}