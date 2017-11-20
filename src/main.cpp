#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "AgeCards.hpp"

int main(void){ 

    std::vector<AgeCard> Age1 = InitAgeCardDeck("AgeCards1.json");

    

    for(auto x : Age1){
        x.PrintCard("");
        std::cout << std::endl;
    }

    std::cout  << Age1.size() << " Hi!" << std::endl;



}
