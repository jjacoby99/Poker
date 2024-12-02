#ifndef SIM_H
#define SIM_H

#include "board.h"
#include "hand.h"
#include "range.h"
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

    // calculates the equity of hand vs the range of hands in the opponent's range
    // to be implemented
    static double CalculateEquityVsRange(size_t num_sims, const std::pair<Card, Card>& hand, const Range& range);

private:
    std::pair<Card, Card> h1;
    std::pair<Card, Card> h2;
    Board board;
    Deck deck;
    
};

#endif