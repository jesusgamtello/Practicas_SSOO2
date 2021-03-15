/********************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    manager.c
 * 
 * Author:          Jesus Gamero Tello
 *
 * Purpose:         Clase manager que ejecuta todo nuestro programa y que se encarga de la creacion de hijos 
 *
 *********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define ESCRITURA 1
#define LECTURA 0

void manejador(int);
void creacion_log();
void aniadir_log();
void limpiar();
int main(){
    pid_t pida,pidc,pidb;
    int tuberia [2];
    char wr_tuberia [256];
    char buffer [16];
    int estado;
    char *arg_list[] = {NULL};
    char *var_list[] = {NULL};

    char cadena_nota [80];    
    
    pipe(tuberia);
    sprintf(wr_tuberia, "%d", tuberia[ESCRITURA]);
    
    signal(SIGINT,manejador);

    creacion_log(); // llamamos a este metodo para crearnos el fichero log.txt
    
    if (system("./EXEC/daemon &") == -1){ //ejecucion del demonio en segundo plano
        printf("error intentando ejecutar el demonio\n");
        return(EXIT_FAILURE);
    }
    pida = fork();
    switch (pida)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:

        if (execve("./EXEC/PA", arg_list, var_list) == -1)
        {
            printf("Error no esperado en execve, ./PA\n");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        wait(&estado); //termina A
        aniadir_log("Creacion de directorios finalizada\n");
        pidb = fork();
        switch (pidb)
        {
        case -1:
            perror("No se puede crear el proceso hijo\n");
            break;
        case 0:
            if (execve("./EXEC/PB", arg_list, var_list) == -1)
            {
                printf("Error no esperado en execve, ./PB\n");
                exit(EXIT_FAILURE);
            }
            break;

        default:
            pidc = fork();
            switch (pidc)
            {
            case -1:
                perror("No se puede crear el proceso hijo\n");
                break;
            case 0:
                if (execl("./EXEC/PC", wr_tuberia, var_list,NULL) == -1)
                {
                    printf("Error no esperado en execl, ./PC\n");
                    exit(EXIT_FAILURE);
                }

                break;

            default:
                waitpid(pidb,&estado,0); //termina B
                aniadir_log("Copia de modelos finalizada\n");
                waitpid(pidc,&estado,0); //termina C 
                read(tuberia[LECTURA], buffer,sizeof(buffer)); //leemos la tuberia 
                sprintf(cadena_nota,"La nota media de la clase es: %s\nFIN DE PROGRAMA\n",buffer);
                aniadir_log(cadena_nota);
                break;
            }
            break;
        }

        break;
    }
    return 0;
}
void creacion_log(){
    //creamos el fichero log.txt
    FILE *fptr;
    char *texto;
    texto = " ******** Log del sistema ********\n";

    fptr = fopen("log.txt", "w");

    if (fptr == NULL) {
        printf("Error abriendo el fichero!");
        exit(EXIT_FAILURE);
    }
    fputs(texto,fptr);
    fclose(fptr);
}
void aniadir_log(char append [20]){
    //aniadimos al fichero log.txt 
    FILE *fptr;

    fptr = fopen("log.txt", "a");
    if (fptr == NULL) {
        printf("Error abriendo el fichero!");
        exit(EXIT_FAILURE);
    }
    fputs(append,fptr);
    fclose(fptr);
}
void limpiar(){
    //llama al proceso D para limpiar la carpeta ESTUDIANTES
    pid_t pidd;
    int status;
    pidd = fork();
    switch (pidd)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:
        if (execve("./EXEC/PD", NULL, NULL) == -1)
        {
            printf("Error no esperado en execve, ./PD\n");
            exit(EXIT_FAILURE);
        }
        break;

    default:
        wait(&status);
        break;
    }
}
void manejador(int sig){
    
    printf("señal %d recibida en manager\n",sig);
    aniadir_log("Interrupción por teclado\n");
    limpiar();
    exit(EXIT_SUCCESS); 
}