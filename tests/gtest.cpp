#include "gtest/gtest.h"
#include "AgeCards.hpp"
#include "CardTree.hpp"
#include "Player.hpp"
#include <iostream>

/////////////////////
/////AgeCard/////////
/////////////////////
class AgeCardTest : public ::testing::Test
{
protected:
    std::vector<AgeCard> Age1;
    virtual void SetUp()
    {      
        Age1 = InitAgeCardDeck("AgeCards1.json");
    }
    //virtual void TearDown(){ //delete [] &Age1; }
};
TEST_F(AgeCardTest, InitDeck)
{
    EXPECT_EQ(Age1.size(),23);   //check that 23 cards are initialized
    for(auto& card : Age1){
        //find Scriptorium card, and check its fields
        if(card.GetName() == "Scriptorium"){
            EXPECT_EQ(card.GetType(),"science");
            EXPECT_EQ(card.GetCoin(),0);
            EXPECT_EQ(card.GetChainCost(),"noChain");
            EXPECT_TRUE(card.GetResCost().empty());
        }
        //find Scriptorium card, and check its fields
        if(card.GetName() == "Stable"){
            EXPECT_EQ(card.GetType(),"military");
            EXPECT_EQ(card.GetCoin(),0);
            EXPECT_EQ(card.GetChainRew(),"horseshoe");
            EXPECT_EQ(card.GetResCost().front(),"lumber");
            EXPECT_EQ(card.GetShields(),1);
        }
    }
}


/////////////////////
/////CardTree////////
/////////////////////
class CardTreeTest : public ::testing::Test
{
protected:
    std::vector<AgeCard> Age1;
    std::vector<Node*> firstAge;
    std::vector<Player> players;
    virtual void SetUp()
    {      
        Age1 = InitAgeCardDeck("AgeCards1.json");
        firstAge = InitFirstAge(Age1);
        players = InitPlayers();
    }
    //virtual void TearDown(){ //delete [] &Age1; }
};
TEST_F(CardTreeTest, InitAge1)
{
    EXPECT_EQ(firstAge.size(),20);   //check that only 20 cards are in play
    EXPECT_EQ(AvailableCards(firstAge).size(),6);    //only 6 cards should be available at the beginning of play
    

}
TEST_F(CardTreeTest, UncoverCard)
{
    //remove two consecutive cards, which will unveil card underneath
    PickCard(firstAge.rbegin()[0]->ac.GetName(), players[0], firstAge);    
    EXPECT_EQ(AvailableCards(firstAge).size(),5);    //only 5 cards should be available after picking one up
    PickCard(firstAge.rbegin()[1]->ac.GetName(), players[0], firstAge);
    EXPECT_EQ(AvailableCards(firstAge).size(),5);    //only 5 cards should be available after picking two up, and exposing one
}
TEST_F(CardTreeTest, RemoveAll)
{
    int i = 0;
    //remove all cards, until AvailableCards().size() returns 0
    while(AvailableCards(firstAge).size()){
        PickCard(firstAge.rbegin()[i++]->ac.GetName(), players[0], firstAge);   
    }
    EXPECT_EQ(AvailableCards(firstAge).size(),0);
}


    

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}