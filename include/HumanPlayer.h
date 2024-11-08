#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "card.h"
#include "board.h"
#include "hand.h"
#include "player.h"
#include <vector>
#include <iostream>


class HumanPlayer : public Player 
{
public:
    

    HumanPlayer(double buyin, const std::string& name);

    void TakeAction(double bet, double minBet, const std::string& street) override;


  
};


#endif 
