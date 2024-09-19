#include "player.h"
Player::Player() : stack(0.0) {}

Player::Player(double stack, std::string name) : stack(stack), name(name) {}

void Player::Bet(double bet)
{
    if(bet <= this->stack)
    {
        this->stack -= bet;
        return;
    }
    // player is all in
    this->stack = 0;
}
std::vector<Card> Player::GetHoleCards()
{
    if(this->holeCards.size() == 2)
    {
        return this->holeCards;
    }
    throw std::runtime_error("Player already folded\n");
}
void Player::Check()
{

}
void Player::DetermineBestHand(std::vector<Card> board)
{
    if(this->holeCards.size() == 0)
    {
        this->bestHand = board;
    }

    std::vector<Card> cards = board;
    cards.push_back(this->holeCards[0]);
    cards.push_back(this->holeCards[1]);

    auto result = Hand::BestHand(cards);
    this->bestHand = result.first;
    this->ranking = result.second;
}
std::vector<Card> Player::GetBestHand()
{
    return this->bestHand;
}
Hand::HandRanking Player::GetHandRanking()
{
    return this->ranking;
}
void Player::SetHoleCards(const std::vector<Card>& holeCards)
{
    this->holeCards = holeCards;
}
double Player::GetStack()
{
    return this->stack;
}
void Player::Fold()
{
    this->holeCards.clear();
    this->bestHand.clear();
}

double Player::AddOn(double buyin)
{
    this->stack += buyin;
    return this->stack;
}

std::string Player::GetName()
{
    return this->name;
}