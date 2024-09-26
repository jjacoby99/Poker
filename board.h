#ifndef BOARD_H
#define BOARD_H

#include "deck.h"


class Board
{
public:
    // default constructor
    Board();

    // pre-specify flop
    Board(const std::vector<Card>& flop);

    // pre-specify flop & turn
    Board(const std::vector<Card>& flop, const Card& turn);

    // pre-specify flop, turn, & river
    Board(const std::vector<Card>& flop, const Card& turn, const Card& river);

    void Flop(const std::vector<Card>& flop);

    void Turn(const Card& turn);

    void River(const Card& river);

    // print the current state of the board
    void DisplayBoard();

    std::vector<Card> GetBoard();
    
private:
    std::vector<Card> board;
};

#endif 