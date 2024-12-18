#ifndef CARD_H
#define CARD_H

#include <string>
#include <sstream>
class Card {
public:
    enum class Suit 
    {
        CLUBS = 1,
        DIAMONDS = 2,
        HEARTS = 3,
        SPADES = 4
    };

    enum class FaceValue 
    {
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

    Card& operator=(const Card& other);

    bool operator==(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);

    // returns true if c1.FaceValue < c2.FaceValue
    // returns false if c1.FaceValue == c2.FaceValue
    static bool CompareFaceValue(const Card& card1, const Card& card2);

    // Getter methods
    Suit GetSuit() const;
    FaceValue GetValue() const;

    // Convert to string method
    std::string ToString() const;

private:
    Suit suit;
    FaceValue value;

    // Static arrays to map face values and suits to symbols
    static const char* faceSymbols[13];
    static const char* suitSymbols[4];
};

#endif // CARD_H
