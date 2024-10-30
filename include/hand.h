#ifndef HAND_H
#define HAND_H

#include "board.h"
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

    static std::string HandRankingToEnglish(HandRanking rank);

    Hand(std::vector<Card> cards);

    Hand(const Board& b, const std::pair<Card, Card>& holeCards);
    static void GetAllCombinations(const std::vector<Card>& cards, std::vector<Card>& hand, std::vector<std::vector<Card>>& allHands, int idx, int start);

    // determines the winning hand between p1 and p2
    // returns true if p1 < p2
    // false if p1 > p2
    static bool PlayerVsPlayer(const std::pair<Card, Card>& p1, const std::pair<Card, Card>& p2, const Board& b);

    
    // Generates all permutations of 5 card poker hands
    static std::vector<std::vector<Card>> GeneratePokerHands(const std::vector<Card>& cards);

    // classifies a 5 card poker hand into one of the HandRankings
    static HandRanking EvaluateHand(std::vector<Card>& hand);
    
    static HandRanking EvaluateHand2(std::vector<Card>& hand, const std::map<HandRanking, bool>& possibleHands);
    
    static std::map<HandRanking, bool> GetPossibleHands(const Board& board);

    // Determines best 5 card poker hand
    static std::pair<std::vector<Card>, Hand::HandRanking> BestHand(const std::vector<Card>& cards);

    // uses pruning based on board
    static std::pair<std::vector<Card>, Hand::HandRanking> BestHand(const Board& b, const std::pair<Card, Card>& holeCards);

    // returns true if h1 < h2
    // returns false if h1 > h2
    static bool CompareHands(std::vector<Card>& h1, std::vector<Card>& h2, HandRanking rank);

    static bool CompareHands(std::vector<Card>& h1, std::vector<Card>& h2);

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

    static bool CompareStraightFlush(std::vector<Card>& hand1, std::vector<Card>& hand2);

    static bool CompareQuads(std::vector<Card>& hand1, std::vector<Card>& hand2);
    
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

    static bool ComparePair(std::vector<Card>& hand1, std::vector<Card>& hand2);

    static bool CompareHighCard(std::vector<Card>& hand1, std::vector<Card>& hand2);

    static std::map<int, int> CountRecurring(std::vector<Card>& hand); 

private:

    // all cards available 
    std::vector<Card> cards;

    Board board;
    std::pair<Card, Card> holeCards;

    HandRanking ranking;





};

#endif