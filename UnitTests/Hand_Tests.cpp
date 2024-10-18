#include <gtest/gtest.h>
#include "hand.h"
#include "deck.h"
#include <iostream>

void PrintHand(std::vector<Card>& h, std::string delim = " ")
{
    for(Card c: h)
    {
        std::cout << c.ToString() << delim;
    }
    std::cout << std::endl;
}
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

    // try another straight
    hand = {Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::SIX), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::THREE)};
    result = Hand::IsStraight(hand);
    EXPECT_EQ(result, true);
}

// test some non straights
TEST(HandTest, NotStraight)
{

    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::SIX), Card(Card::Suit::SPADES, Card::FaceValue::EIGHT), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};
    bool result = Hand::IsStraight(hand);
    EXPECT_EQ(result, false);


    //wrap around straight is not a straight
    hand = {Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN)};
    result = Hand::IsStraight(hand);
    EXPECT_EQ(result, false);

    //test a one gapper 
    hand = {Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::SIX)};
    result = Hand::IsStraight(hand);
    EXPECT_EQ(result, false);

}

TEST(HandTest, StraightFlush)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::SIX)};
    bool result = Hand::IsStraightFlush(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};
    result = Hand::IsStraightFlush(hand);
    EXPECT_EQ(result, true);
}


TEST(HandTest, TripsTest)
{

    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsThreeOfAKind(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::TEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::TEN), Card(Card::Suit::CLUBS, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::TWO)};
    result = Hand::IsThreeOfAKind(hand);
    EXPECT_EQ(result, true);
}

TEST(HandTest, NotTrips)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsThreeOfAKind(hand);
    EXPECT_EQ(result, false);

    //test a pair
    hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    result = Hand::IsThreeOfAKind(hand);
    EXPECT_EQ(result, false);
}

TEST(HandTest, Quads)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::HEARTS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsQuads(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::HEARTS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FOUR)};
    result = Hand::IsQuads(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::THREE)};
    result = Hand::IsQuads(hand);
    EXPECT_EQ(result, true);

}

TEST(HandTest, NotQuads)
{
    // three of a kind
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsQuads(hand);
    EXPECT_EQ(result, false);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::HEARTS, Card::FaceValue::EIGHT), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    result = Hand::IsQuads(hand);
    EXPECT_EQ(result, false);
}

TEST(HandTest, Pair)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    bool result = Hand::IsPair(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    result = Hand::IsPair(hand);
    EXPECT_EQ(result, true);
}

TEST(HandTest, NotPair)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::CLUBS, Card::FaceValue::SIX), Card(Card::Suit::HEARTS, Card::FaceValue::EIGHT), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsPair(hand);
    EXPECT_EQ(result, false);
}

TEST(HandTest, CountRecurring)
{
    Card c1(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card c2(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card c3(Card::Suit::DIAMONDS, Card::FaceValue::ACE);
    Card c4(Card::Suit::SPADES, Card::FaceValue::KING);
    Card c5(Card::Suit::CLUBS, Card::FaceValue::KING);

    std::vector<Card> hand = {c1, c2, c3, c4, c5};

    std::map<int, int> expected;
    int aceVal = 14;
    expected[aceVal] = 3;
    expected[static_cast<int>(c4.GetValue())] = 2;

    std::map<int, int> result = Hand::CountRecurring(hand);
    
    EXPECT_EQ(result[aceVal], expected[aceVal]);
    EXPECT_EQ(result[static_cast<int>(c4.GetValue())], expected[static_cast<int>(c4.GetValue())]);

    hand[0] = Card(Card::Suit::SPADES, Card::FaceValue::ACE);
    hand[1] = Card(Card::Suit::SPADES, Card::FaceValue::TWO);
    hand[2] = Card(Card::Suit::SPADES, Card::FaceValue::THREE);
    hand[3] = Card(Card::Suit::SPADES, Card::FaceValue::FOUR);
    hand[4] = Card(Card::Suit::SPADES, Card::FaceValue::FIVE);

    
    std::map<int, int> expected1;

    expected1[14] = 1;
    expected1[2] = 1;
    expected1[3] = 1;
    expected1[4] = 1;
    expected1[5] = 1;

    result = Hand::CountRecurring(hand);

    EXPECT_EQ(result[aceVal], 1);
    EXPECT_EQ(result[2], 1);
    EXPECT_EQ(result[3], 1);
    EXPECT_EQ(result[4], 1);
    EXPECT_EQ(result[5], 1);

}

TEST(HandTest, TwoPair)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsTwoPair(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TEN), Card(Card::Suit::HEARTS, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::FOUR)};
    result = Hand::IsTwoPair(hand);
    EXPECT_EQ(result, true);
}

