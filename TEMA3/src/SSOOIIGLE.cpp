#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <mutex>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "../include/colors.h"
#include "result.cpp"

void start_message();
void read_file(std::string book, std::string word_argv);
void find_word(std::string word_argv, int number_of_lines, std::string line);
std::string clean_word(std::string word_read);
int main(int argc, char* argv[])
{
    if (argc != 4 ) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <file_name> <word> <thread_number>" << std::endl;
        return 1;
    }else{
        start_message();
        read_file(argv[1], argv[2]);
    }
    
    
    

}
void start_message(){
    std::cout << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "II" << BOLDBLUE << "GL" << BOLDGREEN << "E" << BOLDRED<< std::endl;
}
std::string clean_word(std::string word_read){
    for (int i = 0, len = word_read.size(); i < len; i++)
    {
        if (ispunct(word_read[i]) && i != 0)
        {
            word_read.erase(i--, 1);

            len = word_read.size();
        }
        if (!isalpha(word_read[i]) && i == 0)
        {
            word_read.erase(i--, 1);

            len = word_read.size();
        }
    }

    return word_read;
}
void find_word(std::string word_argv, int number_of_lines, std::string line)
{
    //std::transform(word_read.begin(), word_read.end(), word_read.begin(), ::tolower);    // convierte a minuscula
    std::istringstream entire_line(line);
    std::string word_read;
    std::vector<std::string> vect;
    vect.push_back(" ");
    while (entire_line >> word_read)
    {
        vect.push_back(word_read);
    }
    vect.push_back(" ");

    for (int i = 0; i < vect.size(); i++)
    {
        word_read = vect[i];
        std::string word_to_print = vect[i];
        std::transform(word_read.begin(), word_read.end(), word_read.begin(), ::tolower);
      
        word_read = clean_word(word_read);

        if ((word_argv.compare(word_read)) == 0)
        {
            if ((vect[i].compare(word_to_print)) == 0)
            {

                std::cout << vect[i - 1] << " " << vect[i] << " " << vect[i + 1] << " .....numero de linea " << number_of_lines << std::endl;
                final_result result (1,number_of_lines,0,50,vect[i-1],vect[i],vect[i+1]);     /********************* CREACION DE OBJETO!!!!!!!! *********************/
            }
        }
    }
}
void read_file(std::string book, std::string word_argv){
    std::string word_read, line, path;
    int number_of_lines = 0;
    path = "./utils/"+book;
    std::ifstream file (path);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            number_of_lines++;
            
                find_word(word_argv, number_of_lines, line);
                
            
                
        }
        file.close();
    }

    else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 

}
