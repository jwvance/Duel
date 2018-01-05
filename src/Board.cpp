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
    std::cout << "\n" << this->players[this->turn].GetName() << ", choose a card to buy:" << std::endl;

    std::vector<int> avail = AvailableCards(firstAge);
    int myNum = CollectInput(avail.size());
    myNum = avail[myNum-1];
    std::string cardName = firstAge[myNum]->ac.GetName();
    
    //add specified card to player's hand, then update military
    if(PickCard(cardName, this->players[turn], this->players[!turn], firstAge)){
        UpdateMilitaryPawn(cardName, Age1);
    }

}

void Board::SellCard(void){
    std::cout << "\n" << this->players[this->turn].GetName() << ", you may sell a card for: ";
    std::cout << this->players[this->turn].GetSellBonus() << std::endl;

    std::vector<int> avail = AvailableCards(firstAge);
    int myNum = CollectInput(avail.size());
    myNum = avail[myNum-1];
    std::string cardName = firstAge[myNum]->ac.GetName();

    ::SellCard(cardName, this->players[this->turn], firstAge);
}

void Board::PrintTurn(void){

    //PrintStringWithDelay("\n\n\n\n\n\n      ▣      ▣      ▣\n\n\n", 50);
    PrintStringWithDelay("\n\n\n\n\n\n\n\n\n", 70);
    PrintMilitaryStanding(this->MilitaryPawn);

    PrintStringWithDelay("▶   ▶   ▶  " + this->players[this->turn].GetName() + "'s turn  ◀   ◀   ◀\n\n", 30);

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << " ◇ coins:" << this->players[this->turn].GetCoins() << std::endl;
    std::cout << " ◇ resources: ";
    if(this->players[this->turn].GetResources().size() == 0) std::cout << "none";
    for(auto& res : this->players[this->turn].GetResources()){
        std::cout << res << " ";
    }
    std::cout << "\n\n";

    PrintStringWithDelay("▬▬▬▬▬▬▬▬▬▬▬▬ Available cards ▬▬▬▬▬▬▬▬▬▬▬▬\n", 10);
    std::vector<int> avail = AvailableCards(firstAge);
    PrintInfo(firstAge, avail);
    PrintStringWithDelay("\n▬   ▬   ▬   ▬   ▬   ▬   ▬   ▬   ▬   ▬   ▬ ", 10);
}

int Board::ChooseAction(void){

    std::cout << "\n";
    PrintStringWithDelay(this->players[this->turn].GetName() + ", choose an action: \n", 50);
    
    std::cout << "  1) buy a card\n";
    std::cout << "  2) sell a card\n";
    std::cout << "  3) build a wonder\n";

    return CollectInput(3);
}

void Board::UpdateMilitaryPawn(std::string cardName, std::vector<AgeCard> cards){
    for(auto& card : cards){   //loop through cards to find matching card
        if(card.GetName() == cardName && card.GetType() == "military"){  //check if card has type "military" 
            this->turn ? (this->MilitaryPawn += card.GetShields()) : (this->MilitaryPawn -= card.GetShields());   //adjust military accordingly
        }
    }
}