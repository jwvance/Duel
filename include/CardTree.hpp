#ifndef CARD_TREE_HPP
#define CARD_TREE_HPP


#include "AgeCards.hpp"
#include "Player.hpp"
#include <vector>
#include <iostream>



class Node {
private:
    std::pair<int, int> covers;

public:
    Node(AgeCard card) : ac(card) {   //TODO:: move constructor to C file
        covers = std::make_pair(-1,-1);
        isVisable = false;
        isAvailable = true;
    }

    AgeCard ac;
    bool isVisable;   //if face up
    bool isAvailable;   //if card is still in play

    void SetPair(int first, int second);
    std::pair<int,int> GetPair(void);
};

//Initialize the first age tree data structure 
std::vector<Node*> InitFirstAge(std::vector<AgeCard> Age1);

//return a vector<Node*> containing the available cards to draw
std::vector<int> AvailableCards(const std::vector<Node*>& AgeCard);

//print stats for available cards to draw
void PrintInfo(const std::vector<Node*>& AgeCard, const std::vector<int> avail);

//traverses cards and updates which cards are available
bool UncoverCard(std::string cardName, std::vector<Node*>& age);

//pick up card specified by player, adds it to their hand, updates gameboard
bool PickCard(std::string cardName, Player& player, Player& opponent, std::vector<Node*>& age);

#endif // CARD_TREE_HPP 