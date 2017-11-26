#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "AgeCards.hpp"
#include "CardTree.hpp"
#include "Player.hpp"

int main(void){ 

    std::vector<AgeCard> Age1 = InitAgeCardDeck("AgeCards1.json");
    std::vector<Node*> firstAge = InitFirstAge(Age1);
    std::vector<Player> players = InitPlayers();

    //std::cout << players[1].GetCoins() << std::endl;
    

    std::vector<int> avail = AvailableCards(firstAge);
    PrintInfo(firstAge, avail);

}
