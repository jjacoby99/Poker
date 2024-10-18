#include <gtest/gtest.h>
#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/player.h"
#include <string>

TEST(PlayerTests, Constructor)
{
    double stack = 100.0;
    std::string name = "Josh";

    Player p(stack, name);

    EXPECT_EQ(p.GetName(), name);
    EXPECT_EQ(p.GetStack(), stack);


}

TEST(PlayerTests, Bet)
{
    double stack = 100.0;
    std::string name = "Josh";

    Player p(stack, name);

    double bet = 14.4;

    p.Bet(bet);

    EXPECT_EQ(p.GetStack(), stack - bet);

    bet = 100.0;

    p.Bet(bet);
    EXPECT_EQ(p.GetStack(), 0.0);    
}

TEST(PlayerTests, SetHoleCards)
{
    double stack = 100.0;
    std::string name = "Josh";

    Player p(stack, name);

    std::vector<Card> cards = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE)};
    p.SetHoleCards(cards);

    for(int i = 0; i < 2; i++)
    {
        EXPECT_EQ(static_cast<int>(cards[i].GetValue()), static_cast<int>(p.GetHoleCards()[i].GetValue()));
        EXPECT_EQ(static_cast<int>(cards[i].GetSuit()), static_cast<int>(p.GetHoleCards()[i].GetSuit()));
    }
}

TEST(PlayerTests, BestHand)
{
    Card AceS(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card AceC(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card KingS(Card::Suit::SPADES, Card::FaceValue::KING);
    Card QueenS(Card::Suit::SPADES, Card::FaceValue::QUEEN);
    Card JackS(Card::Suit::SPADES, Card::FaceValue::JACK);
    Card TenS(Card::Suit::SPADES, Card::FaceValue::TEN);
    Card AceD(Card::Suit::DIAMONDS, Card::FaceValue::ACE);

    // best is a straight flush
    std::vector<Card> holeCards = {AceS, KingS};

    std::vector<Card> boardCards = {AceC, QueenS, JackS, TenS, AceD};
    std::vector<Card> cards = {AceS, AceC, KingS, QueenS, JackS, TenS, AceD};

    
    
    double stack = 100.0;
    std::string name = "Josh";

    Player p(stack, name);
    p.SetHoleCards(holeCards);

    p.DetermineBestHand(boardCards);

    std::vector<Card> playerResult = p.GetBestHand();
    Hand::HandRanking playerRanking = p.GetHandRanking();

    auto res = Hand::BestHand(cards);
    
    EXPECT_EQ(static_cast<int>(playerRanking), static_cast<int>(res.second));

    for(int i = 0; i < 5; i++)
    {
        EXPECT_EQ(static_cast<int>(playerResult[i].GetValue()), static_cast<int>(res.first[i].GetValue()));
        EXPECT_EQ(static_cast<int>(playerResult[i].GetSuit()), static_cast<int>(res.first[i].GetSuit()));
    }
}

