#include "board.h"
#include <iostream>

Board::Board()
{
    
}

Board::Board(const std::vector<Card>& flop)
{
    this->Flop(flop);
}
// pre-specify flop & turn
Board::Board(const std::vector<Card>& flop, const Card& turn)
{
    this->Flop(flop);
    this->board.push_back(turn);
}

// pre-specify flop, turn, & river
Board::Board(const std::vector<Card>& flop, const Card& turn, const Card& river)
{
    if(flop.size() != 3)
    {
        throw std::runtime_error("The flop must contain 3 cards");
    }
    this->Flop(flop);
    this->board.emplace_back(turn);
    this->board.emplace_back(river);
}

void Board::Flop(const std::vector<Card>& flop)
{
    if(flop.size() != 3)
    {
        throw std::runtime_error("The flop must contain 3 cards");
    }
    this->board.reserve(3);

    for(Card c: flop)
    {
        this->board.push_back(c);
    }
}

void Board::Turn(const Card& turn)
{
    this->board.push_back(turn);
}

void Board::River(const Card& river)
{
    this->board.push_back(river);
}

// print the current state of the board
void Board::DisplayBoard()
{
    for(Card c: this->board)
    {
        std::cout << c.ToString() << " ";
    }
    std::cout << std::endl;
}

std::vector<Card> Board::GetBoard()
{
    return this->board;
}