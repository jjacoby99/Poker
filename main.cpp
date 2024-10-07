#include <iostream>
#include "sim.h"

int main() {
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
    return 0;
}