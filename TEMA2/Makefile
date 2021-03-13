CC = gcc
FLAGS = -lpthread -lrt

EXEC = createdir manager PA PB PC PD daemon 
FILES = log.txt COPIA_SEGURIDAD/ ESTUDIANTES/ 
DIR = EXEC

all: compile run



compile: $(EXEC)

createdir: 
	mkdir $(DIR)
manager: 
	$(CC) $(FLAGS) SRC/manager.c -o EXEC/manager
PA:
	$(CC) SRC/PA.c -o EXEC/PA
PB:
	$(CC) SRC/PB.c -o EXEC/PB
PC:
	$(CC) SRC/PC.c -o EXEC/PC
PD:
	$(CC) SRC/PD.c -o EXEC/PD
daemon:
	$(CC) SRC/daemon.c -o EXEC/daemon
run:
	EXEC/manager

clean:
	rm -r $(FILES) $(DIR)
	