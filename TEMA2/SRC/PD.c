#include <stdio.h>
#include <stdlib.h>

int main(){
    if (system("rm -R ESTUDIANTES") == -1){
        printf("error intentando limpiar directorios, PD\n");
        return EXIT_FAILURE;
    }

return EXIT_SUCCESS;
}