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
    std::string playerName;

    std::cout << "Enter name for player 1: ";
    getline(std::cin, playerName, '\n');
    this->players[0].SetName(playerName);

    std::cout << "Enter name for player 2: ";
    getline(std::cin, playerName, '\n');
    this->players[1].SetName(playerName);
    std::cout << std::endl;

    return true;
}

void Board::ChooseCard(void){
    std::cout << this->players[turn].GetName() << ", choose a card:" << std::endl;
    std::vector<int> avail = AvailableCards(firstAge);
    PrintInfo(firstAge, avail);

    //recieve number as input
    int myNum;
    do {
        std::cout << "Enter a number between 1 and " << avail.size() << ": ";
        std::cin >> myNum;
    } while(myNum > avail.size() || myNum == 0);

    myNum = avail[myNum-1];
    std::string cardName = firstAge[myNum]->ac.GetName();
    PickCard(cardName, this->players[turn], this->players[!turn], firstAge);
    std::cout << "\n\n\n";
}