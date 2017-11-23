#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "AgeCards.hpp"
#include "CardTree.hpp"

int main(void){ 

    std::vector<AgeCard> Age1 = InitAgeCardDeck("AgeCards1.json");

    std::vector<Node*> firstAge = InitFirstAge(Age1);

    //for(auto& x : firstAge) x->ac.PrintCard();


    std::vector<int> avail = AvailableCards(firstAge);


    for(auto& x : avail) firstAge[x]->ac.PrintCard();

}
