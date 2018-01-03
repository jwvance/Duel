#include "Board.hpp"

Board::Board(){
    curAge = First;
    MilitaryPawn = 0;
    Age1 = InitAgeCardDeck("AgeCards1.json");
    firstAge = InitFirstAge(Age1);
    players = InitPlayers();
    turn = false;
}

void Board::ChangeTurn(void){
    this->turn = !this->turn;
}

bool Board::SetUpPlayerNames(void){
    bool p1 = false, p2 = false;
    std::string playerName1, playerName2;

    std::cout << "Enter name for player 1: ";
    getline(std::cin, playerName1, '\n');
    this->players[0].SetName(playerName1);

    do{
        std::cout << "Enter name for player 2: ";
        getline(std::cin, playerName2, '\n');
        if(playerName2 == playerName1) std::cout << "Please enter a unique name!" << std::endl;
    }while(playerName2 == playerName1);
    
    this->players[1].SetName(playerName2);
    std::cout << std::endl;

    return true;
}

void Board::ChooseCard(void){
    std::cout << "\n\n" << this->players[this->turn].GetName() << ", choose a card:" << std::endl;
    std::vector<int> avail = AvailableCards(firstAge);
    PrintInfo(firstAge, avail);

    int myNum = CollectInput(avail.size());

    myNum = avail[myNum-1];
    std::string cardName = firstAge[myNum]->ac.GetName();
    PickCard(cardName, this->players[turn], this->players[!turn], firstAge);
    std::cout << "\n\n\n";
}

void Board::PrintTurn(void){
    std::cout << "--- " << this->players[this->turn].GetName() << "'s turn ---" << std::endl;
    std::cout << "  coins:" << this->players[this->turn].GetCoins() << std::endl;
    std::cout << "  resources: ";
    if(this->players[this->turn].GetResources().size() == 0) std::cout << "none";
    for(auto& res : this->players[this->turn].GetResources()){
        std::cout << res << " ";
    }
    std::cout << "\n\n";
}

int Board::ChooseAction(void){

    std::cout << this->players[this->turn].GetName() << ", choose an action: " << std::endl;
    std::cout << "  1) buy a card\n";
    std::cout << "  2) sell a card\n";
    std::cout << "  3) build a wonder\n";

    return CollectInput(3);
}