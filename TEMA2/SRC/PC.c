/********************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PC.c
 * 
 * Author:          Jesus Gamero Tello
 *
 * Purpose:         Se generara un fichero .txt con la nota necesaria en el siguiente
 *                  examen para aprobar la asignatura y se calcula la nota media de la 
 *                  clase
 *
 *********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>

int leer_campos();
void calcular_nota();
int nota_media_clase();
void escribir_fichero();
void manejador(int);

void main(int argc, char *argv [])
{
    int nota_media = 0;
    FILE *fichero;
    char msg[20];
   
    signal(SIGINT,manejador);

    fichero = fopen("./UTILS/estudiantes.txt", "rt");
    if (fichero == NULL )
    {
        printf("El fichero no se pueden abrir\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        nota_media = leer_campos(fichero);
        sprintf(msg,"%d",nota_media);
        write(atoi(argv[0]), msg, strlen(msg)+1); //escribimos en la tuberia
        exit(EXIT_SUCCESS);
    }
    

}

void escribir_fichero(char ruta_origen[40],int nota_necesaria){
    //genero el .txt con la nota necesaria y lo copiamos en su directorio 
    char *texto;
    char sentence[100];
    char ruta[50];
    texto = "La nota que debes obtener en este nuevo\
 examen para superar la prueba es ";
  
    FILE *fptr;

    sprintf(sentence,"%s%i",texto,nota_necesaria);
    sprintf(ruta,"%s%s",ruta_origen,"/fichero.txt");
    fptr = fopen(ruta, "w");

    if (fptr == NULL) {
        printf("Error abriendo el fichero!");
        exit(1);
    }
    fprintf(fptr, "%s", sentence);
    fclose(fptr);
}

int nota_media_clase(int nota, int sumatorio_notas, int media_clase, int numero_estudiantes){
    //se calcula la nota media de toda la clase
    media_clase=sumatorio_notas/numero_estudiantes;
    return media_clase;
}

void calcular_nota(char ruta_origen[40],int nota){
    //calculo nota media necesaria para pasar el examen de cada alumno
    int nota_necesaria;
    nota_necesaria = 10 - nota;
    escribir_fichero(ruta_origen,nota_necesaria);
}

int leer_campos(FILE *fichero)
{
    //leemos los campos del fichero estudiantes.txt 
    char dni[10];
    char examen[10];
    char ruta_origen[40];
    int nota;

    int sumatorio_notas=0;
    int media_clase=0;
    int numero_estudiantes=1;
    
    while (!feof(fichero))
    {
        if (fscanf(fichero, "%s %s %i", dni, examen, &nota) == 3)
        {   
            sumatorio_notas += nota;
            sprintf(ruta_origen,"./ESTUDIANTES/%s",dni);
            calcular_nota(ruta_origen,nota);
            media_clase = nota_media_clase(nota,sumatorio_notas,media_clase,numero_estudiantes);
            numero_estudiantes++; 
        }
    }

    fclose(fichero);
    return media_clase;
}
void manejador(int sig){
    
    printf("señal %d recibida en proceso C\n",sig);
    exit(EXIT_SUCCESS); 
}