TEST(HandTest, NotTwoPair)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::SIX), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    bool result = Hand::IsTwoPair(hand);
    EXPECT_EQ(result, false);
}


TEST(HandTest, FullHouse)
{
    std::vector<Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::TWO)};
    bool result = Hand::IsFullHouse(hand);
    EXPECT_EQ(result, true);

    hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE)};
    result = Hand::IsFullHouse(hand);
    EXPECT_EQ(result, true);

}

TEST(HandTest, CompareFullHouse)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::HEARTS, Card::FaceValue::TWO)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::HEARTS, Card::FaceValue::TWO), Card(Card::Suit::HEARTS, Card::FaceValue::THREE)};
    bool result = Hand::CompareFullHouse(hand1, hand2);

    EXPECT_EQ(result,true);

    result = Hand::CompareFullHouse(hand2, hand1);
    EXPECT_EQ(result,false);

    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE)};

    result = Hand::CompareFullHouse(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareFullHouse(hand2, hand1);
    EXPECT_EQ(result, true);

    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::THREE), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE)};

    result = Hand::CompareFullHouse(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareFullHouse(hand2, hand1);
    EXPECT_EQ(result, true);


}

TEST(HandTest, CompareFlush)
{
    Card ace(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card five(Card::Suit::CLUBS, Card::FaceValue::FIVE);
    Card six(Card::Suit::CLUBS, Card::FaceValue::SIX);
    Card seven(Card::Suit::CLUBS, Card::FaceValue::SEVEN);
    Card jack(Card::Suit::CLUBS, Card::FaceValue::JACK);
    Card ten(Card::Suit::CLUBS, Card::FaceValue::TEN);

    

    std::vector<Card> hand1 = {ten, five, six, seven, jack};
    

    std::vector<Card> hand2 = {ace, five, six, seven, jack};


    // h1 < h2: should be true
    bool result = Hand::CompareFlush(hand1, hand2);

    
    EXPECT_EQ(result, true);

    // h2 < h1: should be false
    result = Hand::CompareFlush(hand2, hand1);

    EXPECT_EQ(result, false);

}

TEST(HandTest, CompareStraight)
{
    std::vector<Card> hand1 = {Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::SIX), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::THREE)};
    std::vector<Card> hand2 = {Card(Card::Suit::CLUBS, Card::FaceValue::SEVEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::SIX), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::EIGHT)};

    bool result = Hand::CompareStraight(hand1, hand2);

    EXPECT_EQ(result, true);

    result = Hand::CompareStraight(hand2, hand1);

    EXPECT_EQ(result, false);

    // wheel
    hand1 = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::THREE)};
    
    result = Hand::CompareStraight(hand1, hand2);

    EXPECT_EQ(result, true);

    result = Hand::CompareStraight(hand2, hand1);

    EXPECT_EQ(result, false);

    
}

TEST(HandTest, AvsK)
{
    std::vector<Card> hand1 = {Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::NINE), Card(Card::Suit::SPADES, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK)};
    std::vector<Card> hand2 = {Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK)};

    // hand1 < hand 2
    bool result = Hand::CompareStraight(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::CompareStraight(hand2, hand1);
    EXPECT_EQ(result, false);
}

