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
int main(){
    pid_t pid,pidc,pidb;
    int tuberia [2];
    char wr_tuberia [256];
    char buffer [16];
    int estado;
    char *arg_list[] = {NULL};
    char *var_list[] = {NULL};
    
    pipe(tuberia);
    sprintf(wr_tuberia, "%d", tuberia[ESCRITURA]);
    pid = fork();

    signal(SIGINT,manejador);

    switch (pid)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:
        if (execve("./PA", arg_list, var_list) == -1)
        {
            printf("Error no esperado en execve, ./PA\n");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        wait(&estado);
        pidb = fork();
        switch (pidb)
        {
        case -1:
            perror("No se puede crear el proceso hijo\n");
            break;
        case 0:
            //signal(SIGINT,manejador);
            if (execve("./PB", arg_list, var_list) == -1)
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
                if (execl("./PC", wr_tuberia, var_list) == -1)
                {
                    printf("Error no esperado en execl, ./PC\n");
                    exit(EXIT_FAILURE);
                }

                break;

            default:
                
                waitpid(pidb,&estado,0);
                waitpid(pidc,&estado,0);
                
                read(tuberia[LECTURA], buffer,sizeof(buffer));
                creacion_log(buffer);
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
void creacion_log(char buffer[16]){
    char sentence[1024];
    char *texto;
    
    texto = " ******** Log del sistema ********\n\
    Creación de directorios finalizada.Copia de modelos de examen, finalizada.\n\
    Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n\
    La nota media de la clase es: %s\n \
   FIN DE PROGRAMA\n";
  
    FILE *fptr;

    fptr = fopen("log.txt", "w");
    sprintf(sentence,texto,buffer);
    printf(sentence);

    if (fptr == NULL) {
        printf("Error abriendo el fichero!");
        exit(EXIT_FAILURE);
    }
    fprintf(fptr, "%s", sentence);
    fclose(fptr);
}
void manejador(int sig){
    
    printf("señal %d recibida\n",sig);
    kill(getpid(),SIGINT);

    exit(EXIT_SUCCESS); 
}