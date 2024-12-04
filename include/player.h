#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "board.h"
#include "hand.h"
#include <vector>
#include <string>

class Player {
public:
    enum class Action {
        BET = 4,
        CALL = 3,
        CHECK = 2,
        FOLD = 1,
        UNDECIDED = 0 
    };

    struct GameState
    {
        std::string street;
        double pot;
        double toCall;
        double minBet;
    };

    enum class Position {
        IP = 1,
        OOP = 0
    };

    Player() : stack(0), name(""), action(Action::UNDECIDED) {}
    Player(double buyin, const std::string& name) : stack(buyin), name(name), action(Action::UNDECIDED) {}

    virtual ~Player() = default;

    
    
    virtual void TakeAction(double bet, double minBet, const std::string& street) = 0;
    
    void DetermineBestHand(std::vector<Card> board)
    {
        std::vector<Card> cards = board;
        cards.push_back(this->holeCards.first);
        cards.push_back(this->holeCards.second);

        auto result = Hand::BestHand(cards);
        this->bestHand = result.first;
        this->ranking = result.second;
    }

    // Shared methods
    void Check() {this->action = Action::CHECK; };
    void Fold() {this->action = Action::FOLD; this->bestHand.clear();};
    double PostBlind(double value) 
    {
        this->action = Player::Action::UNDECIDED;
        if(value <= this->stack)
        {
            this->stack -= value;
            this->currentBet = value;
            return value;
        }
        // player is all in
        this->currentBet = this->stack;
        double copy = this->stack;
        this->stack = 0;
        return copy;
    }
    void SetHoleCards(const std::pair<Card, Card>& holeCards) { this->holeCards = holeCards; }
    std::pair<Card, Card> GetHoleCards() const { return this->holeCards; }
    std::vector<Card> GetBestHand() const {return this->bestHand; }
    Hand::HandRanking GetHandRanking() const {return this->ranking; }

    double Bet(double bet)
    {
        this->action = Player::Action::BET;
        if(bet <= this->stack)
        {
            // a bet is an absolute number. If there was a previous bet on the same street, a new bet deletes the 
            // current one and is removed from the stack. Therefore, the previous bet should be added back to the stack.
            this->stack -= bet;
            this->stack += this->currentBet;

            this->currentBet = bet;
            return bet;
        }

        // player is all in
        this->currentBet = this->stack;
        double copy = this->stack;
        this->stack = 0;
        return copy;
    }
    double Call(double bet)
    {
        this->action = Player::Action::CALL;
        if(bet <= this->stack)
        {
            this->stack -= bet;
            this->currentBet += bet;
            return bet;
        }
        // player is all in
        this->currentBet = this->stack;
        double copy = this->stack;
        this->stack = 0;
        return copy;
    }

    double AddOn(double buyin) { stack += buyin; return stack; }
    double GetStack() const { return stack; }
    std::string GetName() const { return name; }
    
    Action GetAction() const { return action; }
    void SetAction(Action newAction) { action = newAction; }
    void SetPosition(Position pos) {this->position = pos;}
    void Win(double pot) {this->stack += pot; }

    double currentBet;

protected:
    double stack;
    std::pair<Card, Card> holeCards;

    std::vector<Card> bestHand;
    Hand::HandRanking ranking;

    std::string name;

    Action action;

    Position position;
};

#endif
