#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/game.h"

Game::Game(std::vector<Player> startPlayers, double sb, double bb)
{
    this->smallBlind = sb;
    this->bigBlind = bb;

    this->maxBuyIn = 100.0 * bb;


    for(Player p: startPlayers)
    {

        this->playerList.push_back({p, true});
    }

    this->button = this->playerList.size();
    this->turn = 2; // 0 - sb, 1 - bb, 2, utg1

    this->deck.Shuffle();
    this->pot = 0.0;
}

void Game::Play()
{
    
}




