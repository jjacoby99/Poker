#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"


class Game 
{
public:
    int players = 6;

    // sets the sb, bb, and maxBuyIn
    // sets players, button, and turn
    Game(std::vector<Player> players, double sb, double bb);

    //void AddPlayer(Player newPlayer);

    // void RemovePlayer(int idx);

    void Play();


private:

    double maxBuyIn;

    Deck deck;
    Board board;

    double smallBlind = 1.0;
    double bigBlind = 3.0;

    double pot;

    // keeps track of players in the game, true if in current hand, false if not. 
    // Hand over if only 1 players.second == true;
    std::vector<std::pair<Player, bool>> playerList;
    int button; // index of button in players

    int turn; // index of player who's turn it is currently

    

};

#endif