#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

void leer_campos();
void crear_directorios();
void manejador(int);


void main()
{
    FILE *fichero;
    char f[20];
    signal(SIGINT,manejador);

    fichero = fopen("./UTILS/estudiantes.txt", "rt");
    if (fichero == NULL)
    {
        printf("El fichero no existe\n");
        exit(EXIT_FAILURE);
    }
    else
    {   
        
        leer_campos(fichero);

        exit(EXIT_SUCCESS);
    }

}

void crea_directorios(char dni[8]){
    char directorio[20];

    sprintf(directorio,"./ESTUDIANTES/%s",dni);
    mkdir(directorio,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void leer_campos(FILE *fichero)
{
   
    char dni[8];
    char examen[4];
    int nota;
    char *dir;

    dir = "./ESTUDIANTES";

    mkdir(dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    do
 {
    if (fscanf(fichero, "%s %s %i", &dni, &examen, &nota) == 3)
      crea_directorios(dni);

      
 } while (!feof(fichero));
    
    fclose(fichero);
}
void manejador(int sig){
    
    printf("señal %d recibida en proceso A\n",sig);
    exit(EXIT_SUCCESS); 
}
