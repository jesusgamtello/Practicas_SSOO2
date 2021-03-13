#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
        /*pid_t pid, sid;
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }                
        sid = setsid();
        if (sid < 0) {
                printf("fallo en la creacion del sid\n");
                exit(EXIT_FAILURE);
        }*/
        while (1)
        {
                sleep(60);
                if (system("cp -r ESTUDIANTES/ COPIA_SEGURIDAD/") == -1)
                {
                        printf("error haciendo la copia de seguridad\n");
                        return (EXIT_FAILURE);
                }
                printf("esperamos 60 segundos\n");
        }
        return (EXIT_SUCCESS);
}