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

void desde_donde(std::vector<int> v, int inicio, int valor_fin);
void read_file(std::string book, std::string word_argv);
void find_word(std::string word_argv, std::string word, int number_of_lines);
int main(int argc, char* argv[])
{
    if (argc != 4 ) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <file_name> <word> <thread_number>" << std::endl;
        return 1;
    }else{
        read_file(argv[1], argv[2]);
    }
    
    
    

}
void find_word(std::string word_argv, std::string word_read, int number_of_lines){
    //std::transform(word_read.begin(), word_read.end(), word_read.begin(), ::tolower);    // convierte a minuscula     
    for (int i = 0, len = word_read.size(); i < len; i++)
        {
            if (ispunct(word_read[i]) && i!=0)
            {
                word_read.erase(i--, 1);
                if ((word_argv.compare(word_read)) == 0)
                {
                    break;
                }
                len = word_read.size();
            }if (!isalpha(word_read[i]) && i == 0)
            {
                word_read.erase(i--,1);
                if ((word_argv.compare(word_read)) == 0)
                {
                    break;
                }
                len = word_read.size();
                

            }
            
        }
        if ((word_argv.compare(word_read)) == 0)
        {
            std::cout << word_argv << " is equal to " << word_read << std::endl;
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
            std::istringstream entire_line(line);
            
            while(entire_line >> word_read){
                //std::cout << word_read.length() << std::endl;
                //std::cout << number_of_lines << std::endl;
                find_word(word_argv, word_read,number_of_lines);
                
            }
                
        }
        file.close();
    }

    else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 

}
