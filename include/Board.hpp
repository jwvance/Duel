#ifndef BOARD_HPP
#define BOARD_HPP

#include "AgeCards.hpp"
#include "CardTree.hpp"
#include "Player.hpp"
#include "IO.hpp"
#include <vector>

enum Ages { First, Second, Third };

class Board{

    Ages curAge;
    int MilitaryPawn;    //0 is neutral, -9 is a player[0] victory, 9 is a player[1] victory
    std::vector<std::string> ProgressTokens;   //represent the 5 available progress tokens for the game
    std::vector<AgeCard> DiscardPile;
    bool turn;   //represents what turn it is

    std::vector<AgeCard> Age1;
    std::vector<Node*> firstAge;
    std::vector<Player> players;

    //init whole board using class constructor?

    //functions like NextAge(), MovePawn(), GetProgressToken(), HasWon()
    //turn can be a variable that keeps track of the turn, saved as a private variable in board
    

public:
    Board();
    void ChangeTurn(void);
    bool SetUpPlayerNames(void);
    void ChooseCard(void);
};


#endif // BOARD_HPP 