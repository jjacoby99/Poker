#include "hand.h"
#include <iostream>
#include <functional>
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
    std::map<int,int> occur = Hand::CountRecurring(hand);
    
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
    std::map<int, int> occur = Hand::CountRecurring(hand);

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

std::map<int, int> Hand::CountRecurring(std::vector<Card>& hand)
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
            if(cur == 1) // account for aces always being high in pair, twopair, trips, fullhouse, quads
            {
                cur = 14;
            }
            occurrences[cur] = count;
            count = 1;
        }

    }
    if(next == 1)
    {
        next = 14;
    }
    occurrences[next] = count;
    
    return occurrences;
}
int Hand::CompareHands(std::vector<Card>& h1, std::vector<Card>& h2)
{
    // todo: handle chop
    return 0;
}

bool Hand::CompareStraightFlush(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::sort(hand1.begin(), hand1.end(), CompareFaceValue);
    std::sort(hand2.begin(), hand2.end(), CompareFaceValue);


    if(CompareFaceValue(hand1[4], hand2[4]))
    {
        return true;
    }
    return false;
}

bool Hand::CompareQuads(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::map<int, int> o1 = Hand::CountRecurring(hand1);
    std::map<int, int> o2 = Hand::CountRecurring(hand2);

    int h1Quads = -1;
    int h1Pair = -1;

    int h2Quads = -1;
    int h2Pair = -1;

    for(auto el: o1)
    {
        if(el.second == 4)
        {
            h1Quads = el.first;
        }
        else
        {
            h1Pair = el.first;
        }
    }

    for(auto el: o2)
    {
        if(el.second == 4)
        {
            h2Quads = el.first;
        }
        else
        {
            h2Pair = el.first;
        }
    }

    // compare quads
    if(h1Quads < h2Quads)
    {
        return true;
    }
    if(h1Quads > h2Quads)
    {
        return false;
    }

    if(h1Pair < h2Pair)
    {
        return true;
    }

    return false;
}

bool Hand::CompareFullHouse(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::map<int, int> o1 = Hand::CountRecurring(hand1);
    std::map<int, int> o2 = Hand::CountRecurring(hand2);

    //already know it's a full house
    int h1Trips = -1;
    int h1Pair = -1;

    int h2Trips = -1;
    int h2Pair = -1;
    for(auto el: o1)
    {

        if(el.second == 3)
        {
            h1Trips = el.first;
        }
        else
        {
            h1Pair = el.second;

        }
    }

    for(auto el: o2)
    {
        if(el.second == 3)
        {
            h2Trips = el.first;
        }
        else
        {
            h2Pair = el.second;
        }
    }
    

    if(h1Trips < h2Trips)
    {
        return true;
    }
    if(h1Trips > h2Trips )
    {
        return false;
    }

    if(h1Pair < h2Pair)
    {
        return true;
    }
    return false;
}
// true if h1 < h2
// false if h2 > h1
bool Hand::CompareFlush(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::sort(hand1.begin(), hand1.end(), CompareFaceValue);
    std::sort(hand2.begin(), hand2.end(), CompareFaceValue);

    for(int i = 4; i >= 0; i--)
    {
        if(static_cast<int>(hand1[i].GetValue()) < static_cast<int>(hand2[i].GetValue()))
        {
            return false;
        }
        if(static_cast<int>(hand1[i].GetValue()) > static_cast<int>(hand2[i].GetValue()))
        {
            return true;
        }
    }
    // the two are equal
    return false;
}

// true if h1 < h2
// false if h1 > h2
bool Hand::CompareStraight(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::sort(hand1.begin(), hand1.end(), CompareFaceValue);
    std::sort(hand2.begin(), hand2.end(), CompareFaceValue);
    
    // check if we have a wheel
    if(hand1[4].GetValue() == Card::FaceValue::ACE && hand1[0].GetValue() == Card::FaceValue::TWO)
    {
        //hand1 is a wheel
        int highCard = hand2[4].GetValue() == Card::FaceValue::ACE ? 14 : static_cast<int>(hand2[4].GetValue());
        if(highCard > 5)
        {
            //hand 2 is a higher straight
            return true;
        }
    }
    // check hand2
    if(hand2[4].GetValue() == Card::FaceValue::ACE && hand2[0].GetValue() == Card::FaceValue::TWO)
    {
        //hand2 is a wheel
        int highCard = hand1[4].GetValue() == Card::FaceValue::ACE ? 14 : static_cast<int>(hand1[4].GetValue());
        if(highCard > 5)
        {
            //hand 1 is a higher straight
            return false;
        }
    }
    return Hand::CompareFaceValue(hand1[4], hand2[4]);
}
bool Hand::CompareTrips(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::map<int, int> o1 = Hand::CountRecurring(hand1);
    std::map<int, int> o2 = Hand::CountRecurring(hand2);

    std::vector<int> kickers1, kickers2;
    int trips1 = -1;
    int trips2 = -1;

    for(auto el: o1)
    {
        if(el.second == 3)
        {
            trips1 = el.first;
        }
        else
        {
            kickers1.push_back(el.first);
        }
    }

    for(auto el: o2)
    {
        if(el.second == 3)
        {
            trips2 = el.first;
        }
        else
        {
            kickers2.push_back(el.first);
        }
    }
    
    if(trips1 < trips2)
    {
        return true;
    }
    if(trips1 > trips2)
    {
        return false;
    }
    
    // know trips1 == trips2 == const
    // need to look at other cards
    std::sort(kickers1.begin(), kickers1.end(), std::greater<int>());
    std::sort(kickers2.begin(), kickers2.end(), std::greater<int>());
    
    for(int i = 1; i >= 0; i--)
    {
        
        if(kickers1[i] < kickers2[i])
        {
            return true;
        }
        if(kickers1[i] > kickers2[i])
        {
            return false;
        }

    }
    // the two are equal, shouldn't get here
    return false;
}
bool Hand::CompareTwoPair(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::map<int, int> o1 = Hand::CountRecurring(hand1);
    std::map<int, int> o2 = Hand::CountRecurring(hand2);

    // keep track of pairs and kickers
    std::vector<int> hand1Pairs, hand2Pairs;

    int kicker1 = -1;
    int kicker2 = -1;

    auto extractPairsAndKicker = [](const std::map<int, int>& occurrences, std::vector<int>& pairs, int& kicker) {
        for (const auto& [value, count] : occurrences) {
            if (count == 2) {
                pairs.push_back(value);
            } else if (count == 1) {
                kicker = value;
            }
        }
        std::sort(pairs.begin(), pairs.end(), std::greater<int>()); // Sort pairs descending for comparison
    };

    extractPairsAndKicker(o1, hand1Pairs, kicker1);
    extractPairsAndKicker(o2, hand2Pairs, kicker2);
    
    if(hand1Pairs[0] < hand2Pairs[0])
    {
        return true;
    }
    if(hand1Pairs[0] > hand2Pairs[0])
    {
        return false;
    }

    if(hand1Pairs[1] < hand2Pairs[1])
    {
        return true;
    }
    if(hand1Pairs[1] > hand2Pairs[1])
    {
        return false;
    }
    return kicker1 < kicker2;
}

