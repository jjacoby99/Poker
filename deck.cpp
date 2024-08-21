#include "deck.h"
#include <iostream> 
#include <algorithm>
#include <random>


Deck::Deck() {
    deck.reserve(52); // Reserve space for 52 cards

    for (int suit = static_cast<int>(Card::Suit::CLUBS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit) {
        for (int value = static_cast<int>(Card::FaceValue::ACE); value <= static_cast<int>(Card::FaceValue::KING); ++value) {
            deck.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::FaceValue>(value));
        }
    }
}


void Deck::Shuffle()
{
    std::cout << "Before shuffle first element: " << this->deck[0].ToString() << std::endl;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->deck.begin(),this->deck.end(),g);
    std::cout << "After shuffle first element: " << this->deck[0].ToString() << std::endl;

}
// Optional method to print the deck (for testing)
std::string Deck::ToString() const 
{
    std::string result;
    for (int i = 0; i < 52; ++i) {
        result += deck[i].ToString();
    }
    return result;
}
