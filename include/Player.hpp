#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AgeCards.hpp"
#include <vector>

class Player {

    //player has cards, coins, wonders
    std::vector<AgeCard*> cards;
    //std::vector<Wonders*> Wonders;
    int coins;
    std::vector<std::string> chains;
    std::vector<std::string> resources;


public:
    Player();

    int GetCoins(void);
    void UpdateCoins(int coin);

    std::vector<AgeCard*> GetCards(void);
    void AddCard(AgeCard* card);

    bool hasChain(std::string chain);
    std::vector<std::string> hasResources(std::vector<std::string> resources);
    bool hasCoin(int cost);

};

std::vector<Player> InitPlayers(void);







#endif // PLAYER_HPP 