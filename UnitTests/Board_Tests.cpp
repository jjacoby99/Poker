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

TEST(BoardTest, TurnConstructor)
{
    // create default deck
    Deck deck;

    std::string deckstr = deck.ToString();

    Board board(deck.Deal(3), deck.Deal(1)[0]);

    std::vector<Card> flop = board.GetBoard();

    std::string actual;
    for(Card c: flop)
    {
        actual += c.ToString();
    }

    EXPECT_EQ(deckstr.substr(0,8), actual);
}

TEST(BoardTest, RiverConstructor)
{
    // create default deck
    Deck deck;

    std::string deckstr = deck.ToString();

    Board board(deck.Deal(3), deck.Deal(1)[0], deck.Deal(1)[0]);

    std::vector<Card> flop = board.GetBoard();

    std::string actual;
    for(Card c: flop)
    {
        actual += c.ToString();
    }

    EXPECT_EQ(deckstr.substr(0,10), actual);
}

TEST(BoardTest, Flop)
{
    Board b;
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ks(Card::Suit::SPADES, Card::FaceValue::KING);
    Card Qs(Card::Suit::SPADES, Card::FaceValue::QUEEN);

    std::vector<Card> threeCards = {As, Ks, Qs};

    b.Flop(threeCards);

    for(int i = 0; i < 3; i++)
    {
        EXPECT_EQ(static_cast<int>(b.GetBoard()[i].GetValue()), static_cast<int>(threeCards[i].GetValue()));
        EXPECT_EQ(static_cast<int>(b.GetBoard()[i].GetSuit()), static_cast<int>(threeCards[i].GetSuit()));

    }
}