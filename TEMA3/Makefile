CC = g++
FLAGS = -pthread -std=c++11

EXEC = createdir ssooiigle  
DIR = exec

all: compile run



compile: $(EXEC)

createdir: 
	mkdir $(DIR)
ssooiigle: 
	$(CC) src/SSOOIIGLE.cpp -o exec/SSOOIIGLE $(FLAGS)

run:
	exec/SSOOIIGLE Actitud_de_vencedor.txt hola 4

clean:
	rm -r $(DIR)