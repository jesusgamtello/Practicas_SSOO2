/********************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    PD.c
 * 
 * Author:          Jesus Gamero Tello
 *
 * Purpose:         Esta clase se ejecutara cuando se produzca una interrupcion por teclado 
 *
 *********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(){
    if (system("rm -R ESTUDIANTES") == -1){
        printf("error intentando limpiar directorios, PD\n");
        return EXIT_FAILURE;
    }

return EXIT_SUCCESS;
}