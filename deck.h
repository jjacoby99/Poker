#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {
public:
    // Constructor
    Deck();

    // Method to print the deck
    void PrintDeck() const;

private:
    Card deck[52]; // Array of 52 Card instances
};

#endif // DECK_H
