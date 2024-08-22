#include "deck.h"
#include <iostream> 
#include <algorithm>
#include <random>
#include <exception>

Deck::Deck() {
    deck.reserve(52); // Reserve space for 52 cards

    for (int suit = static_cast<int>(Card::Suit::CLUBS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit) {
        for (int value = static_cast<int>(Card::FaceValue::ACE); value <= static_cast<int>(Card::FaceValue::KING); ++value) {
            deck.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::FaceValue>(value));
        }
    }
}

Deck::Deck(const Deck &d)
{
    size_t size = d.deck.size();

    this->deck.reserve(size);

    for(Card c: d.deck)
    {
        deck.emplace_back(c);
    }

}

void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->deck.begin(),this->deck.end(),g);
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
        result.emplace_back(this->deck[0]);

        //remove card from deck
        this->deck.erase(this->deck.begin());
    }

    return result;
}

std::string Deck::ToString() const 
{
    std::string result;
    for (int i = 0; i < 52; ++i) {
        result += deck[i].ToString();
    }
    return result;
}
