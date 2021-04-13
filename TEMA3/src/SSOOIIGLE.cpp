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

std::vector<std::thread> vthreads;
std::queue <final_result>final_queue;
std::queue <final_result>aux_queue;
std::mutex sem;

void start_message();
int count_total_lines(std::string book);
void read_file(std::string book, std::string word_argv,int id,int start, int end);
void find_word(std::string word_argv, int number_of_lines, std::string line, int id, int start, int end);
void divide_in_threads(std::string book,std::string word_argv,int num_threads, int number_of_lines);
void print_queue(int id);
void print();
std::string clean_word(std::string word_read);
int main(int argc, char* argv[])
{
    if (argc != 4 ) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <file_name> <word> <thread_number>" << std::endl;
        return 1;
    }else{
        start_message();
        std::string book = argv[1];
        std::string word_argv = argv[2];
        int num_threads = std::stoi(argv[3]);
        int number_of_lines = count_total_lines(book);
        divide_in_threads(book,word_argv,num_threads,number_of_lines);
        //read_file(book, word_argv);
    }
    
    
    

}
void start_message(){
    std::cout << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "II" << BOLDBLUE << "GL" << BOLDGREEN << "E" << BOLDRED<< RESET << std::endl;
}
int count_total_lines(std::string book){
 std::string  line, path;
    int number_of_lines = 0;
    path = "./utils/"+book;
    std::ifstream file (path);
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
void find_word(std::string word_argv, int number_of_lines, std::string line,int id, int start, int end)
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

                //std::cout << vect[i - 1] << " " << vect[i] << " " << vect[i + 1] << " .....numero de linea " << number_of_lines << std::endl;
                final_result result (id,number_of_lines,start,end,vect[i-1],vect[i],vect[i+1]);     /********************* CREACION DE OBJETO!!!!!!!! *********************/
                sem.lock();
                final_queue.push(result);
                sem.unlock();
            }
        }
    }
}
void read_file(std::string book, std::string word_argv, int id,int start, int end){
    std::string word_read, line, path;
    std::vector <std::string> vector_of_words;
    int number_of_lines = 1;
    path = "./utils/"+book;
    std::ifstream file (path);
    if (file.is_open())
    {
        /*while ( getline (file,line) )
        {
            number_of_lines++;
            
                find_word(word_argv, number_of_lines, line, id, start, end);
                
            
        }
        file.close();*/
        while (number_of_lines <= end)
        {
            std::getline(file, line, '\n');
            if (number_of_lines >= start)
            {
               
                find_word(word_argv, number_of_lines, line, id, start, end);
            }

            number_of_lines++;
        }
    }

    else std::cout << "Unable to open file or file doesn't exist"<< std::endl; 

}

void divide_in_threads(std::string book, std::string word_argv,int num_threads,int number_of_lines){
    int start = 0;
    int end = 0;
    int size_task = number_of_lines/num_threads;
    int id = 0;
    for (int i = 0; i < num_threads; i++){
        start = (i * size_task) +1;
        end = (start + size_task) - 1;
        if (i == num_threads - 1) end = number_of_lines;
        id++;


        vthreads.push_back(std::thread(read_file,book,word_argv,id,start,end));
    }
    std::for_each(vthreads.begin(),vthreads.end(), std::mem_fn(&std::thread::join));
    for (int i = 1 ;i< num_threads + 1; i++){
        print_queue(i);
    }
    print();
   
}

void print_queue(int id){
    /*while(!final_queue.empty()){
        std::cout<<"Hilo "<<final_queue.front().get_id ();
        std::cout<<" inicio: "<< final_queue.front().get_start_thread_line();
        std::cout<<" - final: "<< final_queue.front().get_end_thread_line();
        std::cout<<" :: línea "<<final_queue.front().get_line();
        std::cout<<" :: ... "<<final_queue.front().get_behind_word ()<<" "<<final_queue.front().get_exact_word ()<<" "<<final_queue.front().get_after_word ();
		std::cout<<" ... "<<std::endl;
        
		final_queue.pop();
	}
    
    std::cout<<std::endl;*/
    std::queue <final_result>queue = final_queue;
    //int id = 1;
    int j = 0;
    int initial_size = final_queue.size();
    //while(!final_queue.empty()){
      while (!queue.empty()){
        
        if (queue.front().get_id () == id){
            
            aux_queue.push(queue.front());
            queue.pop() ;
        }
        else queue.pop();
        
        j++;
        
        
    }
   
}
void print(){


 /*while(!final_queue.empty()){
        std::cout<<"Hilo "<<final_queue.front().get_id ();
        std::cout<<" inicio: "<< final_queue.front().get_start_thread_line();
        std::cout<<" - final: "<< final_queue.front().get_end_thread_line();
        std::cout<<" :: línea "<<final_queue.front().get_line();
        std::cout<<" :: ... "<<final_queue.front().get_behind_word ()<<" "<<final_queue.front().get_exact_word ()<<" "<<final_queue.front().get_after_word ();
		std::cout<<" ... "<<std::endl;
        
		final_queue.pop();
	}*/
    
    std::cout<<std::endl;

     while(!aux_queue.empty()){
        std::cout<<"Hilo "<<aux_queue.front().get_id ();
        std::cout<<" inicio: "<< aux_queue.front().get_start_thread_line();
        std::cout<<" - final: "<< aux_queue.front().get_end_thread_line();
        std::cout<<" :: línea "<<aux_queue.front().get_line();
        std::cout<<" :: ... "<<aux_queue.front().get_behind_word ()<<" "<<aux_queue.front().get_exact_word ()<<" "<<aux_queue.front().get_after_word ();
		std::cout<<" ... "<<std::endl;
        
		aux_queue.pop();
	}
    
    std::cout<<std::endl;
}
