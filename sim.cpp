#include "sim.h"
#include <iostream>
Sim::Sim(std::pair<Card, Card> h1, std::pair<Card, Card> h2)
{
    this->h1 = h1;
    this->h2 = h2;

    //std::vector<Card> holeCards = {h1.first, h1.second, h2.first, h2.second};
    this->deck.RemoveCards({h1.first, h1.second, h2.first, h2.second});
    this->deck.Shuffle();
}

Sim::Sim(std::pair<Card, Card> h1, std::pair<Card, Card> h2, Board b, Deck d)
{
    this->h1 = h1;
    this->h2 = h2;

    if(b.GetBoard().size() > 5 || b.GetBoard().size() < 3)
    {
        throw std::runtime_error("Invalid board size. Board must contain 3, 4, or 5 cards.\n");
    }
   
    // remove hole cards and deck d
    std::vector<Card> removeCards = {h1.first, h1.second, h2.first, h2.second};
    for(Card c: b.GetBoard())
    {
        removeCards.push_back(c);
    }
    d.RemoveCards(removeCards);

    this->deck = d;
    this->board = b;
}

double Sim::CalculateEquity(size_t numSims)
{
    Board startBoard(this->board);
    
    const int boardSize = startBoard.GetBoard().size();
    const int board = 5;
    double h1Wins = 0;

    Deck simDeck(this->deck);
    for(int i = 0; i < numSims; i++)
    {
        // deal out remaining cards, add to board
        Board simBoard(startBoard);

        // re-initialize the deck if needed
        if(simDeck.CardsRemaining() < board - boardSize)
        {
            simDeck = this->deck;
            simDeck.Shuffle();
        }
        

        simBoard.AddCards(simDeck.Deal(board - boardSize));
               
        
        auto p1 = Hand::BestHand(simBoard, h1);
        auto p2 = Hand::BestHand(simBoard, h2); 
        
        if(static_cast<int>(p1.second) > static_cast<int> (p2.second))
        {
            // h1 classification is greater than h2 classification: h1 winds
            h1Wins += 1.0;
        }
        else if(static_cast<int>(p1.second) == static_cast<int> (p2.second))
        {
            // h2 classification == h2 classification: compare
            bool resultsimDeck = Hand::CompareHands(p1.first, p2.first, p1.second); // this is equivalent to the question ( h1 < h2 )?
            if(!resultsimDeck)
            {
                h1Wins++;
            }
        } 
    }
    return h1Wins / static_cast<double>(numSims);

}

double Sim::CalculateEquityNoPruning(size_t numSims)
{
    Board startBoard(this->board);
    
    const int boardSize = startBoard.GetBoard().size();
    const int board = 5;
    double h1Wins = 0;

    Deck simDeck(this->deck);
    for(int i = 0; i < numSims; i++)
    {
        // deal out remaining cards, add to board
        Board simBoard(startBoard);

        // re-initialize the deck if needed
        if(simDeck.CardsRemaining() < board - boardSize)
        {
            simDeck = this->deck;
            simDeck.Shuffle();
        }
        

        simBoard.AddCards(simDeck.Deal(board - boardSize));
        
        std::vector<Card> board = simBoard.GetBoard();
        
        auto p1 = Hand::BestHand({board[0], board[1],board[2], board[3], board[4], h1.first, h1.second});
        auto p2 = Hand::BestHand({board[0], board[1],board[2], board[3], board[4], h2.first, h2.second}); 

        if(static_cast<int>(p1.second) > static_cast<int> (p2.second))
        {
            // h1 classification is greater than h2 classification: h1 winds
            h1Wins += 1.0;
        }
        else if(static_cast<int>(p1.second) == static_cast<int> (p2.second))
        {
            // h2 classification == h2 classification: compare
            bool resultsimDeck = Hand::CompareHands(p1.first, p2.first, p1.second); // this is equivalent to the question ( h1 < h2 )?
            if(!resultsimDeck)
            {
                //std::cout << "HAND 1 WINS" <<std::endl;
                h1Wins++;
            }
            /*else{
                //std::cout << "HAND 2 WINS" << std::endl;
            }*/
        }

        

        
    }
    return h1Wins / static_cast<double>(numSims);

}
