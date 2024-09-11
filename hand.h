#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>
class Hand 
{
public:
    enum class HandRanking
    {
        ROYALFLUSH = 1,
        STRAIGHFLUSH = 2,
        QUADS = 3,
        FULLHOUSE = 4,
        FLUSH = 5,
        STRAIGHT = 6,
        THREEOFAKIND = 7,
        TWOPAIR = 8,
        PAIR = 9,
        HIGHCARD = 10
    };

    Hand(std::vector<Card> cards);

    void GetAllCombinations(std::vector<Card>& cards, std::vector<Card>& hand, std::vector<std::vector<Card>>& allHands, int idx, int start);

    // Generates all permutations of 5 card poker hands
    std::vector<std::vector<Card>> GeneratePokerHands();
    
    // Determines best 5 card poker hand
    std::vector<Card> BestHand();

    static bool IsRoyalFlush(std::vector<Card>& hand);


    static bool IsFlush(std::vector<Card>& hand);

    static bool IsStraight(std::vector<Card>& hand);
    // returns true if c1.FaceValue < c2.FaceValue
    // returns false if c1.FaceValue == c2.FaceValue
    static bool CompareFaceValue(const Card& card1, const Card& card2);
private:
    // all cards available 
    std::vector<Card> cards;

    // cards to make best 5 card poker hand
    std::vector<Card> hand;

    HandRanking ranking;


};

#endif