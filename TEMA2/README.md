# PRIMERA PRACTICA SISTEMAS OPERATIVOS II

En la carpeta _UTILS_ podemos encontrar el fichero estudiantes.txt el cual contine el dni, nota del ultimo examen y modelo de examen correspondiente a cada estudiante, asi como la carpeta _MODELOSEXAMEN_ que contiene los tres modelos del examen (A,B,C) en formato .pdf

En la carpeta _SRC_ nos encontramos los archivos fuentes en .c compuesto por PA.c, PB.c, PC.c y PD.c los cuales son hijos lanzados por el manager.c. También encontramos el daemon.c que se encargara de realizar una copia de seguridad de los archivos generados cada 60 segundos 

Para ejecutar el programa simplemente abrir una terminal en la carpeta del proyecto y ejecutar: 
 ```
make
```
Lo que compilara los fuentes y los ejecutara creando la carpeta _ESTUDIANTES_ la cual contiene directorios con el dni de cada alumno con un .txt con la nota necesaria en el siguiente examen y el modelo de examen correspondiente.

Para eliminar todo simplemente ejecutar: 
```
make clean
```

Limpiara todas las carpetas y el log.txt
