#include "board.h"
#include <iostream>
#include "hand.h"

Board::Board()
{
    
}
Board::Board(const Board& other)
{
    for(Card c: other.board)
    {
        this->board.push_back(c);
    }
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
    this->board.push_back(turn);
    this->board.push_back(river);
}

void Board::Flop(const std::vector<Card>& flop)
{
    if(flop.size() != 3)
    {
        throw std::runtime_error("The flop must contain 3 cards");
    }

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

std::vector<Card> Board::GetBoard() const 
{
    return this->board;
}

void Board::AddCards(const std::vector<Card>& cards)
{
    if(cards.size() > 5 - this->board.size())
    {
        throw std::runtime_error("Too many cards provided");
    }
    
    for(Card c: cards)
    {
        this->board.push_back(c);
    }
}

bool Board::PossibleStraight() const
{
    return true;
}

bool Board::PossibleFlush() const
{
    int suitCount[4] = {0, 0, 0, 0};

    for(Card c: this->board)
    {
        suitCount[static_cast<int>(c.GetValue()) - 1]++;
    }
    return suitCount[0] > 2 || suitCount[1] > 2 || suitCount[2] > 2 || suitCount[3] > 2;
}

bool Board::BoardPaired() const 
{
    std::vector<Card> b = this->GetBoard();
    std::map<int, int> occur = Hand::CountRecurring(b);

    for(auto el: occur)
    {
        if(el.second > 1)
        {
            return true;
        }
    }
    return false;
}