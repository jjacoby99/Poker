#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "board.h"
#include "hand.h"
#include <vector>



class Player 
{
public:
    // attribute for storing player's choice:
    enum class Action
    {
        BET = 4,
        CALL = 3,
        CHECK = 2,
        FOLD = 1,
        UNDECIDED = 0 
    };

    Player();
    Player(double buyin, std::string name);

    double Bet(double bet);

    double Call(double bet);

    void Check();

    void Fold();

    void SetHoleCards(const std::pair<Card, Card>& holeCards);
    
    std::pair<Card, Card> GetHoleCards() const;

    // returns stack after adding on
    double AddOn(double buyin);

    double GetStack();

    double PostBlind(double value);

    void DetermineBestHand(std::vector<Card> board);

    std::vector<Card> GetBestHand();

    Hand::HandRanking GetHandRanking();

    std::string GetName() const;
    
    Player::Action GetAction() const;
    void SetAction(Player::Action newAction);

    double currentBet;
    void Win(double pot);

private:
    double stack;
    std::pair<Card, Card> holeCards;

    std::vector<Card> bestHand;
    Hand::HandRanking ranking;

    std::string name;

    Action action;

    
    
};


#endif 
