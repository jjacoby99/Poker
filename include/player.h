#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "board.h"
#include "hand.h"
#include <vector>

class Player 
{
public:

    Player();
    Player(double buyin, std::string name);

    double Bet(double bet);

    void Check();

    void Fold();

    void SetHoleCards(const std::vector<Card>& holeCards);
    
    std::vector<Card> GetHoleCards();

    // returns stack after adding on
    double AddOn(double buyin);

    double GetStack();

    void DetermineBestHand(std::vector<Card> board);

    std::vector<Card> GetBestHand();

    Hand::HandRanking GetHandRanking();

    std::string GetName();
    

private:
    double stack;
    std::vector<Card> holeCards;

    std::vector<Card> bestHand;
    Hand::HandRanking ranking;

    double currentBet;
    std::string name;

    // attribute for storing player's choice:
    // 1: bet/call
    // 0: check
    // -1: fold
    int action;
};


#endif 
