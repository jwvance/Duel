#include "gtest/gtest.h"
#include "AgeCards.hpp"
#include "CardTree.hpp"
#include "Player.hpp"
#include "IO.hpp"
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
            EXPECT_EQ(card.GetCoinRew(),0);
            EXPECT_EQ(card.GetChainCost(),"noChain");
            EXPECT_TRUE(card.GetResCost().empty());
        }
        //find Scriptorium card, and check its fields
        if(card.GetName() == "Stable"){
            EXPECT_EQ(card.GetType(),"military");
            EXPECT_EQ(card.GetCoinRew(),0);
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
    int numAvail = 0;
    for(auto& card : firstAge){
        if(card->isAvailable) numAvail++;
    }
    EXPECT_EQ(numAvail,20);   //check that only 20 cards are in play
    EXPECT_EQ(AvailableCards(firstAge).size(),6);    //only 6 cards should be available at the beginning of play
}
TEST_F(CardTreeTest, UncoverCard)
{
    //remove two consecutive cards, which will unveil card underneath
    PickCard(firstAge.rbegin()[3]->ac.GetName(), players[0], players[1], firstAge); 
    EXPECT_EQ(AvailableCards(firstAge).size(),5);    //only 5 cards should be available after picking one up
    PickCard(firstAge.rbegin()[4]->ac.GetName(), players[0], players[1], firstAge);
    EXPECT_EQ(AvailableCards(firstAge).size(),5);    //only 5 cards should be available after picking two up, and exposing one
}
TEST_F(CardTreeTest, RemoveAll)
{
    players[0].UpdateCoins(50);   //give player plenty of coins to buy all cards
    int i = 0;
    //remove all cards, until AvailableCards().size() returns 0
    while(AvailableCards(firstAge).size()){
        PickCard(firstAge.rbegin()[i++]->ac.GetName(), players[0], players[1], firstAge);  
        //std::cout <<  players[0].GetCoins() << std::endl;
    }
    EXPECT_EQ(AvailableCards(firstAge).size(),0);
}


/////////////////////
/////Player//////////
/////////////////////
class PlayerTest : public ::testing::Test
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

        //set all cards available to pick up to test player class
        for(auto& card : firstAge){
            card->SetPair(-1,-1);
            card->isAvailable = true;
        }
    }
    //virtual void TearDown(){ //delete [] &Age1; }
};
TEST_F(PlayerTest, TradeCosts3) //trade costs 3 since opponent owns required resource
{
    EXPECT_TRUE(PickCard("Logging Camp", players[0], players[1], firstAge)); 
    for(auto& card : firstAge){
        if(card->ac.GetName() == "Stable"){  //minus 3 coin since player 0 owns lumber
            EXPECT_TRUE(PickCard("Stable", players[1], players[0], firstAge)); 
            EXPECT_EQ(players[1].GetCoins(), 4); 
        }
    }
}
TEST_F(PlayerTest, TradeCosts2) //trade is free since both players own resource
{
    EXPECT_TRUE(PickCard("Logging Camp", players[0], players[1], firstAge)); 
    EXPECT_TRUE(PickCard("Lumber Yard", players[1], players[0], firstAge)); 
    for(auto& card : firstAge){
        if(card->ac.GetName() == "Stable"){  //minus 3 coin since player 0 owns lumber
            EXPECT_TRUE(PickCard("Stable", players[1], players[0], firstAge)); 
            EXPECT_EQ(players[1].GetCoins(), 7); 
        }
    }
}
TEST_F(PlayerTest, CanAfford)
{
    //check that player can afford card, they are initialized with 7 coins
    for(auto& card : firstAge){
        if(card->ac.GetName() == "Garrison"){  //minus 2 coin
            EXPECT_TRUE(PickCard("Garrison", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Wood Reserve"){  //minus 3 coin
            EXPECT_TRUE(PickCard("Wood Reserve", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Palisade"){  //minus 2 coin
            EXPECT_TRUE(PickCard("Palisade", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Lumber Yard"){  //free card
            EXPECT_TRUE(PickCard("Lumber Yard", players[0], players[1], firstAge)); 
        }
    }
    EXPECT_FALSE(PickCard("Glassworks", players[0], players[1], firstAge));  //cost 1, but player has 0 coin
}
TEST_F(PlayerTest, CollectResources)
{
    //check that player object holds all resources collected
    for(auto& card : firstAge){
        if(card->ac.GetName() == "Lumber Yard"){ 
            EXPECT_TRUE(PickCard("Lumber Yard", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Logging Camp"){ 
            EXPECT_TRUE(PickCard("Logging Camp", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Clay Pool"){  
            EXPECT_TRUE(PickCard("Clay Pool", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Stone Pit"){ 
            EXPECT_TRUE(PickCard("Stone Pit", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Glassworks"){ 
            EXPECT_TRUE(PickCard("Glassworks", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Press"){ 
            EXPECT_TRUE(PickCard("Press", players[0], players[1], firstAge)); 
        }
    }
    EXPECT_EQ(players[0].GetResources().size(), 6);  
}
TEST_F(PlayerTest, CollectChain)
{
    //check that player object holds all chains collected
    for(auto& card : firstAge){
        if(card->ac.GetName() == "Stable"){  
            EXPECT_TRUE(PickCard("Stable", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Garrison"){  
            EXPECT_TRUE(PickCard("Garrison", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Scriptorium"){  
            EXPECT_TRUE(PickCard("Scriptorium", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Theater"){  
            EXPECT_TRUE(PickCard("Theater", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Altar"){ 
            EXPECT_TRUE(PickCard("Altar", players[0], players[1], firstAge)); 
        }
        if(card->ac.GetName() == "Tavern"){  
            EXPECT_TRUE(PickCard("Tavern", players[0], players[1], firstAge)); 
        }
    }
    EXPECT_EQ(players[0].GetChains().size(), 6);  
}
TEST_F(PlayerTest, GoldDiscount)
{
    //check that gold discount applys to players
    for(auto& card : firstAge){  //first aquire gold stone card for player[0]
        if(card->ac.GetName() == "Stone Pit"){  
            EXPECT_TRUE(PickCard("Stone Pit", players[1], players[0], firstAge)); 
        }
        if(card->ac.GetName() == "Stone Reserve"){  //player 0 gets stone for 1 gold
            EXPECT_TRUE(PickCard("Stone Reserve", players[0], players[1], firstAge)); 
        }
    }
    for(auto& card : firstAge){   //then check if discount works
        if(card->ac.GetName() == "Baths"){  //player 0 buys stone
            EXPECT_TRUE(PickCard("Baths", players[0], players[1], firstAge)); 
        }
    }
    EXPECT_EQ(players[0].GetCoins(), 3);
}
//test gold card logic
    



TEST(IOTest, title)
{
    PrintTitleScreen();
}




int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}