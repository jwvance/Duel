#include "IO.hpp"
#include "Board.hpp"

enum States { one };

int main(void){

    PrintTitleScreen();

    Board board;

    enum States state = one;

    

    board.SetUpPlayerNames();
    
    //need to print out player's coins, resources, and VP
    board.ChooseCard();
    board.ChangeTurn();
    board.ChooseCard();


    //ChooseWonders()
    //RandomizeTurn()
    //then enter state machine
        //enter state InitAge where the new ages are set up. Board has enum for current Age

    //to end program, where ever input is collect, include an option to terminate program with ctrl-c

    /*
    while(1){
        switch (state){
            case one:

                break;

            default:
                ;

        }
            
    }
    */




    //States:                                             
    //PickCard <---> Buy, Build, Sell

    //endgame state: AddVPs
    //                                                    
    
    //add error message if player tries to pick unavailable card

}