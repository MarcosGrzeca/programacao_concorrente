#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main() {
     
     int dispositivo;
     struct fb_var_screeninfo vinfo;
     struct fb_fix_screeninfo finfo;
     long int tamanho;
     char *tela;
     int x, y;
     long int localizacao;

     // Open the file for reading and writing
     dispositivo = open("/dev/fb0", O_RDWR);
     
     if (dispositivo == -1) {
         printf("Erro ao abrir o framebuffer");
         exit(0);
     }

     printf("O framebuffer foi aberto com sucesso!\n");

     
     if (ioctl(dispositivo, FBIOGET_FSCREENINFO, &finfo) == -1) {
         perror("Error reading fixed information");
         exit(2);
     }

      if (ioctl(dispositivo, FBIOGET_VSCREENINFO, &vinfo) == -1) {
         perror("Erro ao obter informacoes da tela");
         exit(0);
     }

     // Tamanho da tela
     tamanho = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

     // Mapeando o dispositivo para a memoria
     tela = (char *)mmap(0, tamanho, PROT_READ | PROT_WRITE, MAP_SHARED, dispositivo, 0);
     if (tela == NULL) {
         perror("Erro nao mapear o frame buffer!");
         exit(0);
     }

     for (y = 0; y < 300; y++){
         for (x = 0; x < 300; x++){
             localizacao = x * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
             *(tela + localizacao) = 0;        
             *(tela + localizacao + 1) = 255;  
             *(tela + localizacao + 2) = 255;    
             *(tela + localizacao + 3) = 0;      
          }
     }
 
     munmap(tela, tamanho);
     close(dispositivo);
     return 0;
}

