/**************************************************************
 * Project:         Práctica 2 
 * 
 * Program name:    SSOOIIGLE.cpp
 
 * Author:          Jesús Gamero Tello
 * 
 * Date created:    14/4/2021
 * 
 * Purpose:         The input is a file.txt this program read it and search the word 
 *                  who is specified. Also can be specified the numbers of threads.
 * 
 ****************************************************************/

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
#include <queue>
#include "../include/colors.h"
#include "result.cpp"

std::vector<std::thread>    vthreads;
std::queue <final_result>   final_queue;
std::queue <final_result>   aux_queue;
std::mutex                  sem;

void                        start_message();
int                         count_total_lines(std::string book);
void                        read_file(std::string book, std::string word_argv,int id,int start, int end);
void                        find_word(std::string word_argv, int number_of_lines, std::string line, int id, int start, int end);
void                        divide_in_threads(std::string book,std::string word_argv,int num_threads, int number_of_lines);
void                        order_queue(int id);
void                        print();
std::string                 clean_word(std::string word_read);
int main(int argc, char* argv[])
{
    if (argc != 4 ) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <file_name> <word> <thread_number>" << std::endl;
        return 1;
    }else{
        start_message();
        std::string     book                =   argv[1];
        std::string     word_argv           =   argv[2];
        int             num_threads         =   std::stoi(argv[3]);
        int             number_of_lines     =   count_total_lines(book);
        divide_in_threads(book,word_argv,num_threads,number_of_lines);
    }
    
    
    

}
void start_message(){
    std::cout << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "II" << BOLDBLUE << "GL" << BOLDGREEN << "E" << BOLDRED<< RESET << std::endl;
}
/******************************************************
 * Function:    count_total_lines
 * Date:     14/4/2021
 * Input arguments:  book book's path
 * Purpose:          Count the number of the specified file
 ******************************************************/
int count_total_lines(std::string book){
    std::string     line;
    int             number_of_lines     =   0;
    std::string     path                =   "./utils/"+book;
    std::ifstream   file (path);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            number_of_lines++;
                
        }
        file.close();
        
    }else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 
    return number_of_lines;
}
/******************************************************
 * Function:    clean_word
 * Date:     14/4/2021
 * Input arguments:  word_read word read in each line
 * Purpose:          Clean the words of strange characters
 ******************************************************/
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
/******************************************************
 * Function:    find_word
 * Date:     14/4/2021
 * Input arguments:  word_argv word specified, number_of_lines book's number of line,
 *                   id thread id, start where the thread start,
 *                   end where the thread end  
 * Purpose:          find the word who we are looking for 
 ******************************************************/
void find_word(std::string word_argv, int number_of_lines, std::string line,int id, int start, int end)
{
    std::istringstream          entire_line(line);
    std::string                 word_read;
    std::vector<std::string>    vect;
    vect.push_back(" ");
    while (entire_line >> word_read)
    {
        vect.push_back(word_read);
    }
    vect.push_back(" ");

    for (int i = 0; i < vect.size(); i++)
    {
                        word_read       =   vect[i];
        std::string     word_to_print   =   vect[i];
        std::transform(word_read.begin(), word_read.end(), word_read.begin(), ::tolower);
      
        word_read = clean_word(word_read);

        if ((word_argv.compare(word_read)) == 0)
        {
            if ((vect[i].compare(word_to_print)) == 0)
            {

                
                final_result result (id,number_of_lines,start,end,vect[i-1],vect[i],vect[i+1]);     /********************* CREACION DE OBJETO!!!!!!!! *********************/
                sem.lock();
                aux_queue.push(result);
                sem.unlock();
            }
        }
    }
}
/******************************************************
 * Function:    read_file
 * Date:     14/4/2021
 * Input arguments:  book name, word_argv word specified, id thread id, start where the thread start,
 *                   en where the thread end
 * Purpose:          read the file and try to find the word
 ******************************************************/
void read_file(std::string book, std::string word_argv, int id,int start, int end){
    std::string                 word_read, line;
    std::vector <std::string>   vector_of_words;
    int                         number_of_lines         =   1;
    std::string                 path                    =   "./utils/"+book;
    std::ifstream               file (path);
    if (file.is_open())
    {
        while (number_of_lines <= end)
        {
            std::getline(file, line, '\n');
            if (number_of_lines >= start)
            {
               
                find_word(word_argv, number_of_lines, line, id, start, end);
            }

            number_of_lines++;
        }
        file.close();
    }

    else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 

}
/******************************************************
 * Function:    divide_in_threads
 * Date:     14/4/2021
 * Input arguments:  the book to read, the word specified in the makefile, num_threads num of threads specified,
 *                   number_of_lines book's number of lines
 * Purpose:          divide the file in threads to search simultaneous results
 ******************************************************/
void divide_in_threads(std::string book, std::string word_argv,int num_threads,int number_of_lines){
    int     start       =   0;
    int     end         =   0;
    int     size_task   =   number_of_lines/num_threads;
    int     id          =   0;
    for (int i = 0; i < num_threads; i++){
        start           =   (i * size_task) +1;
        end             =   (start + size_task) - 1;
        if (i == num_threads - 1) end = number_of_lines;
        id++;


        vthreads.push_back(std::thread(read_file,book,word_argv,id,start,end));
    }
    std::for_each(vthreads.begin(),vthreads.end(), std::mem_fn(&std::thread::join));
    for (int i = 1 ;i< num_threads + 1; i++){
        order_queue(i);
        
    }
    print();
   
}
/******************************************************
 * Function:    order_queue
 * Date:     14/4/2021
 * Input arguments:  id, the thread_id to store in the queue 
 * Purpose:          Order the queue to print it later
 ******************************************************/
void order_queue(int id){
  
    std::queue <final_result>   queue           =   aux_queue;
    int                         j               =   0;
    int                         initial_size    =   aux_queue.size();
      while (!queue.empty()){
        
        if (queue.front().get_id () == id){
            
            final_queue.push(queue.front());
            queue.pop() ;
        }
        else queue.pop();
        
        j++;
        
        
    }
   
}
/******************************************************
 * Function:    print
 * Date:     14/4/2021  
 * Purpose:          Print the final queue with the results
 ******************************************************/
void print(){

    int     id  =   1;
    while (!final_queue.empty())
    {
        if (final_queue.front().get_id() == id)
        {
            std::cout << BOLDRED << "Hilo " << final_queue.front().get_id() << RESET;
        }
        else
        {
            std::cout << std::endl;
            std::cout << BOLDBLUE << "Hilo " << final_queue.front().get_id();
            while(id!=final_queue.front().get_id()) id++;
        }
        //std::cout << BOLDRED << "Hilo " << final_queue.front().get_id() << RESET;
        std::cout << " inicio: " << final_queue.front().get_start_thread_line();
        std::cout << " - final: " << final_queue.front().get_end_thread_line();
        std::cout << " :: línea " << final_queue.front().get_line();
        std::cout << " :: ... " << final_queue.front().get_behind_word() << " " << final_queue.front().get_exact_word() << " " << final_queue.front().get_after_word();
        std::cout << " ... " << std::endl;

        final_queue.pop();
    }

    std::cout<<std::endl;
}
