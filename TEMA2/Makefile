CC = gcc
FLAGS = -lpthread -lrt

EXEC = manager PA PB PC PD daemon
FILES = log.txt COPIA_SEGURIDAD/ ESTUDIANTES/

all: compile run

compile: $(EXEC)

manager: 
	$(CC) $(FLAGS) SRC/manager.c -o SRC/manager
PA:
	$(CC) SRC/PA.c -o SRC/PA
PB:
	$(CC) SRC/PB.c -o SRC/PB
PC:
	$(CC) SRC/PC.c -o SRC/PC
PD:
	$(CC) SRC/PD.c -o SRC/PD
daemon:
	$(CC) SRC/daemon.c -o SRC/daemon
run:
	SRC/manager

clean:
	rm -r $(FILES) 
	rm manager PA PB PC PD daemon