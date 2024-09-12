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

bool Hand::IsStraightFlush(std::vector<Card>& hand)
{
    return Hand::IsStraight(hand) && Hand::IsFlush(hand);
}

bool Hand::IsQuads(std::vector<Card>& hand)
{
    std::sort(hand.begin(),hand.end(),CompareFaceValue);

    int count = 1;
    for(int i = 1; i < 5; i++)
    {
        int cur = static_cast<int>(hand[i].GetValue());
        int last = static_cast<int>(hand[i-1].GetValue());

        if(cur == last)
        {
            count++;
        }
        else
        {
            count = 1;
        }
        
        if(count == 4)
        {
            return true;
        }
    }
    return count == 4;
}

bool Hand::IsFullHouse(std::vector<Card>& hand)
{
    std::map<int,int> occur = Hand::CountReccuring(hand);
    
    bool hasTrips = false;
    bool hasPair = false;
    for(auto el: occur)
    {
        if(el.second == 3)
        {
            hasTrips = true;
        }
        else if(el.second == 2)
        {
            hasPair = true;
        }
    }
    return hasTrips && hasPair;
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


bool Hand::IsStraight(std::vector<Card>& hand)
{
    if(hand.size() != 5)
    {
        throw std::runtime_error("Hand is not 5 cards\n");
    }

    // sort into accending order
    // ace is high under this sort
    std::sort(hand.begin(), hand.end(), CompareFaceValue);

    
    // check wheel straight
    if( hand[4].GetValue() == Card::FaceValue::ACE &&
        hand[0].GetValue() == Card::FaceValue::TWO && 
        hand[1].GetValue() == Card::FaceValue::THREE &&
        hand[2].GetValue() == Card::FaceValue::FOUR &&
        hand[3].GetValue() == Card::FaceValue::FIVE) 
        {
            return true;
        }
    
    
    for(int i = 1; i < 5; i++)
    {        
        int last = static_cast<int>(hand[i-1].GetValue());
        int cur = static_cast<int>(hand[i].GetValue());
        
        if(cur == 1)
        {
            // ace gets assigned 14
            cur += 13;
        }

        if(last + 1 != cur) 
        {
            return false;
        }
    }
    return true;
}

bool Hand::IsThreeOfAKind(std::vector<Card>& hand)
{
    std::sort(hand.begin(),hand.end(),CompareFaceValue);

    int count = 1;
    for(int i = 1; i < 5; i++)
    {
        int cur = static_cast<int>(hand[i].GetValue());
        int last = static_cast<int>(hand[i-1].GetValue());

        if(cur == last)
        {
            count++;
        }
        else
        {
            count = 1;
        }

        if(count == 3)
        {
            return true;
        }
    }
    return count == 3;
}

bool Hand::IsTwoPair(std::vector<Card>& hand)
{
    std::map<int, int> occur = Hand::CountReccuring(hand);

    int pairCount = 0;
    for(auto el: occur)
    {   
        if(el.second == 2)
        {
            pairCount++;
        }
    }
    
    return pairCount == 2;
}

bool Hand::IsPair(std::vector<Card>& hand)
{
    std::sort(hand.begin(),hand.end(),CompareFaceValue);

    int count = 1;
    for(int i = 1; i < 5; i++)
    {
        int cur = static_cast<int>(hand[i].GetValue());
        int last = static_cast<int>(hand[i-1].GetValue());

        if(cur == last)
        {
            return true;
        }
        
    }
    return false;
}

std::map<int, int> Hand::CountReccuring(std::vector<Card>& hand)
{
    std::sort(hand.begin(),hand.end(),CompareFaceValue);

    std::map<int, int> occurrences;
    int count = 1;

    int cur = 0;
    int next = 0; 
    for(int i = 0; i < 4; i++)
    {
        cur = static_cast<int>(hand[i].GetValue());
        next = static_cast<int>(hand[i+1].GetValue());
        if(cur == next)
        {
            count++;
        }
        if(cur != next)
        {
            occurrences[cur] = count;
            count = 1;
        }

    }
    occurrences[next] = count;
    return occurrences;
}

std::vector<Card> Hand::BestHand()
{

}