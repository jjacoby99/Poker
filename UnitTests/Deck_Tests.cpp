#include <gtest/gtest.h>
#include "deck.h"

// helper function that checks each character of the two strings are equal
void StringsEqual(std::string first, std::string second)
{
    EXPECT_EQ(first.size(), second.size());
    for(int i = 0; i < first.size(); i++)
    {
        EXPECT_EQ(first[i], second[i]);
    }
}
void PrintVec(std::vector<Card> v)
{
    for(Card c: v)
    {
        std::cout << c.ToString() << " ";
    }
    std::cout << std::endl;
}
void VectorsEqual(std::vector<Card> first, std::vector<Card> second)
{

    EXPECT_EQ(first.size(), second.size());
    std::cout << "first:\n";
    PrintVec(first);
    std::cout << "second:\n";
    PrintVec(second);
    for(int i = 0; i < first.size(); i++)
    {

        EXPECT_EQ(static_cast<int>(first[i].GetSuit()), static_cast<int>(second[i].GetSuit()));
        EXPECT_EQ(static_cast<int>(first[i].GetValue()), static_cast<int>(second[i].GetValue()));
    }
}


TEST(DeckTest, ToString)
{
    Deck deck;
    
    std::string expected = "Ac2c3c4c5c6c7c8c9cTcJcQcKcAd2d3d4d5d6d7d8d9dTdJdQdKdAh2h3h4h5h6h7h8h9hThJhQhKhAs2s3s4s5s6s7s8s9sTsJsQsKs";
    StringsEqual(expected, deck.ToString());
}

// ensures shuffling changes the deck
TEST(DeckTest, Shuffle)
{
    Deck deck;
    std::string initial = deck.ToString();

    deck.Shuffle();
    std::string shuffled = deck.ToString();

    EXPECT_NE(initial, shuffled);
}

// tests deal functionality
TEST(DeckTest, Deal)
{
    // create standard deck
    Deck deck;

    // expected 3 cards
    Card card1(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card card2(Card::Suit::CLUBS, Card::FaceValue::TWO);
    Card card3(Card::Suit::CLUBS, Card::FaceValue::THREE);

    std::vector<Card> expected = {card1, card2, card3};

    std::vector<Card> result = deck.Deal(3);

    VectorsEqual(expected, result);
}