bool Hand::ComparePair(std::vector<Card>& hand1, std::vector<Card>& hand2)
{
    std::map<int, int> o1 = Hand::CountRecurring(hand1);
    std::map<int, int> o2 = Hand::CountRecurring(hand2);

    std::vector<int> kickers1, kickers2;
    int pair1 = -1;
    int pair2 = -1;

    for(auto el: o1)
    {
        if(el.second == 2)
        {
            pair1 = el.first;
        }
        else
        {
            kickers1.push_back(el.first);
        }
    }

    for(auto el: o2)
    {
        if(el.second == 2)
        {
            pair2 = el.first;
        }
        else
        {
            kickers2.push_back(el.first);
        }
    }
    if(pair1 < pair2)
    {
        return true;
    }
    if(pair1 > pair2)
    {
        return false;
    }
    // know pair1 == pair2 == const
    // need to look at other cards
    std::sort(kickers1.begin(), kickers1.end(), std::greater<int>());
    std::sort(kickers2.begin(), kickers2.end(), std::greater<int>());

    for(int i = 0; i < 4; i++)
    {
        if(kickers1[i] < kickers2[i])
        {
            return true;
        }
        if(kickers1[i] > kickers2[i])
        {
            return false;
        }
    }
    return false;

}
Hand::HandRanking Hand::EvaluateHand(std::vector<Card>& hand)
{
    if(Hand::IsRoyalFlush(hand))
    {
        return Hand::HandRanking::ROYALFLUSH;
    }
    if(Hand::IsStraightFlush(hand))
    {
        return Hand::HandRanking::STRAIGHFLUSH;
    }
    if(Hand::IsQuads(hand))
    {
        return Hand::HandRanking::QUADS;
    }
    if(Hand::IsFullHouse(hand))
    {
        return Hand::HandRanking::FULLHOUSE;
    }
    if(Hand::IsFlush(hand))
    {
        return Hand::HandRanking::FLUSH;
    }
    if(Hand::IsStraight(hand))
    {
        return Hand::HandRanking::STRAIGHT;
    }
    if(Hand::IsThreeOfAKind(hand))
    {
        return Hand::HandRanking::THREEOFAKIND;
    }
    if(Hand::IsTwoPair(hand))
    {
        return Hand::HandRanking::TWOPAIR;
    }
    if(Hand::IsPair(hand))
    {
        return Hand::HandRanking::PAIR;
    }
    return Hand::HandRanking::HIGHCARD;

}

std::pair<std::vector<Card>, Hand::HandRanking> Hand::BestHand(std::vector<Card>& cards)
{
    Hand h(cards);
    std::vector<std::vector<Card>> allHands = h.GeneratePokerHands();

    // keep track of the current highest hand and any duplicate classifications
    std::vector<std::vector<Card>> duplicateRankings;
    
    //keep track of the hand classification of the high hand, and number of times that classification occurs
    Hand::HandRanking max = Hand::HandRanking::HIGHCARD;
    int maxcount = 1;

    for(std::vector<Card> el: allHands)
    {
        Hand::HandRanking cur = Hand::EvaluateHand(el);
        if(static_cast<int>(cur) > static_cast<int>(max))
        {
            // new high hand
            // update max, maxcount
            // clear the duplicate rankings
            // add new max

            max = cur;
            maxcount = 1;

            duplicateRankings.clear();
            duplicateRankings.push_back(el);
        }
        if(static_cast<int>(cur) == static_cast<int>(max))
        {
            maxcount++;
            duplicateRankings.push_back(el);
        }
    }
    if(duplicateRankings.size() == 1)
    {
        return {duplicateRankings[0], max};
    }

    // have to compare multiple hands of the given hand type
    

    return {duplicateRankings[0], Hand::HandRanking::ROYALFLUSH};
}