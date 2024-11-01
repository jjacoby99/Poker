#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/game.h"
#include <iostream>
#include <sstream>
Game::Game(std::vector<Player> startPlayers, double sb, double bb)
{
    this->smallBlind = sb;
    this->bigBlind = bb;

    this->maxBuyIn = 100.0 * bb;


    for(Player& p: startPlayers)
    {

        this->playerList.push_back(p);
    }

    this->button = this->playerList.size() - 1;
    this->turn = 2; // 0 - sb, 1 - bb, 2, utg1

    this->deck.Shuffle();
    this->pot = 0.0;
}
bool Game::NextRound() 
{
    if (this->playerList[0].GetAction() == Player::Action::FOLD) {
        // Award pot to player 1 and end hand
        this->playerList[0].Win(this->pot);
        this->pot = 0;
        return false;
    } else if (this->playerList[1].GetAction() == Player::Action::FOLD) {
        // Award pot to player 0 and end hand
        this->playerList[1].Win(this->pot);
        this->pot = 0;
        return false;
    }
    if(this->playerList[0].GetAction() == Player::Action::CHECK && this->playerList[1].GetAction() == Player::Action::CHECK
    && this->playerList[0].currentBet == this->playerList[1].currentBet)
    {
        // player 0 checked and player 1 checked, round over
        return true;
    }

    // Check if all active players have matched the highest bet
    if(this->playerList[0].GetAction() == Player::Action::BET && this->playerList[1].GetAction() == Player::Action::CALL
    && this->playerList[0].currentBet == this->playerList[1].currentBet)
    {
        // player 0 bet and player 1 called, round over
        return true;
    }
    if(this->playerList[1].GetAction() == Player::Action::BET && this->playerList[0].GetAction() == Player::Action::CALL
    && this->playerList[0].currentBet == this->playerList[1].currentBet)
    {
        // player 1 bet and player 0 called, round over
        return true;
    }
    if(this->playerList[1].GetAction() == Player::Action::CALL && this->playerList[0].GetAction() == Player::Action::CHECK
    && this->playerList[0].currentBet == this->playerList[1].currentBet && this->preFlop)
    {
        // pre-flop, player 1 called, and player 0 checked, round over
        return true;
    }
    if(this->playerList[0].GetAction() == Player::Action::CALL && this->playerList[1].GetAction() == Player::Action::CHECK
    && this->playerList[0].currentBet == this->playerList[1].currentBet && this->preFlop)
    {
        // pre-flop, player 0 called, and player 1 checked, round over.
        return true;
    }

    // Continue pre-flop betting as one player has raised
    return false;
}

// simulates a player's action. based on their index and the amount to call determines the actions that are possible. 
// Returns 0 for check (if possible), the bet amount for bet, and -1 for fold
int Game::Action(int playerIdx, double bet, const std::string& street )
{
    int result = 0;

    if(bet - this->playerList[playerIdx].currentBet == 0)
    {
        // can check or raise
        std::cout << street << ", action on "  << this->playerList[playerIdx].GetName() << ". Options:\n1) Enter '0' to check.\n2) Enter a bet amount >= " << 2 * this->bigBlind << " to raise." << std::endl;
        std::cin >> result;

        if(result == 0)
        {
            // player checked, action over
            std::cout << street << ". " << this->playerList[playerIdx].GetName() << " checked." << std::endl;
            this->playerList[playerIdx].Check();
            return 0;
        }
        else if (result >= this->bigBlind * 2)
        {
            // player bet, add to pot and return bet amount
            std::cout << street << ". " << this->playerList[playerIdx].GetName() << " bet $" << result  << "." << std::endl;
            this->pot += this->playerList[playerIdx].Bet(result - this->playerList[playerIdx].currentBet);
            return result;
        }
    }

    //check if player would be all in to call
    if(this->playerList[playerIdx].GetStack() + this->playerList[playerIdx].currentBet < bet)
    {
        // player would be all in, can only call or fold
        std::cout << street << ", action on "  << this->playerList[playerIdx].GetName() << ". Options:\n1) Enter '1' to call ALL IN.\n2) Enter -1 to fold." << std::endl;
        std::cin >> result;
        if(result == 1)
        {
            // player called all in
            std::cout << street << ". " << this->playerList[playerIdx].GetName() << " called ALL IN." << std::endl;
            double stack = this->playerList[playerIdx].GetStack();
            this->pot += this->playerList[playerIdx].Call(bet - this->playerList[playerIdx].currentBet); // handles all in
            return stack;
        }
        // player folded
        this->playerList[playerIdx].Fold();
        std::cout << street << ". " << this->playerList[playerIdx].GetName() << "folded." << std::endl;
        return -1;
    }

    // player has no option to check, can either call, raise, or fold
    std::cout << street << ", action on "  << this->playerList[playerIdx].GetName() << ". Options:\n1) Enter '1' to call $" << bet - this->playerList[playerIdx].currentBet << ".\n2) Enter a bet amount >= " << 2 * bet << " to raise.\n3) Enter -1 to fold." << std::endl;
    std::cin >> result;

    if(result == 1)
    {
        // player called
        std::cout << street << ". " << this->playerList[playerIdx].GetName() << " called." << std::endl;
        double cur = this->playerList[playerIdx].currentBet;
        this->pot += this->playerList[playerIdx].Call(bet - cur);
        return bet + cur;
    }
    if(result >= 2 * bet)
    {
        // player raised
        this->pot -= this->playerList[playerIdx].currentBet;
        this->pot += this->playerList[playerIdx].Bet(result);
        std::cout << street << ". " << this->playerList[playerIdx].GetName() << " raised $" << result  << "." << std::endl;
        return result;
    }
    // player folded
    if(result == -1)
    {
        this->playerList[playerIdx].Fold();
        std::cout << street << ". " << this->playerList[playerIdx].GetName() << " folded." << std::endl;
        return -1;
    }
    std::cout << "Invalid input, call assumed. ($" << bet - this->playerList[playerIdx].currentBet << "). " << std::endl;
    this->pot += this->playerList[playerIdx].Call(bet - this->playerList[playerIdx].currentBet);
    return bet;
    
}
bool Game::HandOver()
{
    for(const Player& p: this->playerList)
    {
        if(p.GetAction() == Player::Action::FOLD)
        {
            return true;
        }
    }
    return false;
}


