#ifndef BOARD_HPP
#define BOARD_HPP

#include "AgeCards.hpp"
#include <vector>

class Board{

    int MilitaryPawn;    //0 is neutral, -9 is a player[0] victory, 9 is a player[1] victory
    std::vector<std::string> ProgressTokens;   //represent the 5 available progress tokens for the game
    std::vector<AgeCard> DiscardPile;


    //use int to keep track of turn, use ^= 1 to switch turn
    //use function CHANGE_TURN() to change turn to next


    //initialize deck and players in here?
    //from main call SetUpBoard()
    //functions like NextAge(), MovePawn(), GetProgressToken(), HasWon()
    //turn can be a variable that keeps track of the turn, saved as a private variable in board
    
    //start game with beautiful splash screen (maybe clear a few lines) and a
        //prompt to enter a name for player one
        //D U E L - 2018 Jason Vance

        //Enter a name for player 1


public:
    Board() {
        MilitaryPawn = 0;
    }
};

#endif // BOARD_HPP 