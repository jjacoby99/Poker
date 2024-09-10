#include "hand.h"
#include <iostream>
Hand::Hand(std::vector<Card> cards) : cards(cards) {}

bool Hand::CompareFaceValue(const Card& card1, const Card& card2)
{
    if(card1.GetValue() == card2.GetValue()) return false;

    if(card1.GetValue() == Card::FaceValue::ACE)
    {
        return false;
    }
    if(card2.GetValue() == Card::FaceValue::ACE)
    {
        return true;
    }
    return static_cast<int>(card1.GetValue()) < static_cast<int>(card2.GetValue());
}

void Hand::GetAllCombinations(std::vector<Card>& cards, std::vector<Card>& hand, std::vector<std::vector<Card>>& allHands, int idx, int start)
{
    if(idx == 5)
    {
        allHands.push_back(hand);
        return;
    }
    for (int i = start; i < cards.size(); i++) {
        hand[idx] = cards[i];
        GetAllCombinations(cards, hand, allHands, idx + 1, i + 1);
    }
}

std::vector<std::vector<Card>> Hand::GeneratePokerHands()
{
    std::vector<Card> hand(5);
    std::vector<std::vector<Card>> allHands;

    GetAllCombinations(this->cards, hand, allHands, 0, 0);

    return allHands;
}

bool Hand::IsRoyalFlush(std::vector<Card>& hand)
{
    if(hand.size() != 5)
    {
        throw std::runtime_error("Hand is not 5 cards\n");
    }
    std::sort(hand.begin(), hand.end(), CompareFaceValue);

    if(!Hand::IsFlush(hand)) return false;

    // know all the same suit
    if(hand[0].GetValue() != Card::FaceValue::TEN) return false;
    if(hand[1].GetValue() != Card::FaceValue::JACK) return false;
    if(hand[2].GetValue() != Card::FaceValue::QUEEN) return false;
    if(hand[3].GetValue() != Card::FaceValue::KING) return false;
    if(hand[4].GetValue() != Card::FaceValue::ACE) return false;

    return true;
}

bool Hand::IsFlush(std::vector<Card>& hand)
{
    if(hand.size() != 5)
    {
        throw std::runtime_error("Hand is not 5 cards\n");
    }
    Card::Suit last = hand[0].GetSuit();
    
    for(int i = 1; i < 5; i++)
    {
        if(hand[i-1].GetSuit() != hand[i].GetSuit()) return false;
    }

    return true;
}



std::vector<Card> Hand::BestHand()
{

}