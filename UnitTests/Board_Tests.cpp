#include <gtest/gtest.h>
#include "board.h"

TEST(BoardTest, FlopConstructor)
{
    // create default deck
    Deck deck;

    std::string deckstr = deck.ToString();

    Board board(deck.Deal(3));

    std::vector<Card> flop = board.GetBoard();

    std::string actual;
    for(Card c: flop)
    {
        actual += c.ToString();
    }

    EXPECT_EQ(deckstr.substr(0,6), actual);

}