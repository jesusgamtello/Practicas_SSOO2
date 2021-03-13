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
void log();
void limpiar();
int main(){
    pid_t pid,pidc,pidb;
    int tuberia [2];
    char wr_tuberia [256];
    char buffer [16];
    int estado;
    char *arg_list[] = {NULL};
    char *var_list[] = {NULL};

    char cadena [80];    
    
    pipe(tuberia);
    sprintf(wr_tuberia, "%d", tuberia[ESCRITURA]);
    pid = fork();

    signal(SIGINT,manejador);

    creacion_log();
    if (system("./SRC/daemon &") == -1){
        printf("error intentando ejecutar el demonio\n");
        return(EXIT_FAILURE);
    }
    switch (pid)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:
        if (execve("./SRC/PA", arg_list, var_list) == -1)
        {
            printf("Error no esperado en execve, ./PA\n");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        wait(&estado);
        log("Creacion de directorios finalizada\n");
        pidb = fork();
        switch (pidb)
        {
        case -1:
            perror("No se puede crear el proceso hijo\n");
            break;
        case 0:
            if (execve("./SRC/PB", arg_list, var_list) == -1)
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
                if (execl("./SRC/PC", wr_tuberia, var_list) == -1)
                {
                    printf("Error no esperado en execl, ./PC\n");
                    exit(EXIT_FAILURE);
                }

                break;

            default:
                waitpid(pidb,&estado,0);
                log("Copia de modelos finalizada\n");
                waitpid(pidc,&estado,0);
                read(tuberia[LECTURA], buffer,sizeof(buffer)); //controlar read
                sprintf(cadena,"La nota media de la clase es: %s\nFIN DE PROGRAMA\n",buffer);
                log(cadena);
                printf("El valor leido de la tuberia es: %s\n", buffer);
                printf("Todo terminao\n");
                break;
            }
            break;
        }

        break;
    }
    return 0;
}
void creacion_log(){
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
void log(char append [20]){
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
    pid_t pid;
    int status;
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:
        if (execve("./SRC/PD", NULL, NULL) == -1)
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
    //kill(getpid(),SIGINT);
    log("Interrupción por teclado\n");
    limpiar();
    exit(EXIT_SUCCESS); 
}