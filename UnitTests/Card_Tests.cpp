#include <gtest/gtest.h>
#include "card.h"

// test default constructor
TEST(CardTest, DefaultConstructor) {
    Card card;
    EXPECT_EQ(card.GetSuit(), Card::Suit::SPADES);
    EXPECT_EQ(card.GetValue(), Card::FaceValue::ACE);
}

// Test Get methods
TEST(CardTest, ParameterizedConstructor) {
    Card card(Card::Suit::HEARTS, Card::FaceValue::QUEEN);
    EXPECT_EQ(card.GetSuit(), Card::Suit::HEARTS);
    EXPECT_EQ(card.GetValue(), Card::FaceValue::QUEEN);
}

// Test ToString method
TEST(CardTest, ToString) {
    Card card(Card::Suit::DIAMONDS, Card::FaceValue::TEN);
    EXPECT_EQ(card.ToString(), "Td");
    
    Card aceOfSpades(Card::Suit::SPADES, Card::FaceValue::ACE);
    EXPECT_EQ(aceOfSpades.ToString(), "As");
}
