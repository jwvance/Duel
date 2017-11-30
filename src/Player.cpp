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

std::vector<std::string> Player::GetResources(void){
    return this->resources;
}

std::vector<std::string> Player::GetChains(void){
    return this->chains;
}

std::vector<AgeCard*> Player::GetCards(void){
    return this->cards;
}

void Player::AddCard(AgeCard* card){
    this->cards.push_back(card);
    if(card->GetCoinRew()) this->coins += card->GetCoinRew();
    if(card->GetResRew().size() > 1){
        this->resources.insert( this->resources.end(), card->GetResRew().begin(), card->GetResRew().end() );
    }else if(card->GetResRew().size()) {
        this->resources.push_back(card->GetResRew().front());
    }
    if(card->GetChainRew() != "noChain") this->chains.push_back(card->GetChainRew()); 
    //TODO:: apply military shields
    //TODO:: apply science symbols
}

bool Player::hasChain(std::string chain){
    for(auto& c : this->chains){
        if(c == chain) return true;
    }
    return false;
}

std::pair<bool, std::vector<std::string>> Player::hasResources(std::vector<std::string> reqRes){
    //make a copy of players resources to return

    std::vector<std::string> own_copy, return_resources;
    own_copy = this->resources;
    bool resFound = false;

    //iterate through required resources
    for(auto& req_res : reqRes){
        //compare against each resource the player owns
        for(int i = 0; i < own_copy.size(); i++){
            if(req_res == own_copy[i]){   //if player owns that resource, remove it from the copied array
                resFound = true;
                own_copy[i].erase();  
                break;
            }
        }
        if(!resFound) return_resources.push_back(req_res);    //add missing resources to a new array to be returned
        resFound = false;
    }
    bool canAfford = false;
    if(return_resources.size() == 0) canAfford = true;
    return std::make_pair(canAfford, return_resources);
}

bool Player::hasCoin(int cost){
    if(this->coins >= cost) return true;
    return false;
}

//create vector of type player, fill with two instances of player
std::vector<Player> InitPlayers(void){

    std::vector<Player> players;

    players.push_back(Player());
    players.push_back(Player());

    return players;
}