#include "card.h"

// Initialize static arrays
const char* Card::faceSymbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
const char* Card::suitSymbols[4] = {"c", "d", "h", "s"}; // Corresponding to Clubs, Diamonds, Hearts, Spades

// Constructor implementations
Card::Card(Suit s, FaceValue val) : suit(s), value(val) {}

Card::Card() : suit(Suit::SPADES), value(FaceValue::ACE) {}

// Getter implementations
Card::Suit Card::GetSuit() const 
{
    return this->suit;
}

Card::FaceValue Card::GetValue() const 
{
    return this->value;
}

std::string Card::ToString() const 
{
    std::string res;
    res += faceSymbols[static_cast<int>(value) - 1]; 
    res += suitSymbols[static_cast<int>(suit) - 1];
    return res;
}
