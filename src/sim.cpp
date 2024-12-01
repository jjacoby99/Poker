#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/sim.h"
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

    if(b.GetBoard().size() > 5 || b.GetBoard().size() < 1)
    {
        throw std::runtime_error("Invalid board size. Board must contain 0, 3, 4, or 5 cards.\n");
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

    if(boardSize == 5)
    {
        // only one sim required:
        numSims = 1;
    }
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
                h1Wins++;
            }
        } 
    }
    return h1Wins / static_cast<double>(numSims);

}
void Sim::ThreadTask(size_t num_sims, double & result)
{
    result = this->CalculateEquity(num_sims);
}

double Sim::CalculateEquity(size_t num_sims, size_t num_threads)
{
    unsigned int maxThreads = std::thread::hardware_concurrency();
    if(num_threads > maxThreads)
    {
        throw std::runtime_error("Too many threads provided.\n");
    }

    // determine breakdown of threads
    size_t simsPerThread = num_sims / num_threads;
    size_t remaining = num_sims - simsPerThread * num_threads;

    std::vector<std::thread> threads;

    std::vector<double> results(num_threads, 0.0);

    // start up threads
    threads.push_back(std::thread(&Sim::ThreadTask, this, simsPerThread + remaining, std::ref(results[0])));
    for(unsigned int i = 1; i < num_threads; i++)
    {
        threads.push_back(std::thread(&Sim::ThreadTask, this, simsPerThread, std::ref(results[i])));
    }

    for(auto& t: threads)
    {
        t.join();
    }

    double equity = results[0] * (simsPerThread + remaining);

    for(int i = 1; i < num_threads; i++)
    {
        equity += results[i] * static_cast<double>(simsPerThread);
    }
    return equity / static_cast<double>(num_sims);
}


double Sim::CalculateEquityVsRange(size_t num_sims, const std::pair<Card, Card>& hand, const Range& range)
{
    return 0.0;
}