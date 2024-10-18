#ifndef SIM_H
#define SIM_H

#include "board.h"
#include "hand.h"
#include <thread>

class Sim 
{
public:

    // pre-flop h1 vs h2
    Sim(std::pair<Card, Card> h1, std::pair<Card, Card> h2);

    // post-flop h1 vs h2 with board b, can be flop, turn or river
    Sim(std::pair<Card, Card> h1, std::pair<Card, Card> h2, Board b, Deck d);

    double CalculateEquity(size_t num_sims);

    double CalculateEquity(size_t num_sims, size_t threads);

    double CalculateEquityNoPruning(size_t num_sims);

    void ThreadTask(size_t num_sims, double & result);

private:
    std::pair<Card, Card> h1;
    std::pair<Card, Card> h2;
    Board board;
    Deck deck;
    
};

#endif