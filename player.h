#ifndef PLAYER_H
#define BOARD_H

#include "card.h"
#include <vector>

class Player 
{
public:

    Player();
    Player(double buyin, std::string name);

    void Bet(double bet);

    void Check();

    void Fold();

    // returns stack after adding on
    double AddOn(double buyin);

    std::string GetName();

private:
    // money
    double stack;
    std::vector<Card> holeCards;

    std::string name;
};


#endif 
