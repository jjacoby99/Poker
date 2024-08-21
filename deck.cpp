#include "deck.h"
#include <iostream> 

Deck::Deck() {
    int index = 0;
    // Loop through each suit
    for (int suit = static_cast<int>(Card::Suit::CLUBS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit) {
        // Loop through each face value
        for (int value = static_cast<int>(Card::FaceValue::ACE); value <= static_cast<int>(Card::FaceValue::KING); ++value) {
            deck[index] = Card(static_cast<Card::Suit>(suit), static_cast<Card::FaceValue>(value));
            ++index;
        }
    }
}

// Optional method to print the deck (for testing)
void Deck::PrintDeck() const {
    for (int i = 0; i < 52; ++i) {
        std::cout << deck[i].ToString() << std::endl;
    }
}