//Ensuring ace high straight beats wheel straight
TEST(HandTest, WheelvsA)
{
    std::vector<Card> wheel = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::THREE)};
    std::vector<Card> broadway = {Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK)};

    // wheel < broadway == true
    bool result = Hand::CompareStraight(wheel, broadway);
    EXPECT_EQ(result, true);

    // broadway > wheel == true
    result = Hand::CompareStraight(broadway, wheel);
    EXPECT_EQ(result, false);
}

TEST(HandTest, TripsCompare)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::DIAMONDS, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::DIAMONDS, Card::FaceValue::THREE), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};

    // hand1 < hand2 == true
    bool result = Hand::CompareTrips(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::CompareTrips(hand2, hand1);
    EXPECT_EQ(result, false);

    //ensure aces is best
    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::FOUR)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};

    result = Hand::CompareTrips(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareTrips(hand2, hand1);
    EXPECT_EQ(result, true);

    //ensure kickers matter
    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::FOUR)};


    result = Hand::CompareTrips(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareTrips(hand2, hand1);
    EXPECT_EQ(result, true);

    


}

TEST(HandTest, TripsCompareAceHigh)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};

    bool result = Hand::CompareTrips(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareTrips(hand2, hand1);
    EXPECT_EQ(result, true);

}

TEST(HandTest, CompareTwoPair)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};

    bool result = Hand::CompareTwoPair(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::CompareTwoPair(hand2, hand1);
    EXPECT_EQ(result, false);

    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};

    result = Hand::CompareTwoPair(hand1, hand2);
    EXPECT_EQ(result, false);
    
    result = Hand::CompareTwoPair(hand2, hand1);
    EXPECT_EQ(result, true);

    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};

    result = Hand::CompareTwoPair(hand1, hand2);
    EXPECT_EQ(result, false);
    
    result = Hand::CompareTwoPair(hand2, hand1);
    EXPECT_EQ(result, true);
}

TEST(HandTest, PairCompare)
{
    // pair1 < pair2
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::TEN), Card(Card::Suit::SPADES, Card::FaceValue::EIGHT)};

    bool result = Hand::ComparePair(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::ComparePair(hand2, hand1);
    EXPECT_EQ(result, false);

    // pair1 == pair2, kicker1 < kicker2
    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::TWO), Card(Card::Suit::SPADES, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::ACE)};

    result = Hand::ComparePair(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::ComparePair(hand2, hand1);
    EXPECT_EQ(result, false);
}

TEST(HandTest, CompareQuads)
{
    //quads1 < quads2
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};

    bool result = Hand::CompareQuads(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::CompareQuads(hand2, hand1);
    EXPECT_EQ(result, false);


    // quads1 == quads2, kicker1 < kicker2
    hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::FIVE)};
    hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::SIX)};

    result = Hand::CompareQuads(hand1, hand2);
    EXPECT_EQ(result, true);

    result = Hand::CompareQuads(hand2, hand1);
    EXPECT_EQ(result, false);

}

TEST(HandTest, CompareStraightFlush)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::NINE), Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::SPADES, Card::FaceValue::JACK), Card(Card::Suit::SPADES, Card::FaceValue::TEN)};

    bool result = Hand::CompareQuads(hand1, hand2);
    EXPECT_EQ(result, false);

    result = Hand::CompareQuads(hand2, hand1);
    EXPECT_EQ(result, true);
}

TEST(HandTest, CompareHighCard)
{
    std::vector<Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::SEVEN)};
    std::vector<Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::THREE), Card(Card::Suit::SPADES, Card::FaceValue::FOUR), Card(Card::Suit::SPADES, Card::FaceValue::FIVE), Card(Card::Suit::SPADES, Card::FaceValue::EIGHT)};

    bool result = Hand::CompareHighCard(hand1, hand2);
    EXPECT_EQ(result, true);
    
    result = Hand::CompareHighCard(hand2, hand1);
    EXPECT_EQ(result, false);
}

