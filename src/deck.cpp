#include "deck.h"
#include <iostream> 
#include <algorithm>
#include <random>
#include <exception>


Deck::Deck() {

    std::deque<Card> deck;

    for (int suit = static_cast<int>(Card::Suit::CLUBS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit)
    {
        for (int value = static_cast<int>(Card::FaceValue::ACE); value <= static_cast<int>(Card::FaceValue::KING); ++value) 
        {
            this->deck.push_back(Card(static_cast<Card::Suit>(suit), static_cast<Card::FaceValue>(value)));
        }
    }
}

Deck::Deck(const Deck &d) : deck(d.deck) {}


void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->deck.begin(),this->deck.end(),g);
}
Deck& Deck::operator=(const Deck& other)
{
    this->deck = other.deck;
    return *this;
}
std::vector<Card> Deck::Deal(size_t num_cards)
{
    if(num_cards > this->deck.size())
    {
        throw std::runtime_error("Attempted to deal more cards than remain in the deck.\n");
    }

    std::vector<Card> result;
    result.reserve(num_cards);

    for(int i = 0; i < num_cards; i++)
    {
        //populate result
        result.emplace_back(this->deck.front());

        this->deck.pop_front();
    }

    return result;
}

std::string Deck::ToString() const 
{
    std::string result;
    for(Card c: this->deck)
    {
        result += c.ToString();
    }
    return result;
}

int Deck::CardsRemaining()
{
    return this->deck.size();
}

void Deck::RemoveCards(const std::vector<Card>& cards)
{
    for(Card c: cards)
    {
        auto it = std::find(this->deck.begin(), this->deck.end(), c);
        

        if(it != this->deck.end())
        {
            this->deck.erase(it);
        }
    }
}
