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
	exec/SSOOIIGLE prueba.txt es 4

clean:
	rm -r $(DIR)