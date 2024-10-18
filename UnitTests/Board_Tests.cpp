#include <gtest/gtest.h>
#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/board.h"

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

TEST(BoardTest, PossibleStraight)
{
    Board b;
    Card Twos(Card::Suit::SPADES, Card::FaceValue::TWO);
    Card Fours(Card::Suit::SPADES, Card::FaceValue::FOUR);
    Card Sixs(Card::Suit::SPADES, Card::FaceValue::SIX);

    Card Td(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    Card Kc(Card::Suit::CLUBS, Card::FaceValue::KING);

    std::vector<Card> flop = {Twos, Fours, Sixs};
    b.Flop(flop);
    
    bool result = b.PossibleStraight();
    EXPECT_EQ(result, true);

    b.Turn(Td);
    b.River(Kc);

    EXPECT_EQ(b.PossibleStraight(), true);
}

TEST(BoardTest, NotPossibleStraight)
{
    Board b;
    Card Twos(Card::Suit::SPADES, Card::FaceValue::TWO);
    Card Fours(Card::Suit::SPADES, Card::FaceValue::FOUR);
    Card Sevs(Card::Suit::SPADES, Card::FaceValue::SEVEN);

    Card Td(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    Card Kc(Card::Suit::CLUBS, Card::FaceValue::KING);

    std::vector<Card> flop = {Twos, Fours, Sevs};
    b.Flop(flop);
    
    bool result = b.PossibleStraight();
    EXPECT_EQ(result, false);

    b.Turn(Td);
    b.River(Kc);

    EXPECT_EQ(b.PossibleStraight(), false);
}

TEST(BoardTest, Broadway)
{
    Board b;
    Card Jh(Card::Suit::HEARTS, Card::FaceValue::JACK);
    Card Fours(Card::Suit::SPADES, Card::FaceValue::FOUR);
    Card Sevs(Card::Suit::SPADES, Card::FaceValue::SEVEN);

    Card Td(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    Card Kc(Card::Suit::CLUBS, Card::FaceValue::KING);

    std::vector<Card> cards = {Jh, Fours, Sevs, Td, Kc};

    b.AddCards(cards);

    EXPECT_EQ(b.PossibleStraight(), true);

    Board b2;

    cards[3] = Card(Card::Suit::SPADES, Card::FaceValue::ACE);
    
    b2.AddCards(cards);

    EXPECT_EQ(b2.PossibleStraight(), true);
}

TEST(BoardTest, Wheel)
{
    Board b;
    Card Fivec(Card::Suit::CLUBS, Card::FaceValue::FIVE);
    Card Fours(Card::Suit::SPADES, Card::FaceValue::FOUR);
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);

    Card Td(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    Card Kc(Card::Suit::CLUBS, Card::FaceValue::KING);

    std::vector<Card> cards = {Fivec, Fours, As, Td, Kc};
    b.AddCards(cards);

    EXPECT_EQ(b.PossibleStraight(), true);
}