#include "IO.hpp"

void PrintStringWithDelay(std::string str, int delay){
     for(auto& sym : str){
        std::cout << sym << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    } 
}

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

void PrintSplashScreen(std::string fileName, int delay){
    std::ifstream file;
    file.open(fileName, std::ios::in);
    
    int speed = 0;
    std::string line;
    if (file){ 
        while (getline(file, line)){ 
            PrintStringWithDelay(line + "\n", delay - (speed / 3));
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
    std::cout << "                  ";
    PrintStringWithDelay("--- MILITARY STATUS --- \n", 25);
    PrintStringWithDelay("◤▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬◥\n", 1);
    while(PawnShift--){ std::cout << " "; }
    std::cout << "◆" << std::endl;
    PrintStringWithDelay("  ✪  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ◇  Ω  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ◇  ✪\n", 5);
    //std::cout << "      [-5 coin]   [-2 coin]                       [-2 coin]   [-5 coin]     " << std::endl;
    PrintStringWithDelay("◣▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬◢\n\n", 1);
}