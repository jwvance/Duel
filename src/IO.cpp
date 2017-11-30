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

bool SetUpPlayerNames(std::vector<Player>& players){
    bool p1 = false, p2 = false;
    std::string inStr;

    std::cout << "Enter name for player 1: ";
    getline(std::cin, inStr, '\n');
    players[0].playerName = inStr;

    std::cout << "Enter name for player 2: ";
    getline(std::cin, inStr, '\n');
    players[1].playerName = inStr;

    return true;
}