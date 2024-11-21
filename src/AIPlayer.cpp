#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/Include/AIPlayer.h"

AIPlayer::AIPlayer(double buyin, const std::string& name) : Player(buyin, name) {}

void AIPlayer::TakeAction(double bet, double minBet, const std::string& street)
{
    double betsize = 0;
    if(street == "Pre-flop")
    {
        betsize = 3 * minBet;
    }
    return;
}

void AIPlayer::TakeAction(const GameState& state)
{
    double betsize = 0;
    if(state.street == "Pre-flop")
    {
        betsize = 3 * state.minBet;
    }

    

}