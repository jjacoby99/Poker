#include <string>
 
class Card
{
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

    // constructor 
    Card(Suit s, FaceValue val) : suit(s), value(val) {}

    // default constructor: Ace of Spades
    Card() : suit(Suit::SPADES), value(FaceValue::ACE) {}

    Suit GetSuit()
    {
        return this->suit;
    }

    FaceValue GetValue()
    {
        return this->value;
    }

    std::string ToString()
    {
        std::string res;
        
        // determine face value
        res += this->faceSymbols[static_cast<int>(this->value)];

        // determine suit
        res += this->suitSymbols[static_cast<int>(this->suit)];

        return res;
    }


private:
    Suit suit;
    FaceValue value;
    
    // Array to map face values to symbols
    const char* faceSymbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};

    // Array to map suit values to symbols
    const char* suitSymbols[4] = {"s", "h", "d", "c"};
};