void Game::ResetPlayers()
{
    for(Player& p: this->playerList)
    {
        p.SetAction(Player::Action::UNDECIDED);
        p.currentBet = 0;
    }
}
void Game::AwardPot()
{
    for(Player& p : this->playerList)
    {
        if(!(p.GetAction() == Player::Action::FOLD))
        {
            p.Win(this->pot);
            this->pot = 0;
        }
    }

}
bool Game::PlayBettingRound(const std::string& name)
{
    int curIdx = this->button;
    int lastIdx = this->button == 0? 1: 0;
    
    if(name == "Pre-flop")
    {
        // action starts on the button
        lastIdx = this->button;
        curIdx = this->button == 0? 1: 0;
    }
    
    this->playerList[lastIdx].TakeAction(this->playerList[curIdx].currentBet, this->bigBlind, name);

    if(this->playerList[lastIdx].GetAction() == Player::Action::FOLD)
    {
        std::cout << this->playerList[lastIdx].GetName() << " folded. Hand over." << std::endl;
        std::cout << this->playerList[curIdx].GetName() << " wins $" << this->pot << std::endl;
        this->playerList[curIdx].Win(this->pot);
        this->pot = 0;
        return false;
    }
    // update the pot
    
    while(!Game::NextRound())
    {
        this->playerList[curIdx].TakeAction(this->playerList[lastIdx].currentBet, this->bigBlind, name);

        if(this->playerList[curIdx].GetAction() == Player::Action::FOLD)
        {
            std::cout << this->playerList[curIdx].GetName() << " folded. Hand over." << std::endl;
            std::cout << this->playerList[lastIdx].GetName() << " wins $" << this->pot << std::endl;
            this->playerList[lastIdx].Win(this->pot);
            this->pot = 0;
            return false;
        }

        // continuation condition
        std::swap(curIdx, lastIdx);
    }
    this->pot = this->playerList[0].currentBet + this->playerList[1].currentBet;
    if(this->playerList[0].GetAction() == Player::Action::FOLD || this->playerList[0].GetAction() == Player::Action::FOLD)
    {
        // give the pot to the correct person
        Game::AwardPot();
        return false;
    }
    
    std::cout << name << " over. $" << this->pot << " in the pot." << std::endl;
    this->ResetPlayers();
    return true;
}

