#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


int main()
{
        mkdir("COPIA_SEGURIDAD",0777);
        while (1)
        {
                if (system("cp -r ESTUDIANTES COPIA_SEGURIDAD") == -1)
                {
                        printf("error haciendo la copia de seguridad\n");
                        return (EXIT_FAILURE);
                }
                
                sleep(20);
        }
        return (EXIT_SUCCESS);
}