void HandsSame(std::vector<Card>& h1, std::vector<Card>& h2)
{
    for(int i = 0; i < 5; i++)
    {
        EXPECT_EQ(static_cast<int>(h1[i].GetValue()),static_cast<int>(h2[i].GetValue()));
        EXPECT_EQ(static_cast<int>(h2[i].GetSuit()), static_cast<int>(h2[i].GetSuit()));
    }
}
//make sure the best poker hand is recognized
TEST(HandTest, BestHandStraightFlush)
{
    Card TwoS(Card::Suit::SPADES, Card::FaceValue::TWO);
    Card ThreeC(Card::Suit::CLUBS, Card::FaceValue::THREE);
    Card FourD(Card::Suit::DIAMONDS, Card::FaceValue::FOUR);
    Card ThreeS(Card::Suit::SPADES, Card::FaceValue::THREE);
    Card FourS(Card::Suit::SPADES, Card::FaceValue::FOUR);
    Card FiveS(Card::Suit::SPADES, Card::FaceValue::FIVE);
    Card SixS(Card::Suit::SPADES, Card::FaceValue::SIX);

    // best is a straight flush
    std::vector<Card> cards = {TwoS, ThreeC, FourD, ThreeS, FourS, FiveS, SixS};
    
    std::vector<Card> expectedBest = {TwoS, ThreeS, FourS, FiveS, SixS};
    Hand::HandRanking expectedRanking = Hand::HandRanking::STRAIGHFLUSH;
    
    
    auto result = Hand::BestHand(cards);

    HandsSame(expectedBest, result.first);
    EXPECT_EQ(static_cast<int>(expectedRanking), static_cast<int>(result.second));


}
TEST(HandTest, BestHandRoyalFlush)
{
    Card AceS(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card AceC(Card::Suit::CLUBS, Card::FaceValue::ACE);
    Card KingS(Card::Suit::SPADES, Card::FaceValue::KING);
    Card QueenS(Card::Suit::SPADES, Card::FaceValue::QUEEN);
    Card JackS(Card::Suit::SPADES, Card::FaceValue::JACK);
    Card TenS(Card::Suit::SPADES, Card::FaceValue::TEN);
    Card AceD(Card::Suit::DIAMONDS, Card::FaceValue::ACE);

    // best is a straight flush
    std::vector<Card> cards = {AceS, AceC, KingS, QueenS, JackS, TenS, AceD};
    
    std::vector<Card> expectedBest = {TenS, JackS, QueenS, KingS, AceS};
    Hand::HandRanking expectedRanking = Hand::HandRanking::ROYALFLUSH;
    
    
    auto result = Hand::BestHand(cards);

    HandsSame(expectedBest, result.first);
    EXPECT_EQ(static_cast<int>(expectedRanking), static_cast<int>(result.second));
}

TEST(HandTest, StraightRecognize)
{
    Card KingS(Card::Suit::SPADES, Card::FaceValue::KING);
    Card QueenD(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN);
    Card JackC(Card::Suit::CLUBS, Card::FaceValue::JACK);
    Card TenS(Card::Suit::SPADES, Card::FaceValue::TEN);
    Card NineH(Card::Suit::HEARTS, Card::FaceValue::NINE);

    std::vector<Card> cards = {KingS, QueenD, JackC, TenS, NineH};
    
    Hand::HandRanking expectedRanking = Hand::HandRanking::STRAIGHT;
    auto result = Hand::EvaluateHand(cards);

    EXPECT_EQ(static_cast<int>(result), static_cast<int>(expectedRanking));

    Card Kings(Card::Suit::SPADES, Card::FaceValue::KING);
    Card SevenD(Card::Suit::DIAMONDS, Card::FaceValue::SEVEN);

    cards.push_back(Kings);
    cards.push_back(SevenD);

    std::pair<std::vector<Card>, Hand::HandRanking> r2 = Hand::BestHand(cards);
    std::vector<Card> expected = {NineH, TenS, JackC, QueenD, KingS};
    HandsSame(expected, r2.first);

    Hand h(cards);
    std::vector<std::vector<Card>> allHands;

    allHands = h.GeneratePokerHands();
    int i = 1;
    
    EXPECT_EQ(static_cast<int>(Hand::HandRanking::STRAIGHT), static_cast<int>(r2.second));

}

/*TEST(HandTest, BestHandBoard)
{
    Card KingS(Card::Suit::SPADES, Card::FaceValue::KING);
    Card KingD(Card::Suit::DIAMONDS, Card::FaceValue::KING);
    Card QueenD(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN);
    Card JackC(Card::Suit::CLUBS, Card::FaceValue::JACK);
    Card TenS(Card::Suit::SPADES, Card::FaceValue::TEN);
    Card NineH(Card::Suit::HEARTS, Card::FaceValue::NINE);
    Card ThreeC(Card::Suit::CLUBS, Card::FaceValue::THREE);
    Card SevenD(Card::Suit::DIAMONDS, Card::FaceValue::SEVEN);

    std::vector<Card> cards = {ThreeC, QueenD, JackC, TenS, NineH};
    Board b;
    b.AddCards(cards);
    std::pair<Card, Card> holeCards = {KingS, KingD};


    std::pair<std::vector<Card>, Hand::HandRanking> r2 = Hand::BestHand(b, holeCards);
    std::vector<Card> expected = {NineH, TenS, JackC, QueenD, KingS};
    HandsSame(expected, r2.first);

    EXPECT_EQ(static_cast<int>(Hand::HandRanking::STRAIGHT), static_cast<int>(r2.second));

}*/



TEST(HandTest, PruningEvaluateFullHouse)
{
    Card Ks(Card::Suit::SPADES, Card::FaceValue::KING);
    Card Kd(Card::Suit::DIAMONDS, Card::FaceValue::KING);
    Card Qd(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN);
    Card Jc(Card::Suit::CLUBS, Card::FaceValue::JACK);
    Card Ts(Card::Suit::SPADES, Card::FaceValue::TEN);

    Card Qh(Card::Suit::HEARTS, Card::FaceValue::QUEEN);
    Card Qc(Card::Suit::CLUBS, Card::FaceValue::QUEEN);

    std::vector<Card> board = {Ks, Kd, Qd, Jc, Ts};
    Board b;
    b.AddCards(board);

    std::cout << std::endl;
    std::pair<Card, Card> holeCards = {Qh, Qd};
    
    std::vector<Card> hand = {Ks, Kd, Qd, Qh, Qd};

    auto pos = Hand::GetPossibleHands(b);
    //auto result = Hand::EvaluateHand2(std::vector<Card>& hand, const std::map<HandRanking, bool>& possibleHands)
    auto result = Hand::EvaluateHand2(hand, pos);
    EXPECT_EQ(static_cast<int>(result), static_cast<int>(Hand::HandRanking::FULLHOUSE));
}
// Board where straights, full houses, and full houses are impossible.
TEST(HandTest, MultipleNotPossible)
{
    Card Ks(Card::Suit::SPADES, Card::FaceValue::KING);
    Card Td(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    Card Ec(Card::Suit::CLUBS, Card::FaceValue::EIGHT);
    Card Fh(Card::Suit::HEARTS, Card::FaceValue::FIVE);
    Card Threes(Card::Suit::SPADES, Card::FaceValue::THREE);

    Card Eh(Card::Suit::HEARTS, Card::FaceValue::EIGHT);
    Card Es(Card::Suit::SPADES, Card::FaceValue::EIGHT);

    std::vector<Card> board = {Ks, Td, Ec, Fh, Threes};
    std::pair<Card, Card> holeCards = {Eh, Es};

    std::vector<Card> hand = {Ks, Td, Ec, Eh, Es};

    Board b;
    b.AddCards(board);

    auto pos = Hand::GetPossibleHands(b);
    std::vector<bool> expectedPossible = {true, true, true, true, false, false, false, false, false, false};
    int i = 0;
    for(auto el: pos)
    {
        EXPECT_EQ(expectedPossible[i++], el.second);
    }
    
    auto result = Hand::EvaluateHand2(hand, pos);
    EXPECT_EQ(static_cast<int>(result), static_cast<int>(Hand::HandRanking::THREEOFAKIND));

}