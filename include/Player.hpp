#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AgeCards.hpp"
#include <vector>

class Player {

    //player has cards, coins, wonders
    std::vector<AgeCard*> cards;
    //std::vector<Wonders*> Wonders;
    int coins;

public:
    Player();

    int GetCoins(void);
    void UpdateCoins(int coin);

    std::vector<AgeCard*> GetCards(void);
    void AddCard(AgeCard* card);


};

std::vector<Player> InitPlayers(void);







#endif // PLAYER_HPP 