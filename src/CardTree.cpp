#include "CardTree.hpp"
#include <iostream>

std::pair<int,int> Node::GetPair(void){
    return this->covers;
}

void Node::SetPair(int first, int second){
    this->covers = std::make_pair(first,second);
}

//each card has a pair of numbers which represent the cards covering it. -1 means no card
std::vector<Node*> InitFirstAge(std::vector<AgeCard> Age1){
    //assign proper links between cards
    std::vector<Node*> Age1Tree(23);

    int i = 0;
    for(auto& card : Age1){
        Age1Tree[i++] = new Node(card);
        //if(i == 20) break;
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

    //keep in deck but unavailable (for testing)
    Age1Tree[20]->isAvailable = false;
    Age1Tree[21]->isAvailable = false;
    Age1Tree[22]->isAvailable = false;

    return Age1Tree;
}

//returns vector that holds indexes of available cards
std::vector<int> AvailableCards(const std::vector<Node*>& AgeCard){
    std::vector<int> avail;
    for(auto & card : AgeCard){
        if(card->GetPair() == std::make_pair(-1,-1) && card->isAvailable){
            avail.push_back(&card - &AgeCard[0]);
        }
    }
    return avail;
}

void PrintInfo(const std::vector<Node*>& AgeCard, const std::vector<int> avail){
    int count = 1;
    for(auto& card : avail){
        std::cout << "  " << count++ << ") ";
        if(AgeCard[card]->ac.GetType() == "resource") AgeCard[card]->ac.PrintInfo_Resource();
        if(AgeCard[card]->ac.GetType() == "science") AgeCard[card]->ac.PrintInfo_Science();
        if(AgeCard[card]->ac.GetType() == "military") AgeCard[card]->ac.PrintInfo_Military();
        if(AgeCard[card]->ac.GetType() == "civil") AgeCard[card]->ac.PrintInfo_Civil();
        if(AgeCard[card]->ac.GetType() == "commercial") AgeCard[card]->ac.PrintInfo_Commercial();
    }
}

//traverses the cards in play and updates the necessary pair values
bool UncoverCard(std::string cardName, std::vector<Node*>& age){
    bool cardFound = false;
    int index;
    //first locate index of cardName
    for(auto& card : age){
        if(card->ac.GetName() == cardName){
            index = &card - &age[0];
            cardFound = true;
            break;
        }
    }

    //then search tree for pairs that contain that index,
    //if part of a pair matches, update pair value to -1
    for(auto& card : age){
        if(card->GetPair().first == index){
            card->SetPair(-1,card->GetPair().second);
        }
        if(card->GetPair().second == index){
            card->SetPair(card->GetPair().first,-1);
        }
        if(card->GetPair() == std::make_pair(-1,-1)){
            card->isVisable = true;
        }
    }
    return cardFound;
}

//add card named cardName to player's hand if they can afford it, mark isAvailable as false
bool PickCard(std::string cardName, Player& player, Player& opponent, std::vector<Node*>& age){
    //first make sure card is available, check status of isAvailable and num pair
    for(auto& card : age){
        //player can take if card is available and nothing is covering it
        if(card->ac.GetName() == cardName && card->isAvailable && card->GetPair() == std::make_pair(-1,-1)){    
            bool canAquire = false, hasChain = false;   //flag for tracking how player will pay for card
            int cost = 0;    //tracks amount player has pay bank for resources if they don't own them

            //check if can aquire with chain, then pay nothing
            hasChain = canAquire = player.hasChain(card->ac.GetChainCost());

            //check if can aquire with resources
            if(!canAquire){
                //compare resources owned by player to required resources. return addtional resources needed
                std::vector<std::string> missingRes;
                std::pair<bool, std::vector<std::string>> resPair = player.hasResources(card->ac.GetResCost());
                canAquire = resPair.first;
                missingRes = resPair.second;

                //if player doesn't have resources, calculate coin cost of those resources
                if(!canAquire){
                    std::vector<std::string> opponentRes = opponent.GetResources();
                    for(auto& missing : missingRes){

                        bool hasGold = false;
                        //find any gold cards for the current resource and apply discount
                        for(auto& goldCard : player.GetResources()){
                            if(goldCard == missing + "_1"){
                                hasGold = true;
                                break;
                            }
                        }
                        if(hasGold){
                            cost += 1;
                            continue;
                        }

                        bool hasRes = false;    //flag to check if opponent has resource
                        //check if opponent has resources, then cost += 3
                        for(auto& oppRes : opponentRes){
                            if(missing == oppRes){       //compare player resource to opponent resource
                                cost += 3;
                                hasRes = true;
                                break;
                            }
                        }
                        if(!hasRes){    //if opponent doesn't have resource
                            cost += 2;
                        }
                    }
                }
            }

            //calculate total coin
            cost += card->ac.GetCoinCost();
            canAquire = player.hasCoin(cost);

            //player doesn't pay for card if they have chain
            if(canAquire && !hasChain){
                //subtract cost from player's total
                player.UpdateCoins(-cost);
            }

            //finally, add card to player's hand since they can afford it
            if(canAquire){
                //add card to player's hand, add coin, resources
                player.AddCard(&(card->ac)); 
                
                //uncover free cards on the table
                UncoverCard(cardName, age);
            
                card->isAvailable = false;
                return true;
            }
            return false; //not enough coins
        }
    }
    return false;  //card not available   
}

bool SellCard(std::string cardName, Player& player, std::vector<Node*>& age){
    for(auto& card : age){
        //player can sell if card is available and nothing is covering it
        if(card->ac.GetName() == cardName && card->isAvailable && card->GetPair() == std::make_pair(-1,-1)){
            UncoverCard(cardName, age);
            card->isAvailable = false;
            player.UpdateCoins(player.GetSellBonus());
            return true;
        }
    }
    return false;
}