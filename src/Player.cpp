#include "Player.hpp"


Player::Player() {
    coins = 7;
}

int Player::GetCoins(void){
    return this->coins;
}

void Player::UpdateCoins(int coin){

}

std::vector<AgeCard*> Player::GetCards(void){
    return this->cards;
}

void Player::AddCard(AgeCard* card){

}

//create vector of type player, fill with two instances of player
std::vector<Player> InitPlayers(void){

    std::vector<Player> players;

    players.push_back(Player());
    players.push_back(Player());

    return players;
}