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

void Player::Check()
{

}

void Player::Fold()
{

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