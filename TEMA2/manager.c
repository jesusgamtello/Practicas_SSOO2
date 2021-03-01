#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    pid_t pid,pidc,pidb;
    int estado;
    int n;
    char *arg_list[] = {NULL};
    char *var_list[] = {NULL};
 
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("No se puede crear el proceso hijo\n");
        break;
    case 0:
        printf("soy el proceso A\n");
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
            if (execve("./PB", arg_list, var_list) == -1)
            {
                printf("Error no esperado en execve, ./PB\n");
                exit(EXIT_FAILURE);
            }

            break;

        default:
            /*printf("esperando a que los proceso hijo2 finalice\n");
            wait(&estado);*/
            pidc = fork();
            switch (pidc)
            {
            case -1:
                perror("No se puede crear el proceso hijo\n");
                break;
            case 0:
                if (execve("./PC", arg_list, var_list) == -1)
                {
                    printf("Error no esperado en execve, ./PC\n");
                    exit(EXIT_FAILURE);
                }

                break;

            default:
                waitpid(pidb,&estado,0);
                waitpid(pidc,&estado,0);

                printf("Todo terminao");
                break;
            }
            break;
        }

        break;
    }
    return 0;
}