#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>
#include <map>

class Hand 
{
public:
    enum class HandRanking
    {
        ROYALFLUSH = 10,
        STRAIGHFLUSH = 9,
        QUADS = 8,
        FULLHOUSE = 7,
        FLUSH = 6,
        STRAIGHT = 5,
        THREEOFAKIND = 4,
        TWOPAIR = 3,
        PAIR = 2,
        HIGHCARD = 1
    };

    Hand(std::vector<Card> cards);

    void GetAllCombinations(std::vector<Card>& cards, std::vector<Card>& hand, std::vector<std::vector<Card>>& allHands, int idx, int start);

    // Generates all permutations of 5 card poker hands
    std::vector<std::vector<Card>> GeneratePokerHands();

    // classifies a 5 card poker hand into one of the HandRankings
    static HandRanking EvaluateHand(std::vector<Card>& hand);
    
    // Determines best 5 card poker hand
    static std::pair<std::vector<Card>, Hand::HandRanking> BestHand(std::vector<Card>& cards);

    // returns 1 if h1 > h2
    // returns 0 if h1 == h2
    // returns -1 if h1 < h2
    static int CompareHands(std::vector<Card>& h1, std::vector<Card>& h2);

    static bool IsRoyalFlush(std::vector<Card>& hand);

    static bool IsStraightFlush(std::vector<Card>& hand);
    
    static bool IsQuads(std::vector<Card>& hand);

    static bool IsFullHouse(std::vector<Card>& hand);

    static bool IsFlush(std::vector<Card>& hand);

    static bool IsStraight(std::vector<Card>& hand);

    static bool IsThreeOfAKind(std::vector<Card>& hand);

    static bool IsTwoPair(std::vector<Card>& hand);

    static bool IsPair(std::vector<Card>& hand);

    // returns true if c1.FaceValue < c2.FaceValue
    // returns false if c1.FaceValue == c2.FaceValue
    static bool CompareFaceValue(const Card& card1, const Card& card2);

    // returns true if h1 < h2
    // returns false if h1 > h2
    static bool CompareFullHouse(std::vector<Card>& hand1, std::vector<Card>& hand2);

    // returns true if h1 < h2
    // returns false if h1 > h2
    static bool CompareFlush(std::vector<Card>& hand1,std::vector<Card>& hand2);
    
    // returns true if h1 < h2
    // returns false if h1 > h2
    static bool CompareStraight(std::vector<Card>& hand1, std::vector<Card>& hand2);

    static bool CompareTrips(std::vector<Card>& hand1, std::vector<Card>& hand2);
    
    static bool CompareTwoPair(std::vector<Card>& hand1, std::vector<Card>& hand2);


    static std::map<int, int> CountRecurring(std::vector<Card>& hand); 

private:

    // all cards available 
    std::vector<Card> cards;

    // cards to make best 5 card poker hand
    std::vector<Card> hand;

    HandRanking ranking;


};

#endif