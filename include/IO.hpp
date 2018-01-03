#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include <iostream>
#include "Player.hpp"

//Read which number the player chooses
int CollectInput(int numOptions);

//opens asciiTitle.txt and prints the contents to the console
void PrintTitleScreen(void);

//prints a visual that indicates the position of the military pawn
void PrintMilitaryStanding(int PawnPosition);
// TODO:
// These SHOW functions could be implemented in IO to prevent player from getting too cluttered
// ShowCards() print out cards that player holds 
// ShowResources();
// ShowCoin();
// ShowProgressTokens();
// ShowWonders(); //prints wonders like this:  (x)Giza, ()Colossus   where (x) represents it being built  


#endif // IO_HPP 