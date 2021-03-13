#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

void leer_campos();
void copiar_examen();
void manejador(int);

void main()
{
    //printf("empieza B\n");

    FILE *fichero;
    char f[20];
    signal(SIGINT,manejador);

    fichero = fopen("./UTILS/estudiantes.txt", "rt");
    if (fichero == NULL )
    {
        printf("El fichero o el directorio no se pueden abrir\n");
        exit(EXIT_FAILURE);
    }
    else
    {   //sleep(20);
        leer_campos(fichero);
        //printf("termina B\n");
        exit(EXIT_SUCCESS);
    }
    

}

void copiar_examen(char ruta_origen[40],char dni [8]){
    char comando[60];
  
    sprintf(comando,"cp %s ./ESTUDIANTES/%s",ruta_origen,dni);
    if (system(comando) == -1){
        printf("Error copiando examenes, PB\n");
        return (EXIT_FAILURE);
    }

}
void leer_campos(FILE *fichero)
{
    char dni[10];
    char examen[10];
    int nota;
    char ruta_origen[40];
    
    while (!feof(fichero))
    {
        if (fscanf(fichero, "%s %s %i", &dni, &examen, &nota) == 3)
        {   
            sprintf(ruta_origen,"./UTILS/MODELOSEXAMEN/MODELO%s.pdf",examen);
            
            copiar_examen(ruta_origen,dni);
            
        }
    }

    fclose(fichero);
}
void manejador(int sig){
    
    printf("señal %d recibida en proceso B\n",sig);
    exit(EXIT_SUCCESS); 
}