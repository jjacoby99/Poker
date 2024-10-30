#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/player.h"

Player::Player() : stack(0.0), currentBet(0.0), action(Player::Action::UNDECIDED) {}

Player::Player(double stack, std::string name) : stack(stack), name(name), action(Player::Action::UNDECIDED) {}


double Player::Bet(double bet)
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

double Player::PostBlind(double value)
{
    this->action = Player::Action::UNDECIDED;
    if(value <= this->stack)
    {
        // a bet is an absolute number. If there was a previous bet on the same street, a new bet deletes the 
        // current one and is removed from the stack. Therefore, the previous bet should be added back to the stack.
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
double Player::Call(double bet)
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
std::pair<Card, Card> Player::GetHoleCards() const 
{
    return this->holeCards;
}
void Player::Check()
{
    this->action = Player::Action::CHECK;
}

Player::Action Player::GetAction() const
{
    return this->action;
}
void Player::SetAction(Player::Action newAction)
{
    this->action = newAction;
}
void Player::DetermineBestHand(std::vector<Card> board)
{
    std::vector<Card> cards = board;
    cards.push_back(this->holeCards.first);
    cards.push_back(this->holeCards.second);

    auto result = Hand::BestHand(cards);
    this->bestHand = result.first;
    this->ranking = result.second;
}
void Player::Win(double pot)
{
    this->stack += pot;
}
std::vector<Card> Player::GetBestHand()
{
    return this->bestHand;
}
Hand::HandRanking Player::GetHandRanking()
{
    return this->ranking;
}
void Player::SetHoleCards(const std::pair<Card, Card>& holeCards)
{
    this->holeCards = holeCards;
}
double Player::GetStack()
{
    return this->stack;
}
void Player::Fold()
{
    this->action = Player::Action::FOLD;
    this->bestHand.clear();
}

double Player::AddOn(double buyin)
{
    this->stack += buyin;
    return this->stack;
}

std::string Player::GetName() const
{
    return this->name;
}