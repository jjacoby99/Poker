#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck {
public:
    // Constructor
    Deck();

    // Copy constructor
    Deck(const Deck &d);

    // Randomizes the order of the deck
    void Shuffle();

    std::string ToString() const;

    // returns the first num_cards cards from the top of the deck
    // has the side effect of removing those cards from the deck
    std::vector<Card> Deal(size_t num_cards);
    
private:
    std::vector<Card> deck; // Array of 52 Card instances
};

#endif // DECK_H
