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
    std::string playerName;

public:
    Player();

    void SetName(std::string newName);
    std::string GetName(void);

    int GetCoins(void);
    void UpdateCoins(int coin);

    std::vector<std::string> GetResources(void);
    std::vector<std::string> GetChains(void);

    std::vector<AgeCard*> GetCards(void);
    void AddCard(AgeCard* card);

    bool hasChain(std::string chain);
    std::pair<bool, std::vector<std::string>> hasResources(std::vector<std::string> resources);
    bool hasCoin(int cost);

};

std::vector<Player> InitPlayers(void);







#endif // PLAYER_HPP 