#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/game.h"
#include <iostream>
#include <sstream>
Game::Game(std::vector<Player> startPlayers, double sb, double bb)
{
    this->smallBlind = sb;
    this->bigBlind = bb;

    this->maxBuyIn = 100.0 * bb;


    for(Player p: startPlayers)
    {

        this->playerList.push_back({p, true});
    }

    this->button = this->playerList.size();
    this->turn = 2; // 0 - sb, 1 - bb, 2, utg1

    this->deck.Shuffle();
    this->pot = 0.0;
}

// simulates a player's action. based on their index and the amount to call determines the actions that are possible. 
// Returns 0 for check (if possible), the bet amount for bet, and -1 for fold
int Game::Action(int playerIdx, double toCall, const std::string& street )
{
    int result = 0;

    if(toCall == 0)
    {
        // can check or raise
        std::cout << street << ", action on "  << this->playerList[playerIdx].first.GetName() << ". Options:\n1) Enter '0' to check.\n2) Enter a bet amount >= " << 2 * this->bigBlind << " to raise." << std::endl;
        std::cin >> result;

        if(result == 0.0)
        {
            // player checked, action over
            std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << "checked." << std::endl;
            return 0.0;
        }
        else if (result >= this->bigBlind * 2)
        {
            // player bet, add to pot and return bet amount
            std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << "bet $" << result  << "." << std::endl;
            this->pot += this->playerList[playerIdx].first.Bet(result);
            return 0.0;
        }
    }

    //check if player would be all in to call
    if(this->playerList[playerIdx].first.GetStack() < toCall)
    {
        // player would be all in, can only call or fold
        std::cout << street << ", action on "  << this->playerList[playerIdx].first.GetName() << ". Options:\n1) Enter '1' to call ALL IN.\n2) Enter -1 to fold." << std::endl;
        std::cin >> result;
        if(result == 1)
        {
            // player called all in
            std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << " called ALL IN." << std::endl;
            this->pot += this->playerList[playerIdx].first.Bet(toCall); // handles all in
            return toCall;
        }
        // player folded
        this->playerList[playerIdx].second = false;
        std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << "folded." << std::endl;
        return -1;
    }

    // player has no option to check, can either call, raise, or fold
    std::cout << street << ", action on "  << this->playerList[playerIdx].first.GetName() << ". Options:\n1) Enter '1' to call.\n2) Enter a bet amount >= " << 2 * toCall << " to raise.\n3) Enter -1 to fold." << std::endl;
    std::cin >> result;

    if(result == 1)
    {
        // player called
        std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << " called." << std::endl;
        this->pot += this->playerList[playerIdx].first.Bet(toCall);
        return toCall;
    }
    if(result >= 2 * toCall)
    {
        // player raised
        this->pot += this->playerList[playerIdx].first.Bet(result);
        std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << "raised $" << result  << "." << std::endl;
        return result;
    }
    // player folded
    this->playerList[playerIdx].second = false;
    std::cout << street << ". " << this->playerList[playerIdx].first.GetName() << "folded." << std::endl;
    return -1;
}

void Game::Play()
{

    int hands = 0;
    while(hands < 10)
    {
        

        // while nobody has folded, keep playing the hand
        while(this->playerList[0].second && this->playerList[1].second)
        {
            this->playerList[0].first.SetHoleCards(this->deck.Deal(2));
            this->playerList[1].first.SetHoleCards(this->deck.Deal(2));

            std::cout << playerList[0].first.GetName() << " has " << playerList[0].first.GetHoleCards()[0] << playerList[0].first.GetHoleCards()[1] << std::endl;
            std::cout << playerList[1].first.GetName() << " has " << playerList[1].first.GetHoleCards()[0] << playerList[1].first.GetHoleCards()[1] << std::endl;
        
            // player0 is bb, player1 is sb
            this->pot += playerList[0].first.Bet(this->bigBlind) + playerList[1].first.Bet(this->smallBlind);

            /*---PRE-FLOP---*/
            bool preFlag = false;
            int playerIdx = 1;
            int p1Action = this->Action(playerIdx, this->bigBlind - this->smallBlind, "Pre-flop");

            while(!preFlag)
            {
                if(playerIdx == 1)
                {
                    playerIdx = 0;
                }
                else
                {
                    playerIdx = 1;
                }
                int nextAction = this->Action(playerIdx, p1Action, "Pre-flop");
                if(nextAction == 0)
            }



        }

    }
    
}




