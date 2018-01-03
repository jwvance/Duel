#include "IO.hpp"


int CollectInput(int numOptions){
    //recieve number as input
    int myNum;
    do {
        std::cout << "Enter a number between 1 and " << numOptions << ": ";
        while(!(std::cin >> myNum)){
            std::cout << "Enter a number between 1 and " << numOptions << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(myNum == -1) std::exit(0);
    } while(myNum > numOptions || myNum == 0);
    return myNum;
}

void PrintTitleScreen(void){
    std::ifstream file;
    file.open("asciiTitle.txt", std::ios::in);
    
    std::string line;
    if (file){ // same as: if (myfile.good())
        while (getline(file, line)){ // same as: while (getline( myfile, line ).good())
            std::cout << line << std::endl;
        }
        file.close();
    }else{
        std::cout << "file open failed" << std::endl;
    }     
}

void PrintMilitaryStanding(int PawnPosition){
    
    PawnPosition += 9;
    int PawnShift = PawnPosition * 3 + 2;

    //determine position of military pawn
    //3  = -9
    //7  = -8
    //11 = -7
    std::cout << "                  --- MILITARY STATUS --- " << std::endl;
    std::cout << "◤▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬◥" << std::endl;
    while(PawnShift--){ std::cout << " "; }
    std::cout << "◆" << std::endl;
    std::cout << "  ✪  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ◇  Ω  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ✪ " << std::endl;
    //std::cout << "      [-5 coin]   [-2 coin]                       [-2 coin]   [-5 coin]     " << std::endl;
    std::cout << "◣▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬◢\n" << std::endl;

}