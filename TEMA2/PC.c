#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void leer_campos();
void calcular_nota();

void main()
{
    printf("empieza C\n");

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
        printf("termina C\n");
        exit(EXIT_SUCCESS);
    }
    

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
    
    while (!feof(fichero))
    {
        if (fscanf(fichero, "%s %s %i", &dni, &examen, &nota) == 3)
        {   
            sprintf(ruta_origen,"ESTUDIANTES/%s",dni);
            calcular_nota(ruta_origen,nota);
            //printf("ruta nueva %i\n", nota);
            
        }
    }

    fclose(fichero);
}