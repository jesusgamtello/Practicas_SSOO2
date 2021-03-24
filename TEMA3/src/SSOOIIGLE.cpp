#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <mutex>
#include <fstream>
#include <string>

void desde_donde(std::vector<int> v, int inicio, int valor_fin);
void read_file(std::string book);
int main(int argc, char* argv[])
{
    if (argc != 4 ) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <nombre_fichero> <palabra> <numero_hilos>" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    
    std::vector<int> v_naleatorios;
    std::vector<std::thread> vhilos;
    read_file(argv[1]);
    /*int size_task = LIMITE/NUM_MAX_HILOS;
    long suma = 0;
    for (int i = 0; i < LIMITE; i++)
    {
        int numero = rand();
        v_naleatorios.push_back(numero);
        suma +=numero;
    }
    std::cout << "La suma acumulada es: " << suma << std::endl;
    int valor = 0;
    int inicio = 0;
    for (int i = 0; i < NUM_MAX_HILOS; i++)
    {

        inicio = i * size_task;
        valor = (inicio + size_task) - 1;
        if (i == NUM_MAX_HILOS - 1) valor = LIMITE - 1;
        vhilos.push_back(std::thread(desde_donde, v_naleatorios, inicio, valor));
    }

    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));*/

}
void read_file(std::string book){
    std::string line;
    std::string path;
    path = "./utils/"+book;
    std::cout << path<< std::endl;
    std::ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
        std::cout << line << std::endl;
        }
        myfile.close();
    }

    else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 

}