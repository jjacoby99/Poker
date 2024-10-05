#include <gtest/gtest.h>
#include "sim.h"
#include <iostream>

TEST(SimTests, Equity)
{
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ac(Card::Suit::CLUBS, Card::FaceValue::ACE);

    std::pair<Card, Card> h1 = {As, Ac};

    Card Kh(Card::Suit::HEARTS, Card::FaceValue::KING);
    Card Kd(Card::Suit::DIAMONDS, Card::FaceValue::KING);

    std::pair<Card, Card> h2 = {Kh, Kd};


    Sim s1(h1, h2);

    double numSims = 10000;
    double h1Equity = s1.CalculateEquity(numSims);

    std::cout << "Aces vs Kings equity preflop: " << h1Equity << ". Ran " << numSims << " simulations." << std::endl;

}

TEST(SimTests, DrawingDead)
{
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ac(Card::Suit::CLUBS, Card::FaceValue::ACE);

    std::pair<Card, Card> h1 = {As, Ac};

    Card Kh(Card::Suit::HEARTS, Card::FaceValue::KING);
    Card Kd(Card::Suit::DIAMONDS, Card::FaceValue::KING);

    std::pair<Card, Card> h2 = {Kh, Kd};

    //flop where Kings is drawing dead vs aces
    Card Ad(Card::Suit::DIAMONDS, Card::FaceValue::ACE);
    Card Ah(Card::Suit::HEARTS, Card::FaceValue::ACE);
    Card Ks(Card::Suit::SPADES, Card::FaceValue::KING);

    std::vector<Card> flop = {Ah, Ad, Ks};
    std::vector<Card> holeCards = {As, Ac, Kh, Kd};

    Board b(flop);
    Deck d; 
    d.RemoveCards(flop);
    d.RemoveCards(holeCards);

    Sim s1(h1, h2, b, d);


    double numSims = 10;
    double h1Equity = s1.CalculateEquity(numSims);


    EXPECT_EQ(h1Equity, 1.0);

}

TEST(SimTests, Flipping)
{
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ks(Card::Suit::SPADES, Card::FaceValue::KING);

    std::pair<Card, Card> h1 = {As, Ks};

    Card Qh(Card::Suit::HEARTS, Card::FaceValue::QUEEN);
    Card Qd(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN);

    std::pair<Card, Card> h2 = {Qh, Qd};

    Sim s1(h1, h2);
    double numSims = 10000;
    double h1Equity = s1.CalculateEquity(numSims);

    std::cout << "Ran " << numSims << " sims to determine " << h1.first.ToString() << h1.second.ToString() << " equity vs " << h2.first.ToString() << h2.second.ToString() << ": "<< h1Equity << std::endl;
}

TEST(SimTests, WeirdCase)
{
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ac(Card::Suit::CLUBS, Card::FaceValue::ACE);

    std::pair<Card, Card> h1 = {As, Ac};

    Card Kh(Card::Suit::HEARTS, Card::FaceValue::KING);
    Card Kd(Card::Suit::DIAMONDS, Card::FaceValue::KING);

    std::pair<Card, Card> h2 = {Kh, Kd};

    Card Qs(Card::Suit::SPADES, Card::FaceValue::QUEEN);
    Card Jd(Card::Suit::DIAMONDS, Card::FaceValue::JACK);
    Card Ts(Card::Suit::SPADES, Card::FaceValue::TEN);
    Card Nc(Card::Suit::CLUBS, Card::FaceValue::NINE);
    Card TwoH(Card::Suit::HEARTS, Card::FaceValue::TWO);

    std::vector<Card> runout = {Qs, Jd, Ts, Nc, TwoH};

    Board b;
    b.AddCards(runout);

    Deck d;

    Sim s(h1, h2, b, d);

    std::cout << s.CalculateEquity(1);


}