#include "CardTree.hpp"
#include <iostream>

std::pair<int,int> Node::GetPair(void){
    return this->covers;
}

void Node::SetPair(int first, int second){
    this->covers = std::make_pair(first,second);
}

std::vector<Node*> InitFirstAge(std::vector<AgeCard> Age1){
    //assign proper links between cards
    std::vector<Node*> Age1Tree(20);

    int i = 0;
    for(auto& card : Age1){
        Age1Tree[i++] = new Node(card);
        if(i == 20) break;
    }

    Age1Tree[0]->SetPair(2,3);
    Age1Tree[1]->SetPair(3,4);

    Age1Tree[2]->SetPair(5,6);
    Age1Tree[3]->SetPair(6,7);
    Age1Tree[4]->SetPair(7,8);

    Age1Tree[5]->SetPair(9,10);
    Age1Tree[6]->SetPair(10,11);
    Age1Tree[7]->SetPair(11,12);
    Age1Tree[8]->SetPair(12,13);

    Age1Tree[9]->SetPair(14,15);
    Age1Tree[10]->SetPair(15,16);
    Age1Tree[11]->SetPair(16,17);
    Age1Tree[12]->SetPair(17,18);
    Age1Tree[13]->SetPair(18,19);

    return Age1Tree;
}

//returns vector that holds indexes of available cards
std::vector<int> AvailableCards(const std::vector<Node*>& AgeCard){
    std::vector<int> avail;
    for(auto & card : AgeCard){
        if(card->GetPair() == std::make_pair(-1,-1)){
            avail.push_back(&card - &AgeCard[0]);
        }
    }
    return avail;
}

void PrintInfo(const std::vector<Node*>& AgeCard, const std::vector<int> avail){
    std::cout << "Available cards:" << std::endl;

    for(auto& card : avail){
        if(AgeCard[card]->ac.GetType() == "resource") AgeCard[card]->ac.PrintInfo_Resource();
        if(AgeCard[card]->ac.GetType() == "science") AgeCard[card]->ac.PrintInfo_Science();
        if(AgeCard[card]->ac.GetType() == "military") AgeCard[card]->ac.PrintInfo_Military();
        if(AgeCard[card]->ac.GetType() == "civil") AgeCard[card]->ac.PrintInfo_Civil();
        if(AgeCard[card]->ac.GetType() == "commercial") AgeCard[card]->ac.PrintInfo_Commercial();

    }
}

//create print function to print card details
//eg print("names")
//eg print("symbol")
//eg print("military strength")





//card cover pattern (cover represents the 1 or 2 cards that protects cards underneath it from being used)
//the vector Age1Tree contains all of the cards for the first age
//each card has a pair of numbers which represent the cards covering it. A -1 means no card.

//r00 (r10, r11)
//r01(r11,r12)

//r10(r20,r21)
//r11(r21,r22)
//r12(r22,r23)

//r20(r30,r31)
//r21(r31,r32)
//r22(r32,r33)
//r23(r33,r34)

//r30(r40,r41)
//r31(r41,r42)
//r32(r42,r43)
//r33(r43,r44)
//r34(r44,r45)
