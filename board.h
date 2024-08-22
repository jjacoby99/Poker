#ifndef BOARD_H
#define BOARD_H

#include "deck.h"


class Board
{
public:
    // default constructor
    Board();

    // pre-specify flop
    Board(std::vector<Card> flop);

    // pre-specify flop & turn
    Board(std::vector<Card> flop, Card turn);

    // pre-specify flop, turn, & river
    Board(std::vector<Card> flop, Card turn, Card river);

    void Flop(std::vector<Card> flop);

    void Turn(Card turn);

    void River(Card river);

    // print the current state of the board
    void DisplayBoard();

    std::vector<Card> GetBoard();
    
private:
    std::vector<Card> board;
};

#endif 