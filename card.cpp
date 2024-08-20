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

private:
    int suit;
    int value;
};