#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    // Enum for Suit
    enum class Suit {
        CLUBS = 1,
        DIAMONDS = 2,
        HEARTS = 3,
        SPADES = 4
    };

    // Enum for FaceValue
    enum class FaceValue {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13
    };

    // Constructors
    Card(Suit s, FaceValue val);
    Card(); // Default constructor: Ace of Spades

    // Getter functions
    Suit GetSuit() const;
    FaceValue GetValue() const;

    // Convert card to string representation
    std::string ToString() const;

private:
    Suit suit;
    FaceValue value;
    
    // Array to map face values to symbols
    const char* faceSymbols[14] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
    
    // Array to map suit values to symbols
    const char* suitSymbols[5] = {"", "c", "d", "h", "s"}; // Note: Added an empty string for index 0
};

#endif // CARD_H
