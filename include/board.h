#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include <map>

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

    // takes the top 3 cards from the deck, adds them to the board
    void Flop(const std::vector<Card>& flop);

    // takes the top card from the deck, adds it to the board
    void Turn(const Card& turn);

    // takes the top card from the deck, adds it to the board
    void River(const Card& river);

    // adds the provided cards to the board, assuming there are less than 5 provided
    void AddCards(const std::vector<Card>& cards);

    // print the current state of the board
    void DisplayBoard();

    // returns the cards on the board currently in a vector
    std::vector<Card> GetBoard() const;

    // checks to see if a royal flush is possible on the current board
    // to used in optimizations elsewhere
    // to be refined. will give false positives currently
    bool PossibleRoyal() const;

    // checks to see if a straight flush is possible on the current board
    // to used in optimizations elsewhere
    // to be refined. will give false positives currently
    bool PossibleStraightFlush() const;

    // checks to see if a straight is possible on the current board
    // used in optimizations elsewhere
    bool PossibleStraight() const;

    // checks to see if a flush is possible on the current board
    // used in optimizations elsewhere
    bool PossibleFlush() const;

    // checks to see if the board is paired
    // has the side effect of sorting the board in ascending order
    // not sure if this is worth the performance benefits of not creating a copy
    bool BoardPaired() const;

    // helper function to map face values to the number of times they occur on the current board
    // on A A K K 2, the result would be {1 -> 2, 13 -> 2, 2 -> 2}
    std::map<int, int> CountRecurring() const;
private:

    std::vector<Card> board;
};

#endif 