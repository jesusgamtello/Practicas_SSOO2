#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
     pid_t pid, sid;
        
        /* Fork off the parent process */
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);
                       
                
        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
                printf("fallo en la creacion del sid\n");
                exit(EXIT_FAILURE);
        }
    while (1)
    {
        system("cp -r * /home/jesus/Desktop/copia");
        printf("esperamos 60 segundos\n");
        sleep(60);
    }
    return (EXIT_SUCCESS);
}