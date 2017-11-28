#include "Player.hpp"


Player::Player() {
    this->coins = 7;
}

int Player::GetCoins(void){
    return this->coins;
}

void Player::UpdateCoins(int coin){
    this->coins += coin;
}

std::vector<AgeCard*> Player::GetCards(void){
    return this->cards;
}

void Player::AddCard(AgeCard* card){
    this->cards.push_back(card);
    if(card->GetCoin()) this->coins += card->GetCoin();
    if(card->GetResRew().size() > 1){
        this->resources.insert( this->resources.end(), card->GetResRew().begin(), card->GetResRew().end() );
    }else if(card->GetResRew().size()) {
        this->resources.push_back(card->GetResRew().front());
    }
    //TODO:: apply military shields
    //TODO:: apply science symbols
}

bool Player::hasChain(std::string chain){
    for(auto& c : this->chains){
        if(c == chain) return true;
    }
    return false;
}

std::vector<std::string> Player::hasResources(std::vector<std::string> reqRes){
    //make a copy of players resources to return

    std::vector<std::string> own_copy, return_resources;
    own_copy = this->resources;

    //iterate through required resources
    for(auto& req_res : reqRes){
        for(int i = 0; i < own_copy.size(); i++){
            if(req_res == own_copy[i]){   //if player owns that resource, remove it from the copied array
                own_copy[i].erase();
                break;
            }
        }
        return_resources.push_back(req_res);    //else, add missing resources to a new array to be returned
    }
    return return_resources;
}

bool Player::hasCoin(int cost){
    if(this->coins <= cost) return true;
    return false;
}

//create vector of type player, fill with two instances of player
std::vector<Player> InitPlayers(void){

    std::vector<Player> players;

    players.push_back(Player());
    players.push_back(Player());

    return players;
}