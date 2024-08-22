#include "board.h"
#include <iostream>

Board::Board()
{
    
}

Board::Board(std::vector<Card> flop)
{
    this->board.reserve(3);
    this->Flop(flop);
}
// pre-specify flop & turn
Board::Board(std::vector<Card> flop, Card turn)
{
    this->board.reserve(4);
    this->Flop(flop);
    this->board.emplace_back(turn);
}

// pre-specify flop, turn, & river
Board::Board(std::vector<Card> flop, Card turn, Card river)
{
    this->board.reserve(5);
    if(flop.size() != 3)
    {
        throw std::runtime_error("The flop must contain 3 cards");
    }
    for(Card c: flop)
    {
        this->board.emplace_back(c);
    }
    this->board.emplace_back(turn);
    this->board.emplace_back(river);
}

void Board::Flop(std::vector<Card> flop)
{
    if(flop.size() != 3)
    {
        throw std::runtime_error("The flop must contain 3 cards");
    }
    for(Card c: flop)
    {
        this->board.emplace_back(c);
    }
}

void Board::Turn(Card turn)
{
    this->board.emplace_back(turn);
}

void Board::River(Card river)
{
    this->board.emplace_back(river);
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