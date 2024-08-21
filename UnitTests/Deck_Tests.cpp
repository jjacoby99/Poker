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

TEST(DeckTest, ToString)
{
    Deck deck;
    
    std::string expected = "Ac2c3c4c5c6c7c8c9cTcJcQcKcAd2d3d4d5d6d7d8d9dTdJdQdKdAh2h3h4h5h6h7h8h9hThJhQhKhAs2s3s4s5s6s7s8s9sTsJsQsKs";
    StringsEqual(expected, deck.ToString());
}
