#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void leer_campos();
void calcular_nota();
void nota_media_clase();

void main()
{
    //printf("empieza C\n");

    FILE *fichero;
    char f[20];
    
    fichero = fopen("estudiantes.txt", "rt");
    if (fichero == NULL )
    {
        printf("El fichero o el directorio no se pueden abrir\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("el fichero existe\n");
        leer_campos(fichero);
        //printf("termina C\n");
        exit(EXIT_SUCCESS);
    }
    

}

void nota_media_clase(int nota, int sumatorio_notas, int media_clase, int numero_estudiantes){
    
    media_clase=sumatorio_notas/numero_estudiantes;
    printf("la nota media de la clase es %i\n",media_clase);
}

void calcular_nota(char ruta_origen[40],int nota){
    char comando[240];
    int nota_necesaria;
    char *texto;

    texto = "La nota que debes obtener en este nuevo\
 examen para superar la prueba es ";
    nota_necesaria = 10 - nota;
  
    sprintf(comando,"echo %s%i > %s/fichero.txt",texto,nota_necesaria,ruta_origen);
    system(comando);

    //printf("%s\n",comando);
}

void leer_campos(FILE *fichero)
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
            nota_media_clase(nota,sumatorio_notas,media_clase,numero_estudiantes);
            numero_estudiantes++;
            
            
        }
    }

    fclose(fichero);
}