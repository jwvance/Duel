#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include <iostream>
#include "Player.hpp"

class IO{



public:



};

//opens asciiTitle.txt and prints the contents to the console
void PrintTitleScreen(void);

bool SetUpPlayerNames(std::vector<Player>& players);


#endif // IO_HPP 