class Card
{
public: 
    Card(int s, int val) : suit(s), value(val) {}

    Card() : suit(0), value (0) {}
private:
    int suit;
    int value;
};