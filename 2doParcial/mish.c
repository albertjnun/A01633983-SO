/******** mish.c **********/

// gcc -o mish mish.c

#include <ctype.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/wait.h>

 

#define MAX_LINE 80

#define MAX_NUM_ARGS 10

 

size_t string_parser(char *input, char *word_array[]) {
size_t n = 0;
while (*input) {
while (isspace((unsigned char)*input))
++input;
if (*input) {
word_array[n++] = (char *)input;
while (*input && !isspace((unsigned char)*input))
++input;
*(input) = '\0';
++input;
}
}
word_array[n] = NULL;
return n;
}


 

int main(void) {

  char *args[MAX_NUM_ARGS + 1]; /* command line (of 80) has max of 5 arguments */

  char line[MAX_LINE + 1];

  int should_run = 1;

 

  int i;

 

  while (should_run) {

    printf("mish> ");

    fgets(line,MAX_LINE,stdin);

    line[strcspn(line, "\n")] = '\0';

    // Separamos la línea en palabras separadas por espacio

    i = string_parser(line,args); // i contiene el número de argumentos

    //printf("Args 0:%d, %s %s\n", i, args[0],line); // Es solo para pruebas borrar cuando esté listo
    //printf("Args 1:%d, %s %s\n", i, args[1],line); // Es solo para pruebas borrar cuando esté listo

    // y las guardamos en args

    //(1) Crear un proceso hijo
    
    //args[i]=NULL;
    /*
        Agregamos al arreglo un valor de NULL, para indicar el fin del arreglo
    */
    if ((strcmp(args[0],"exit"))==0){
       return 0;
    }

    pid_t pid = fork();

    if (pid == 0) {
    //(2) El hijo debe ejecutar execvp para ejecutar al comando tecleado
        /*
        char *dummy[MAX_NUM_ARGS];
        for (int a = 0; a < i; a++){
            dummy[a]=args[a+1];
            Creamos un arreglo con el fin de copiar args sin el primer valor para tratar de solucionar los errores al ejecutar
            una programa con mas de 1 argumento.
        }
        printf("Ese es dummy 0: %s\n",dummy[0]);
        printf("Ese es dummy 1: %s\n",dummy[1]);
        */

        execvp(args[0], args);
       

    //(3) Si el programa no existe debe imprimir programa no encontrado
        printf("%s Programa no encontrado\n",line); 
    }
    else{ 
    //(4) El proceso padre debe esperar a que el hijo termine, checar funcion wait
        waitpid(pid,0,0);
        printf("Soy el padre\n");
    } 

    


    
    /*
    (5) Debe ejecutar comandos como ls -l /etc o ps -fea

    (6) Cuando se teclee exit deberá terminar
    */

    

    

    fflush(stdout);

    fflush(stdin);

    line[0] = '\0';

  }

 

  return 0;

}
