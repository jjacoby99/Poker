#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "card.h"
#include "board.h"
#include "hand.h"
#include "player.h"

class AIPlayer : public Player
{
public:
    

    AIPlayer(double buyin, const std::string& name);

    void TakeAction(double bet, double minBet, const std::string& street) override;

};

#endif