void PrintHoleCards(const Player& p)
{
    std::cout << p.GetName() << " has " << p.GetHoleCards().first << p.GetHoleCards().second << std::endl;
}
void PrintBestHand(const Player& p, const Board& b)
{
    auto bestHand = Hand::BestHand(b, p.GetHoleCards());
    std::cout << p.GetName() << "'s best hand: " << Hand::HandRankingToEnglish(bestHand.second);
    
    for(Card c : bestHand.first)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void Game::Play()
{

    int hands = 0;
    while(hands < 10)
    {
        // while nobody has folded, keep playing the hand
        while(!Game::HandOver())
        {
            this->preFlop = true;
            std::cout << "Hand " << hands << " beginning." << std::endl;
            std::cout << this->playerList[0].GetName() << " has $" << this->playerList[0].GetStack() << " in their stack." << std::endl;
            std::cout << this->playerList[1].GetName() << " has $" << this->playerList[1].GetStack() << " in their stack." << std::endl;

            std::cout << "Hole cards being dealt..." << std::endl;
            // deal hole carrds
            this->playerList[0].SetHoleCards({this->deck.Deal(1)[0], this->deck.Deal(1)[0]});
            this->playerList[1].SetHoleCards({this->deck.Deal(1)[0], this->deck.Deal(1)[0]});

            PrintHoleCards(this->playerList[0]);
            PrintHoleCards(this->playerList[1]);
        
            // player0 is bb, player1 is sb
            this->pot += this->playerList[0].PostBlind(this->bigBlind) + this->playerList[1].PostBlind(this->smallBlind);
            

            std::cout << playerList[0].GetName() << " posted the big blind ($" << this->bigBlind << ")." << std::endl;
            std::cout << playerList[1].GetName() << " posted the small blind ($" << this->smallBlind << ")." << std::endl;

            
            /*---PRE-FLOP---*/
            bool preFlop = Game::PlayBettingRound("Pre-flop");
            if(!preFlop)
            {
                break;
            }
            this->preFlop = false;

            /*---FLOP---*/
            PrintHoleCards(this->playerList[0]);
            PrintHoleCards(this->playerList[1]);
            // create a board and put out the flop
            this->board.Flop(this->deck.Deal(3));

            std::cout << "FLOP: ";
            this->board.DisplayBoard();

            this->ResetPlayers();
            bool flop = Game::Game::PlayBettingRound("Flop");;
            if(!flop)
            {
                break;
            }
            std::cout << std::endl;
            PrintBestHand(this->playerList[0], this->board);
            std::cout << std::endl;
            PrintBestHand(this->playerList[1], this->board);
            std::cout << std::endl;


            /*---TURN---*/
            PrintHoleCards(this->playerList[0]);
            PrintHoleCards(this->playerList[1]);
            this->board.Turn(this->deck.Deal(1)[0]);
            std::cout << "TURN: board: ";
            this->board.DisplayBoard();

            bool turn = Game::PlayBettingRound("Turn");
            if(!turn)
            {
                break;
            }
            std::cout << std::endl;
            PrintBestHand(this->playerList[0], this->board);
            std::cout << std::endl;
            PrintBestHand(this->playerList[1], this->board);
            std::cout << std::endl;

            /*---RIVER---*/
            PrintHoleCards(this->playerList[0]);
            PrintHoleCards(this->playerList[1]);
            this->board.River(this->deck.Deal(1)[0]);
            std::cout << "RIVER: board: ";
            
            this->board.DisplayBoard();

            bool river = Game::PlayBettingRound("River");

            if(river)
            {
                auto player0BestHand = Hand::BestHand(this->board, playerList[0].GetHoleCards());
                auto player1BestHand = Hand::BestHand(this->board, playerList[1].GetHoleCards());

                bool compare = Hand::CompareHands(player0BestHand.first, player1BestHand.first);
                
                if(compare)
                {
                    //player1 won the hand
                    std::cout << playerList[1].GetName() << " won the pot worth $" << this->pot << std::endl;
                    std::cout << "Hand classification: " << Hand::HandRankingToEnglish(player1BestHand.second);
                    std::cout << "Five card hand: ";
                    for(Card c: player1BestHand.first)
                    {
                        std::cout << c << " ";
                    }
                    std::cout << std::endl;
                    playerList[1].Win(this->pot);
                }
                else
                {
                    // player 0 won the hand 
                    std::cout << playerList[0].GetName() << " won the pot worth $" << this->pot << std::endl;
                    std::cout << "Hand classification: " << Hand::HandRankingToEnglish(player0BestHand.second);
                    std::cout << "Five card hand: ";
                    for(Card c: player0BestHand.first)
                    {
                        std::cout << c << " ";
                    }
                    std::cout << std::endl;
                    playerList[0].Win(this->pot);
                }
            }
        }

        // reset folds
        for(Player &p: this->playerList)
        {
            p.SetAction(Player::Action::UNDECIDED);
        }
        Deck newDeck;
        newDeck.Shuffle();
        this->deck = newDeck;
        this->pot = 0;
        hands++;
    }
    
}




