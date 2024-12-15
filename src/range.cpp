#include "range.h"


// maps to store the suit combos to their respective tuple indices in range table
// can be done programatically, but done this way to save time

// order doesn't matter for pairs, ie AhAs == AsAh
static const std::map<std::pair<Card::Suit, Card::Suit>, size_t> pair2index = {
    {{Card::Suit::SPADES, Card::Suit::HEARTS}, 0},
    {{Card::Suit::SPADES, Card::Suit::DIAMONDS}, 1},
    {{Card::Suit::SPADES, Card::Suit::CLUBS}, 2},
    {{Card::Suit::HEARTS, Card::Suit::DIAMONDS}, 3},
    {{Card::Suit::HEARTS, Card::Suit::CLUBS}, 4},
    {{Card::Suit::DIAMONDS, Card::Suit::CLUBS}, 5}
};

// only one suit required for suited conversion
static const std::map<Card::Suit, size_t> suited2index = {
    {{Card::Suit::SPADES}, 0},
    {{Card::Suit::HEARTS}, 1},
    {{Card::Suit::DIAMONDS}, 2},
    {{Card::Suit::CLUBS}, 3}
};

// order DOES matter for unsuited hands, ie AhKc != AcKh
static const std::map<std::pair<Card::Suit, Card::Suit>, size_t> offsuit2index = {
    {{Card::Suit::SPADES, Card::Suit::HEARTS}, 0},
    {{Card::Suit::SPADES, Card::Suit::DIAMONDS}, 1},
    {{Card::Suit::SPADES, Card::Suit::CLUBS}, 2},
    {{Card::Suit::HEARTS, Card::Suit::SPADES}, 3},
    {{Card::Suit::HEARTS, Card::Suit::DIAMONDS}, 4},
    {{Card::Suit::HEARTS, Card::Suit::CLUBS}, 5},
    {{Card::Suit::DIAMONDS, Card::Suit::SPADES}, 6},
    {{Card::Suit::DIAMONDS, Card::Suit::HEARTS}, 7},
    {{Card::Suit::DIAMONDS, Card::Suit::CLUBS}, 8},
    {{Card::Suit::CLUBS, Card::Suit::SPADES}, 9},
    {{Card::Suit::CLUBS, Card::Suit::HEARTS}, 10},
    {{Card::Suit::CLUBS, Card::Suit::DIAMONDS}, 11}
};

Range::Range()
{
    // initialize range table sizes with all false

    for(int row = 0; row < 14; row++)
    {
        for(int col = 0; col < 14; col++)
        {
            int combos = 0;
            if(row == col) // pair
            {
                combos = 6;
            }
            else if(row < col) // suited hand
            {
                combos = 4;
            }
            else // unsuited hand
            {
                combos = 12;
            }

            for(int i = 0; i < combos; i++)
            {
                this->rangeTable[row][col].push_back(false);
            }
        }
    }
}

