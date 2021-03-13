/********************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PB.c
 * 
 * Author:          Jesus Gamero Tello
 *
 * Purpose:         Se copia cada modelo de examen  en la carpteta con el dni correspondiente
 *
 *********************************************************/
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
    {   
        leer_campos(fichero);
        
        exit(EXIT_SUCCESS);
    }
    

}

void copiar_examen(char ruta_origen[40],char dni [8]){
    //copiamos el modelo .pdf en la carpeta de su dni
    char comando[60];
  
    sprintf(comando,"cp %s ./ESTUDIANTES/%s",ruta_origen,dni);
    if (system(comando) == -1){
        printf("Error copiando examenes, PB\n");
        return (EXIT_FAILURE);
    }

}
void leer_campos(FILE *fichero){
    //leemos el fichero estudiantes y cogemos los datos del modelo del examen
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