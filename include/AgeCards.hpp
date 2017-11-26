#ifndef AGE_CARDS_HPP
#define AGE_CARDS_HPP

#include <vector>
#include <string>

/*
enum cardType { rawResource, mfdResource, civil, science, commercial, military, guild };
enum scienceSym { noScience, globe, scale, sundial, mortar, pendulum, quill, wheel };
enum militaryStr { noSheild, oneShield, twoSheild, threeSheild };
enum resource { noResource, lumber, stone, clay, glass, papyrus }; 
enum chain { noChain, horseshoe, sword, castle, target, helmet, book, cog, lyre, 
             lamp, mask, pillar, moon, sun, water, temple, jug, barrel };
*/

class AgeCard {
    unsigned int card_age, card_coinCost, card_VP, card_coinReward, card_str;
    std::string card_type, card_name, card_chainCost, card_chain, card_sym;
    std::vector<std::string> card_resourceCost, card_resourceReward;
   
public:
    AgeCard(std::string t, std::string n, unsigned int age, unsigned int coinc, std::vector<std::string> rc, std::string chainc, 
        std::vector<std::string> card_resourceReward, std::string c, unsigned int vp, unsigned int card_coinReward, std::string s, unsigned int str);

    void PrintCard(std::string complexity = "");

    std::string GetType(void) { return this->card_type; }
    std::string GetName(void) { return this->card_name; }

    void PrintInfo_Resource(void);
    void PrintInfo_Science(void);
    void PrintInfo_Military(void);
    void PrintInfo_Civil(void);
    void PrintInfo_Commercial(void);


    /*Maybe a customized print for each type of card,
    eg. PrintSci()
        PrintMil()
        PrintRes()
    */

};

std::vector<AgeCard> InitAgeCardDeck(std::string fileName);

class ProgressToken {
    
};


#endif // AGE_CARDS_HPP 