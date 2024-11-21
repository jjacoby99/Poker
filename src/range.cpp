#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/range.h"



Range::Range(const std::vector<std::pair<Card, Card>>& range, const std::vector<Card>& deadCards)
{
    double frequency = 1.0;

    std::vector<std::pair<Card, Card>> offSuitHands;
    std::vector<std::pair<Card, Card>> suitedHands;
    std::vector<std::pair<Card, Card>> pairedHands;

    for(auto p: range)
    {
        std::cout << "Hand: " << p.first << p.second << std::endl;
    }
    for(const std::pair<Card, Card>& hand: range)
    {
        // classify each specific hand into it's category for the rangeTable
        if(this->IsPairHand(hand))
        {
            // paired hand, insert by face value
            pairedHands.push_back(hand);
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
            this->rangeTable[index][index] += 1.0 / static_cast<double>(this->GetHandCombos(hand, deadCards));
        }
        else if(this->IsSuitedHand(hand))
        {
            // row is the highest face value
            suitedHands.push_back(hand);
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

            this->rangeTable[row][col] += 1.0 / static_cast<double>(this->GetHandCombos(hand, deadCards));
        }
        else
        {
            // dealing with an unsuited unpaired hand
            // these hands make up the lower triangle of the table
            offSuitHands.push_back(hand);

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
            this->rangeTable[row][col] += 1.0 / static_cast<double>(this->GetHandCombos(hand, deadCards));
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

std::vector<std::vector<double>> Range::GetRangeTable() const
{
    return this->rangeTable;
}
void Range::PrintRangeTable()
{
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            std::cout << this->rangeTable[i][j];
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

double Range::GetSingleHandFrequency(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards)
{
    int startCombos = 1;
    if(this->IsPairHand(hand))
    { 
        startCombos = 6;
        int cards = 4;
        for(const Card& card: deadCards)
        {
            if(card.GetValue() == hand.first.GetValue())
            {
                cards--;
            }
        }

        // number of combos is cards choose 2
        return static_cast<double>(cards * (cards - 1)) / 2.0 / startCombos;
    }

    // steps
    // determine how many dead cards have the same face value as one card in the hand
    // determine how many combos. 

    return 1.0;
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
int Range::GetHandCombos(const std::pair<Card, Card>& hand, const std::vector<Card>& deadCards)
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
    for(auto el: deadSuits)
    {
        if(el.second)
        {
            countDeadSuits++;
        }
    }
    if(this->IsSuitedHand(hand))
    {
        if(deadCards.size() == 0)
        {
            return 4;
        }
        
        return 4 - countDeadSuits;
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
    

    return (availableRank1 * availableRank2) - (4 - countDeadSuits);
}