#ifndef RANGE_H
#define RANGE_H
#include "Card.h"
#include <map>
class Range 
{
public: 

    // initializes a range object from a vector of pair of hole cards
    // frequency of each hand is assumed to be 1.0 (100%)
    Range(const std::vector<std::pair<Card, Card>>& range);

    // initializes a range based on a std::vector of card, but accounts for frequencies of each hand
    Range(const std::vector<std::map<std::pair<Card,Card>, double>>& rangeFrequencies);

    // initializes a range based on the worst offsuit hand, the worst suited hand, and the worst pair in the range.
    // all hands better than the provided bottom will be included in the range
    // frequency of all hands in range is assumed to be 1.0 (100%)
    Range(const std::pair<Card, Card>& bottomOffsuit, const std::pair<Card, Card>& bottomSuited, const std::pair<Card, Card>& bottomPair);

    // returns a vector of map that maps each holeCards to the number of combinations in range of that hand, given the dead cards
    // dead cards can include the caller's holeCards, as well as the community cards
    std::vector<std::map<std::pair<Card,Card>, int>> GetCombos(const std::vector<Card>& deadCards);

private:
    
    // table representing the range of a player.
    // AA   AKs AQs AJs ... A4s A3s A2s
    // AKo  KK  KQs KJs ... K4s K3s K2s
    // AQo  KQo QQ  QJs ... Q4s Q3s Q2s
    // AJo  KJo QJo JJ  ... J4s J3s J2s
    // ...
    // A2o  K2o Q2o J2o ... 42o 32o 22
    // rangeTable[i][j] is the frequency that the hand is in the range  
    double rangeTable[13][13] = {0};
};

#endif