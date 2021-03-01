#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void leer_campos();
void copiar_examen();

void main()
{
    printf("empieza B\n");

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
        printf("termina B\n");
        exit(EXIT_SUCCESS);
    }
    

}

void copiar_examen(char ruta_origen[40],char dni [8]){
    char comando[60];
  
    sprintf(comando,"cp %s ESTUDIANTES/%s",ruta_origen,dni);
    system(comando);

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
            sprintf(ruta_origen,"MODELOSEXAMEN/MODELO%s.pdf",examen);
            
            copiar_examen(ruta_origen,dni);
            
        }
    }

    fclose(fichero);
}