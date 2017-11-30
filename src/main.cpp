#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "AgeCards.hpp"
#include "CardTree.hpp"
#include "Player.hpp"
#include "IO.hpp"

int main(void){

    PrintTitleScreen();

    std::vector<AgeCard> Age1 = InitAgeCardDeck("AgeCards1.json");
    std::vector<Node*> firstAge = InitFirstAge(Age1);
    std::vector<Player> players = InitPlayers();


    //optional
    //SetUpPlayerNames(players);

    //std::vector<int> avail = AvailableCards(firstAge);
    //PrintInfo(firstAge, avail);

  
    
    //print out cards that player holds
    //add error message if player tries to pick unavailable card




}
