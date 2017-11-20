#include <vector>

enum cardType { rawResource, mfdResource, civil, science, commercial, military, guild };
enum scienceSym { noScience, globe, scale, sundial, mortar, pendulum, quill, wheel };
enum militaryStr { noSheild, oneShield, twoSheild, threeSheild };
enum resource { noResource, lumber, stone, clay, glass, papyrus }; 
enum chain { noChain, horseshoe, sword, castle, target, helmet, book, cog, lyre, 
             lamp, mask, pillar, moon, sun, water, temple, jug, barrel };


class AgeCard {
    unsigned int card_age, card_coinCost, card_VP, card_coinReward, card_str;
    std::string card_type, card_name, card_chainCost, card_chain, card_sym;
    std::vector<std::string> card_resourceCost, card_resourceReward;
   
public:
    AgeCard(std::string t, std::string n, unsigned int age, unsigned int coinc, std::vector<std::string> rc, std::string chainc, 
        std::vector<std::string> card_resourceReward, std::string c, unsigned int vp, unsigned int card_coinReward, std::string s, unsigned int str);

    void PrintCard(std::string complexity);

};

std::vector<AgeCard> InitAgeCardDeck(std::string fileName);






class ProgressToken {
    
};
