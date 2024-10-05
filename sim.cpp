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
        

        // printing
        /*std::cout << "Hand " << i << ". Board: ";
        for(Card c: simBoard.GetBoard())
        {
            std::cout << c.ToString() << " ";
        }
        std::cout << std::endl;

        std::cout << "\tP1: " << h1.first.ToString() << " " << h1.second.ToString() << std::endl;
        std::cout << "\tP2: " << h2.first.ToString() << " " << h1.second.ToString() << std::endl;

        std::cout << "\tH1: " << static_cast<int>(p1.second) << std::endl;
        for(Card c: p1.first)
        {
            std::cout << c.ToString() << " ";
        }
        std::cout << std::endl;
        std::cout << "\tH2: " << static_cast<int>(p2.second) << std::endl;
        for(Card c: p2.first)
        {
            std::cout << c.ToString() << " ";
        }
        std::cout << std::endl;
        */
        if(static_cast<int>(p1.second) > static_cast<int> (p2.second))
        {
            // h1 classification is greater than h2 classification: h1 winds
            //std::cout << "HAND 1 WINS" <<std::endl;
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