Range::Range(const std::vector<std::pair<Card, Card>>& range, const std::vector<Card>& deadCards)
{
    for(int row = 0; row < 13; row++)
    {
        for(int col = 0; col < 13; col++)
        {
            int combos = 0;
            if(row == col) // pair
            {
                combos = 6;
            }
            else if(row < col) // suited hand
            {
                combos = 4;
            }
            else // unsuited hand
            {
                combos = 12;
            }

            // 4 is the starting size of rangeTable[i][j], so we need to push back combos - 4 elements
            for(int i = 0; i < combos - 4; i++)
            {
                this->rangeTable[row][col].push_back(0.0);
            }
        }
    }
    

    for(const std::pair<Card, Card>& hand: range)
    {
        if(this->IsPairHand(hand))
        {
            size_t index = static_cast<size_t>(hand.first.GetValue());
            if(index == 1)
            {
                // ace
                index = 0;
            }
            else
            {
                // King = 1, Queen = 2, Jack = 3, ...
                index = 14 - index;
            }
            
            // order of suits for pairs doesn't matter, ei AsAc == AcAs, need to give pair2index the proper order
            size_t handIdx = pair2index.at(std::make_pair(
                                hand.first.GetSuit() > hand.second.GetSuit()? hand.first.GetSuit(): hand.second.GetSuit(),                  
                                hand.first.GetSuit() < hand.second.GetSuit()? hand.first.GetSuit(): hand.second.GetSuit()));

            this->rangeTable[index][index][handIdx] = 1.0; 
        }
        else if(this->IsSuitedHand(hand))
        {
            // row is the highest face value
            int val1 = static_cast<int>(hand.first.GetValue());
            int val2 = static_cast<int>(hand.second.GetValue());

            if(val1 == 1)
            {
                val1 = 14;
            }
            else if(val2 == 1)
            {
                val2 = 14;
            }
            size_t row = val1 > val2 ? static_cast<size_t>(val1): static_cast<size_t>(val2);
            size_t col = row == val1 ? static_cast<size_t>(val2): static_cast<size_t>(val1);


            if(row == 1)
            {
                row = 0;
            }
            else
            {
                row = 14 - row;
            }

            // col can't be an ace
            col = 14 - col;

            // both suits are the same so we only need one
            size_t handIdx = suited2index.at(hand.first.GetSuit());

            this->rangeTable[row][col][handIdx] = 1.0;

        }
        else
        {
            // dealing with an unsuited unpaired hand

            // col is the highest face value
            int val1 = static_cast<int>(hand.first.GetValue());
            int val2 = static_cast<int>(hand.second.GetValue());

            if(val1 == 1)
            {
                val1 = 14;
            }
            else if(val2 == 1)
            {
                val2 = 14;
            }

            size_t col = val1 > val2 ? static_cast<size_t>(val1): static_cast<size_t>(val2);
            size_t row = col == val1 ? static_cast<size_t>(val2): static_cast<size_t>(val1);

            if(col == 1)
            {
                col = 0;
            }
            else
            {
                col = 14 - col;
            }

        
            // row can't be an ace
            row = 14 - row;

            // order of suits is important
            size_t handIdx = offsuit2index.at(std::make_pair(hand.first.GetSuit(), hand.second.GetSuit()));
            this->rangeTable[row][col][handIdx] = 1.0;
        }
    }
}


Range::Range(const Range& other)
{
    this->rangeTable = other.GetRangeTable();
}

Range::Range(const std::vector<std::map<std::pair<Card,Card>, double>>& rangeFrequencies)
{
    
}

Range::Range(const std::pair<Card, Card>& bottomOffsuit, const std::pair<Card, Card>& bottomSuited, const std::pair<Card, Card>& bottomPair)
{

}

