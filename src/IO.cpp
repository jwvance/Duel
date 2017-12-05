#include "IO.hpp"

void PrintTitleScreen(void){
    std::ifstream file;
    file.open("asciiTitle.txt", std::ios::in);
    
    std::string line;
    if (file){ // same as: if (myfile.good())
        while (getline(file, line)){ // same as: while (getline( myfile, line ).good())
            std::cout << line << std::endl;
        }
        file.close();
    }else{
        std::cout << "file open failed" << std::endl;
    }     
}