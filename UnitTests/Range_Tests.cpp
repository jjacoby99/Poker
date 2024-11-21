#include <gtest/gtest.h>
#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/range.h"

TEST(RangeTests, PrintRange)
{
    std::pair<Card, Card> hand6 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::JACK)};
    std::pair<Card, Card> hand = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::KING)};
    std::pair<Card, Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::KING)};
    std::pair<Card, Card> hand3 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> hand5 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> hand7 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::JACK)};
    std::pair<Card, Card> hand8 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::TWO)};
    std::pair<Card, Card> hand9 = {Card(Card::Suit::SPADES, Card::FaceValue::TWO), Card(Card::Suit::CLUBS, Card::FaceValue::TWO)};
    
    // all combos of aces
    std::pair<Card, Card> AsAc = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE)};
    std::pair<Card, Card> AsAd = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE)};
    std::pair<Card, Card> AsAh = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::ACE)};
    std::pair<Card, Card> AcAh = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::HEARTS, Card::FaceValue::ACE)};
    std::pair<Card, Card> AcAd = {Card(Card::Suit::CLUBS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE)};
    std::pair<Card, Card> AhAd = {Card(Card::Suit::HEARTS, Card::FaceValue::ACE), Card(Card::Suit::DIAMONDS, Card::FaceValue::ACE)};

    // all combos of Kings
    std::pair<Card, Card> KsKc = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::CLUBS, Card::FaceValue::KING)};
    std::pair<Card, Card> KsKd = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING)};
    std::pair<Card, Card> KsKh = {Card(Card::Suit::SPADES, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::KING)};
    std::pair<Card, Card> KcKh = {Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::HEARTS, Card::FaceValue::KING)};
    std::pair<Card, Card> KcKd = {Card(Card::Suit::CLUBS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING)};
    std::pair<Card, Card> KhKd = {Card(Card::Suit::HEARTS, Card::FaceValue::KING), Card(Card::Suit::DIAMONDS, Card::FaceValue::KING)};
    
    // all combos of Queens
    std::pair<Card, Card> QsQc = {Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::CLUBS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> QsQd = {Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> QsQh = {Card(Card::Suit::SPADES, Card::FaceValue::QUEEN), Card(Card::Suit::HEARTS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> QcQh = {Card(Card::Suit::CLUBS, Card::FaceValue::QUEEN), Card(Card::Suit::HEARTS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> QcQd = {Card(Card::Suit::CLUBS, Card::FaceValue::QUEEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN)};
    std::pair<Card, Card> QhQd = {Card(Card::Suit::HEARTS, Card::FaceValue::QUEEN), Card(Card::Suit::DIAMONDS, Card::FaceValue::QUEEN)};

    std::vector<std::pair<Card, Card>> hands = {AsAc, AsAd, AsAh, AcAh, AcAd, AhAd, KsKc, KsKd, KsKh, KcKh, KcKd, KhKd, QsQc, QsQd, QsQh, QcQh, QcQd, QhQd};
    Range r(hands);
    r.PrintRangeHeaders();
    r.PrintRangeTable();
}

TEST(RangeTests, HandCombos)
{
    std::pair<Card, Card> hand1 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::JACK)};
    std::pair<Card, Card> hand2 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::SPADES, Card::FaceValue::JACK)};
    std::pair<Card, Card> hand3 = {Card(Card::Suit::SPADES, Card::FaceValue::ACE), Card(Card::Suit::CLUBS, Card::FaceValue::ACE)};

    std::vector<std::pair<Card, Card>> range = {hand1, hand2, hand3};
    Range r(range);
    int combos = r.GetHandCombos(hand1);

    // Try unsuited hand
    EXPECT_EQ(combos, 12);

    // Try suited hand
    combos = r.GetHandCombos(hand2);
    EXPECT_EQ(combos, 4);

    // try paired hand
    combos = r.GetHandCombos(hand3);
    EXPECT_EQ(combos, 6);
    


    /*---add a dead card---*/ 
    Card Ah(Card::Suit::HEARTS, Card::FaceValue::ACE);
    std::vector<Card> deadCards = {Ah};

    // Try unsuited hand
    combos = r.GetHandCombos(hand1, deadCards);
    EXPECT_EQ(combos, 9);

    // Try suited hand
    combos = r.GetHandCombos(hand2, deadCards);
    EXPECT_EQ(combos, 3);

    // Try paired hand
    combos = r.GetHandCombos(hand3, deadCards);
    EXPECT_EQ(combos, 3);

    /*---Add more dead cards---*/
    Card Ad(Card::Suit::HEARTS, Card::FaceValue::ACE);
    Card Jd(Card::Suit::DIAMONDS, Card::FaceValue::JACK);
    deadCards.push_back(Ad);
    deadCards.push_back(Jd);


    // Try unsuited hand
    // combos of AJo, given Ac, Ad, Jd are dead.
    combos = r.GetHandCombos(hand1, deadCards);
    EXPECT_EQ(combos, 4);

    // Try suited hand
    // combos of AJs, given Ac, Ad, Jd are dead.
    // two dead suits: clubs, diamonds. so 2 combos.
    combos = r.GetHandCombos(hand2, deadCards);
    EXPECT_EQ(combos, 2);

    // Try paired hand
    // combos of AA, given Ac, Ad, Jd are dead.
    // Ah As is the only remaining combo
    combos = r.GetHandCombos(hand3, deadCards);
    EXPECT_EQ(combos, 1);
}