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


    std::vector<int> avail = AvailableCards(firstAge);
    PrintInfo(firstAge, avail);

    //type name of card you'd like to pick up
    //need to uncover cards beneath
    //need to add card to players hand

    PickCard("Glassworks", players[0], firstAge);
    PickCard("Press", players[0], firstAge);
    PickCard("Garrison", players[0], firstAge);
    PickCard("Palisade", players[0], firstAge);

    std::vector<AgeCard*> cardey = players[0].GetCards();
    for(auto& card : cardey){
        std::cout << card->GetName() << std::endl;
    }
    //print out cards that player holds
    //add error message if player tries to pick unavailable card

    std::vector<int> avail2 = AvailableCards(firstAge);
    PrintInfo(firstAge, avail2);



}
