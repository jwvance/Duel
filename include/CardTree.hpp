#ifndef CARD_TREE_HPP
#define CARD_TREE_HPP


#include "AgeCards.hpp"
#include <vector>
#include <iostream>



class Node {
private:
    std::pair<int, int> covers;

public:
    Node(AgeCard card) : ac(card) {
        covers = std::make_pair(-1,-1);
        isVisable = false;
        isAvailable = false;
        isTaken = false;
    }

    AgeCard ac;
    bool isVisable;   //if face up
    bool isAvailable;   //if no cards are blocking
    bool isTaken;

    void SetPair(int first, int second);
    std::pair<int,int> GetPair(void);
};

//Initialize the first age tree data structure 
std::vector<Node*> InitFirstAge(std::vector<AgeCard> Age1);

//return a vector<Node*> containing the available cards to draw
std::vector<int> AvailableCards(const std::vector<Node*>& AgeCard);

//print stats for available cards to draw
void PrintInfo(const std::vector<Node*>& AgeCard, const std::vector<int> avail);

#endif // CARD_TREE_HPP 