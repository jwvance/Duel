#include "IO.hpp"
#include "Board.hpp"

enum States { one };
enum Actions { BUY = 1, SELL, BUILD };

int main(void){

    Board board;   //init board
    enum Actions ACTION = BUY;
    PrintSplashScreen("asciiTitle.txt", 3);   //print title screen
    board.SetUpPlayerNames();

    PrintSplashScreen("Age1Splash.txt", 2);   //print intro to age 1
    

    //ChooseWonders()
    //RandomizeTurn()
    //then enter state machine
        //enter state InitAge where the new ages are set up. Board has enum for current Age

    //to end program, whenever input is collected, include an option to terminate program with ctrl-c

    //main loop
    while(1) { 
        //need to print current turn
        board.PrintTurn();
        
        
        ////need to print out player's coins, resources, and VP
        
        //check input for what player wants to do
        ACTION = static_cast<Actions>(board.ChooseAction());
        switch(ACTION) {
            case BUY:
                board.ChooseCard();     //TODO: after choosing card, say "aquired 'name of card'", next player's turn.
                break;

            case SELL:
                //std::cout << "Choose a card to sell for " << std::endl;
                board.SellCard();
                //TODO: finish SellCard()

                break;

            case BUILD:
                std::cout << "building" << std::endl;
                break;            
            
        }

        //let player choose between three keywords: buy, build, or sell
        //aquire info by typing: info 'cards' / 'wonders' / 'status'
            //eg:
                //Science: card 1, card 2
                //Military: card 1, card 2
                //gold cards: card 1


            //eg: military visualization





        
        board.ChangeTurn();
    }


    




    //States:                                             
    //PickCard <---> Buy, Build, Sell

    //endgame state: AddVPs
                                          
    

}