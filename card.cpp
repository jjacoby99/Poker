#include <string>
 
class Card
{
public: 
    Card(int s, int val) : suit(s), value(val) {}

    Card() : suit(0), value (0) {}

    int GetSuit()
    {
        return this->suit;
    }

    int GetValue()
    {
        return this->value;
    }

    std::string ToString()
    {
        std::string res;
        
        // determine face value
        res += this->faceSymbols[this->value];

        // determine suit
        res += this->suitSymbols[this->suit];
    }

private:
    int suit;
    int value;
    
    // Array to map face values to symbols
    const char* faceSymbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};

    // Array to map suit values to symbols
    const char* suitSymbols[4] = {"s", "h", "d", "c"};
};