#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "AgeCards.hpp"
#include "json.hpp"

using json = nlohmann::json;

AgeCard::AgeCard(std::string t, std::string n, unsigned int age, unsigned int coinc, std::vector<std::string> rc,
        std::string chainc, std::vector<std::string> rr, std::string c, unsigned int vp, unsigned int coinr, std::string s, unsigned int str)
        :   card_type(t),
            card_name(n),
            card_age(age),
            card_coinCost(coinc),
            card_resourceCost(rc),
            card_chainCost(chainc),
            card_resourceReward(rr),
            card_chain(c),
            card_VP(vp),
            card_coinReward(coinr),
            card_sym(s),
            card_str(str)
        {};

void AgeCard::PrintCard(std::string complexity){
    
    std::cout << card_name << ", " << card_type << " card, Age " << card_age <<  ".";
    
    if(complexity == "complex"){
        std::cout << "\nCost: " << 
            card_coinCost << " coins";
        if(card_resourceCost[0] != "noResource"){ 
            std::cout << ", or ";
            for(auto x : card_resourceCost) { std::cout << x << " "; }
        } 
        if(card_chainCost != "noChain"){
            std::cout << ", or free with " << card_chainCost;
        }
        std::cout << "." << std::endl;

        std::cout << "This card grants: ";
        if(card_VP != 0) { std::cout << card_VP << " VPs, "; }
        if(card_coinReward != 0 ) { std::cout << card_coinReward << " coins, "; }
        if(card_sym != "noScience") { std::cout << "the " << card_sym << " symbol, "; }
        if(card_str != 0) { std::cout << card_str << " sheilds."; }
    }

}

std::vector<AgeCard> InitAgeCardDeck(std::string fileName){
    std::string t, name, chainCost, ch, ss;
    unsigned int age, coinCost, VP, coinR, sheild;
    std::vector<std::string> resourceCost, resourceReward;

    // read a JSON file
    
    std::ifstream json_stream(fileName);
    json json_data;
    try{
        json_stream >> json_data;
    }catch(std::exception &e) { std::cout << "FUCK" << e.what() << std::endl; }
   
    std::cout << "FUCK" << std::endl;

    //prepare card deck
    std::vector<AgeCard> deck;

    //fetch first card data from json file
    auto deserialized_json = json_data["Cards"].get<std::vector<std::unordered_map<std::string, json>>>();

    for (int i = 0; i < deserialized_json.size(); i++){
        //deserialize json and construct a card object
        for(auto j : deserialized_json[i]){
            //std::cout << j.first << ": " << j.second << '\n';
            if(j.first == "type") t = j.second;
            if(j.first == "name") name = j.second;
            if(j.first == "age") age = j.second;
            if(j.first == "coinCost") coinCost = j.second;
            if(j.first == "resourceCost") resourceCost.push_back(j.second[0]);
            if(j.first == "chainCost") chainCost = j.second;
            if(j.first == "resourceReward") resourceReward.push_back(j.second[0]);
            if(j.first == "chain") ch = j.second;
            if(j.first == "VP") VP = j.second;
            if(j.first == "coinReward") coinR = j.second;
            if(j.first == "sym") ss = j.second;
            if(j.first == "shield") sheild = j.second;
        }
        deck.push_back(AgeCard(t, name, age, coinCost, resourceCost, chainCost, resourceReward, ch, VP, coinR, ss, sheild));
    } 
    return deck;
}