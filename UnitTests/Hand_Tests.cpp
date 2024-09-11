#include <gtest/gtest.h>
#include "hand.h"
#include "deck.h"
#include <iostream>


// ensures all 21 permutations of 5 card hands from 7 cards are being generated 
TEST(HandTest, HandPermutations)
{
    std::vector<Card> cards;

    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::ACE));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::TWO));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::THREE));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::FOUR));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::FIVE));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::SIX));
    cards.push_back(Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN));


    Hand h(cards);
    std::vector<std::vector<Card>> allHands;

    allHands = h.GeneratePokerHands();

    // generate expected
    std::vector<std::vector<Card>> expected(21);

    expected[0] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE)};
    expected[1] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX)};
    expected[2] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[3] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX)};
    expected[4] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[5] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[6] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX)};
    expected[7] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[8] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[9] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[10] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX)};
    expected[11] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[12] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[13] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[14] = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[15] = {Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX)};
    expected[16] = {Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[17] = {Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[18] = {Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[19] = {Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};
    expected[20] = {Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::FIVE), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN)};




    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            EXPECT_EQ(allHands[i][j].ToString(), expected[i][j].ToString());
        }
    }
}

// tests that a flush is recognized as a flush
TEST(HandTest, Flush)
{
    Card one(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card two(Card::Suit::CLUBS, Card::FaceValue::FIVE);
    Card three(Card::Suit::CLUBS, Card::FaceValue::SIX);
    Card four(Card::Suit::CLUBS, Card::FaceValue::SEVEN);
    Card five(Card::Suit::CLUBS, Card::FaceValue::JACK);

    std::vector<Card> hand = {one, two, three, four, five};

    Hand h(hand);

    bool result = h.IsFlush(hand);
    EXPECT_EQ(result, true);
}

// tests that a non flush is not recognized as a flush
TEST(HandTest, NotFlush)
{
    Card one(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card two(Card::Suit::SPADES, Card::FaceValue::FIVE);
    Card three(Card::Suit::CLUBS, Card::FaceValue::SIX);
    Card four(Card::Suit::CLUBS, Card::FaceValue::SEVEN);
    Card five(Card::Suit::CLUBS, Card::FaceValue::JACK);

    std::vector<Card> hand = {one, two, three, four, five};

    bool result = Hand::IsFlush(hand);
    EXPECT_EQ(result, false);
}

TEST(HandTest, ValueCompare)
{
    Card c1(Card::Suit::CLUBS, Card::FaceValue::ACE);

    Card c2(Card::Suit::SPADES, Card::FaceValue::KING);

    Card c3(Card::Suit::DIAMONDS, Card::FaceValue::TWO);

    // shouuld be false
    bool r1 = Hand::CompareFaceValue(c1, c2);
    EXPECT_EQ(r1, false);

    // should be true
    bool r2 = Hand::CompareFaceValue(c2, c1);
    EXPECT_EQ(r2, true);

    // should be false
    bool r3 = Hand::CompareFaceValue(c1, c3);
    EXPECT_EQ(r3, false);

    // should be true;
    bool r4 = Hand::CompareFaceValue(c3, c1);
    EXPECT_EQ(r4, true);

    // should be false
    bool r5 = Hand::CompareFaceValue(c2, c3);
    EXPECT_EQ(r5, false);

    // should be true
    bool r6 = Hand::CompareFaceValue(c3, c2);
    EXPECT_EQ(r6, true);

}

TEST(HandTest, RoyalFlush)
{

    // Test spades 
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};

    bool result = Hand::IsRoyalFlush(hand);
    EXPECT_EQ(result, true);

    // test diamonds
    hand = {Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::JACK), Card(Card::Suit::DIAMONDS, Card::FaceValue::TEN)};
    result = Hand::IsRoyalFlush(hand);
    EXPECT_EQ(result, true);
}


TEST(HandTest, NotRoyal)
{
    // test the Ace through ten straight with one incorrect suit
    std::vector<Card> hand = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};

    bool result = Hand::IsRoyalFlush(hand);
    EXPECT_EQ(result, false);


    // test some random hand

    hand[0] = Card(Card::Suit::DIAMONDS, Card::FaceValue::SEVEN);
    hand[1] = Card(Card::Suit::CLUBS, Card::FaceValue::EIGHT);
    hand[2] = Card(Card::Suit::SPADES, Card::FaceValue::ACE);
    hand[3] = Card(Card::Suit::HEARTS, Card::FaceValue::QUEEN);
    hand[4] = Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO);

    result = Hand::IsRoyalFlush(hand);
    EXPECT_EQ(result, false);
}

TEST(HandTest, Straight)
{
    // royal flush is also a straight
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};

    bool result = Hand::IsStraight(hand);
    EXPECT_EQ(result, true);


    // try wheel straight
    hand = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::TWO)};
    result = Hand::IsStraight(hand);
    EXPECT_EQ(result, true);


}