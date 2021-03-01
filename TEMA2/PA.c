#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void leer_campos();
void crear_directorios();

void main()
{
    printf("empieza A\n");
    FILE *fichero;
    char f[20];

    fichero = fopen("estudiantes.txt", "rt");
    if (fichero == NULL)
    {
        printf("El fichero no existe\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("el fichero existe\n");
        leer_campos(fichero);
     printf("Termina A\n");

        exit(EXIT_SUCCESS);
    }

}

void crea_directorios(char dni[8]){
    char directorio[20];

    sprintf(directorio,"ESTUDIANTES/%s",dni);
    mkdir(directorio,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void leer_campos(FILE *fichero)
{
   
    char dni[8];
    char examen[4];
    int nota;
    char *dir;

    dir = "ESTUDIANTES/";

    mkdir(dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    do
 {
    if (fscanf(fichero, "%s %s %i", &dni, &examen, &nota) == 3)
      crea_directorios(dni);

      
 } while (!feof(fichero));
    
    fclose(fichero);
}
