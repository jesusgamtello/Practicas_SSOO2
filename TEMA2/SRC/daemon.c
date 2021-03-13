/********************************************************
 * Project:         Práctica 1 de Sistemas Operativos II
 * 
 * Program name:    daemon.c
 * 
 * Author:          Jesus Gamero Tello
 *
 * Purpose:         Este es el demonio que se ejecutara en segundo plano cada 60 segundos para realizar la copia de seguridad 
 *                  de nuestros archivos 
 *
 *********************************************************/
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


int main()
{
        mkdir("COPIA_SEGURIDAD", 0777);
        while (1)
        {
                if (system("cp -r ESTUDIANTES COPIA_SEGURIDAD") == -1)
                {
                        printf("error haciendo la copia de seguridad\n");
                        return (EXIT_FAILURE);
                }

                sleep(60);
        }
        return (EXIT_SUCCESS);
}