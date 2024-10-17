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

    // copy constructor
    Board(const Board& other);

    void Flop(const std::vector<Card>& flop);

    void Turn(const Card& turn);

    void River(const Card& river);

    void AddCards(const std::vector<Card>& cards);

    // print the current state of the board
    void DisplayBoard();

    std::vector<Card> GetBoard() const;

    bool PossibleRoyal() const;

    bool PossibleStraightFlush() const;

    bool PossibleStraight() const;

    bool PossibleFlush() const;

    bool BoardPaired() const;

    
private:
    std::vector<Card> board;
};

#endif 