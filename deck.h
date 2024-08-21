#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck {
public:
    // Constructor
    Deck();

    // Randomizes the order of the deck
    void Shuffle();

    std::string ToString() const;

private:
    std::vector<Card> deck; // Array of 52 Card instances
};

#endif // DECK_H
