#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

int leer_campos();
void calcular_nota();
int nota_media_clase();
void escribir_fichero();
void manejador(int);

void main(int argc, char *argv [])
{
    //printf("empieza C\n");
    int nota_media = 0;
    FILE *fichero;
    char msg[20];
   
    signal(SIGINT,manejador);

    fichero = fopen("estudiantes.txt", "rt");
    if (fichero == NULL )
    {
        printf("El fichero o el directorio no se pueden abrir\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        nota_media = leer_campos(fichero);
        sprintf(msg,"%d",nota_media);
        write(atoi(argv[0]), msg, strlen(msg)+1);
        //printf("termina C\n");
        exit(EXIT_SUCCESS);
    }
    

}

void escribir_fichero(char ruta_origen[40],int nota_necesaria){
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
    
    media_clase=sumatorio_notas/numero_estudiantes;
    //printf("la nota media de la clase es %i\n",media_clase);
    return media_clase;
}

void calcular_nota(char ruta_origen[40],int nota){
    int nota_necesaria;
    nota_necesaria = 10 - nota;
    escribir_fichero(ruta_origen,nota_necesaria);
}

int leer_campos(FILE *fichero)
{
    char dni[10];
    char examen[10];
    char ruta_origen[40];
    int nota;

    int sumatorio_notas=0;
    int media_clase=0;
    int numero_estudiantes=1;
    
    while (!feof(fichero))
    {
        if (fscanf(fichero, "%s %s %i", &dni, &examen, &nota) == 3)
        {   
            sumatorio_notas += nota;
            sprintf(ruta_origen,"ESTUDIANTES/%s",dni);
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