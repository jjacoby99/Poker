#ifndef RANGE_H
#define RANGE_H
#include "card.h"
#include <vector>
#include <map>
#include <iostream>
#include <tuple>

class Range 
{
public: 

    Range();
    // initializes a range object from a vector of pair of hole cards
    // frequency of each hand is assumed to be 1.0 (100%)
    Range(const std::vector<std::pair<Card, Card>>& range, const std::vector<Card>& deadCards = {});

    Range(const Range& other);

    // initializes a range based on a std::vector of card, but accounts for frequencies of each hand
    Range(const std::vector<std::map<std::pair<Card,Card>, double>>& rangeFrequencies);

    // initializes a range based on the worst offsuit hand, the worst suited hand, and the worst pair in the range.
    // all hands better than the provided bottom will be included in the range
    // frequency of all hands in range is assumed to be 1.0 (100%)
    Range(const std::pair<Card, Card>& bottomOffsuit, const std::pair<Card, Card>& bottomSuited, const std::pair<Card, Card>& bottomPair);

    // returns a vector of map that maps each holeCards to the number of combinations in range of that hand, given the dead cards
    // dead cards can include the caller's holeCards, as well as the community cards
    std::vector<std::map<std::pair<Card,Card>, int>> GetCombos(const std::vector<Card>& deadCards);

    // gets the number of combinations of a given hand, based on the dead cards provided.
    // note that this function differentiates between suited hands and off-suit hands. 
    // For example, if a suited hand is provided, the number of suited combinations of that same hand will be determined.
    int GetHandCombos(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards = {});

    // The purpose of this method is to update the range table by determining which combinations of hands are now impossible
    // due to the new deadCards
    // importantly, this method assumes that cards already in deadCards have been accounted for
    void UpdateRange(const std::vector<Card>& newDead);

    void PrintRangeTable();

    void PrintRangeHeaders();

    std::vector<std::vector<std::vector<double>>> GetRangeTable() const;
    
    // gets the combinations of the hand represented by RangeTable[i][j] given dead cards
    // GetCombos(i, j) returns {{As,Ah}, {As,Ac}, {As,Ad}, {Ah,Ac}, {Ah,Ad}, {Ac,Ad}}
    std::vector<std::pair<Card, Card>> GetCombos(const size_t i, const size_t j, const std::vector<Card>& deadCards);


private:
    
    // table representing the range of a player.
    // AA   AKs AQs AJs ... A4s A3s A2s
    // AKo  KK  KQs KJs ... K4s K3s K2s
    // AQo  KQo QQ  QJs ... Q4s Q3s Q2s
    // AJo  KJo QJo JJ  ... J4s J3s J2s
    // ...
    // A2o  K2o Q2o J2o ... 42o 32o 22

    // rangeTable[i][j] is a vector of the frequency that each combo of the hand is in range  
    std::vector<std::vector<std::vector<double>>> rangeTable = std::vector<std::vector<std::vector<double>>>(13, std::vector<std::vector<double>>(13, std::vector<double>(4, 0.0)));

    const std::vector<double>& operator[](size_t i) const;

    bool IsOffSuitHand(const std::pair<Card,Card>& hand);

    bool IsSuitedHand(const std::pair<Card, Card>& hand);

    bool IsPairHand(const std::pair<Card, Card>& hand);

    std::vector<Card> deadCards{};
    
};

#endif