std::vector<std::vector<std::vector<double>>> Range::GetRangeTable() const
{
    return this->rangeTable;
}
void Range::PrintRangeTable()
{
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            double frequency = 0;
            for(int k = 0; k < this->rangeTable[i][j].size(); k++)
            {
                this->rangeTable[i][j][k]? frequency += 1.0: 0;
            }
            
            double combos = 0.0;
            if(i == j)
            {
                combos = 6;
            }
            else if(i < j)
            {
                combos = 4;
            }
            else
            {
                combos = 12;
            }
            frequency /= combos;

            std::cout << frequency;

            if(j != 12)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Range::PrintRangeHeaders()
{
    std::cout << "AA \tAKs\tAQs\tAJs\tATs\tA9s\tA8s\tA7s\tA6s\tA5s\tA4s\tA3s\tA2s" << std::endl;
    std::cout << "AKo\tKK \tKQs\tKJs\tKTs\tK9s\tK8s\tK7s\tK6s\tK5s\tK4s\tK3s\tK2s" << std::endl;
    std::cout << "AQo\tKQo\tQQ \tQJs\tQTs\tQ9s\tQ8s\tQ7s\tQ6s\tQ5s\tQ4s\tQ3s\tQ2s" << std::endl;
    std::cout << "AJo\tKJo\tQJo\tJJ \tJTs\tJ9s\tJ8s\tJ7s\tJ6s\tJ5s\tJ4s\tJ3s\tJ2s" << std::endl;
    std::cout << "ATo\tKTo\tQTo\tJTo\tTT \tT9s\tT8s\tT7s\tT6s\tT5s\tT4s\tT3s\tT2s" << std::endl;
    std::cout << "A9o\tK9o\tQ9o\tJ9o\tT9o\t99 \t98s\t97s\t96s\t95s\t94s\t93s\t92s" << std::endl;
    std::cout << "A8o\tK8o\tQ8o\tJ8o\tT8o\t98o\t88 \t87s\t86s\t85s\t84s\t83s\t82s" << std::endl;
    std::cout << "A7o\tK7o\tQ7o\tJ7o\tT7o\t97o\t87o\t77 \t76s\t75s\t74s\t73s\t72s" << std::endl;
    std::cout << "A6o\tK6o\tQ6o\tJ6o\tT6o\t96o\t86o\t76o\t66 \t65s\t64s\t63s\t62s" << std::endl;
    std::cout << "A5o\tK5o\tQ5o\tJ5o\tT5o\t95o\t85o\t75o\t65o\t55 \t54s\t53s\t52s" << std::endl;
    std::cout << "A4o\tK4o\tQ4o\tJ4o\tT4o\t94o\t84o\t74o\t64o\t54o\t44 \t43s\t42s" << std::endl;
    std::cout << "A3o\tK3o\tQ3o\tJ3o\tT3o\t93o\t83o\t73o\t63o\t53o\t43o\t33 \t32s" << std::endl;
    std::cout << "A2o\tK2o\tQ2o\tJ2o\tT2o\t92o\t82o\t72o\t62o\t52o\t42o\t32o\t22 " << std::endl;
}
/*const std::vector<double>& Range::operator[](size_t index) const
{
    return this->rangeTable[index];
}*/
bool Range::IsOffSuitHand(const std::pair<Card,Card>& hand)
{
    return hand.first.GetSuit() != hand.second.GetSuit();
}

bool Range::IsSuitedHand(const std::pair<Card, Card>& hand)
{
    return hand.first.GetSuit() == hand.second.GetSuit();
}

bool Range::IsPairHand(const std::pair<Card, Card>& hand)
{
    return hand.first.GetValue() == hand.second.GetValue();
}

int CountAvailableCards(const Card& c, const std::vector<Card>& deadCards)
{
    int count = 4;
    for(const Card& card: deadCards)
    {
        if(c.GetValue() == card.GetValue() && c.GetSuit() == card.GetSuit())
        {
            count--;
        }
    }
    return count;
}
int CountAvailableRanks(const Card& c, const std::vector<Card>& deadCards)
{
    int count = 4;
    Card::FaceValue rank = c.GetValue();
    for(const Card& card: deadCards)
    {
        if(card.GetValue() == rank)
        {
            count--;
        }
    }
    return count;
}
std::map<Card::Suit, bool> MapDeadSuits(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards)
{
    std::map<Card::Suit, bool> deadSuits;
    deadSuits[Card::Suit::CLUBS] = false;
    deadSuits[Card::Suit::SPADES] = false;
    deadSuits[Card::Suit::HEARTS] = false;
    deadSuits[Card::Suit::DIAMONDS] = false;

    int countDeadSuits = 0;
    for(const Card& c: deadCards)
    {
        if(c.GetValue() == hand.first.GetValue() || c.GetValue() == hand.second.GetValue())
        {
            deadSuits[c.GetSuit()] = true;
        }
    }
    return deadSuits;
}
int CountDeadSuits(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards)
{
    std::map<Card::Suit, bool> deadSuits = MapDeadSuits(hand, deadCards);
    int countDeadSuits = 0;
    for(auto el: deadSuits)
    {
        if(el.second)
        {
            countDeadSuits++;
        }
    }
    return countDeadSuits;
}
int Range::GetHandCombos(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards)
{
    int deadSuits = CountDeadSuits(hand, deadCards);

    if(this->IsSuitedHand(hand))
    {
        if(deadCards.size() == 0)
        {
            return 4;
        }
        
        return 4 - deadSuits;
    }
    if(this->IsPairHand(hand))
    {
        if(deadCards.size() == 0)
        {
            return 6;
        }
        int availableRank = CountAvailableRanks(hand.first, deadCards);
        return availableRank * (availableRank - 1) / 2;
    }
    
    // Unsuited hand: Consider all suit combinations and subtract suited hands
    if(deadCards.size() == 0)
    {
        return 12;
    }
    
    int availableRank1 = CountAvailableRanks(hand.first, deadCards);
    int availableRank2 = CountAvailableRanks(hand.second, deadCards);
    

    return (availableRank1 * availableRank2) - (4 - deadSuits);
}


void Range::UpdateRange(const std::vector<Card>& newDead)
{
    for(const Card& c: newDead)
    {
        int idx = static_cast<int>(c.GetValue());
        if(idx == 1)
        {
            // ace
            idx = 0;
        }
        else
        {
            idx = 14 - idx;
        }

    }

    for(const Card& c: newDead)
    {
        this->deadCards.push_back(c);
    }

}