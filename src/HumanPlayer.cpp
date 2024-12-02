#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(double stack, const std::string& name) : Player(stack, name) {}

void HumanPlayer::TakeAction(double bet, double minBet, const std::string& street)
{   
    int result = 0;
    if(bet - this->currentBet == 0)
    {
        // can check or raise
        std::cout << street << ", action on "  << this->GetName() << ". Options:\n1) Enter '0' to check.\n2) Enter a bet amount >= " << 2 * minBet << " to raise." << std::endl;
        std::cin >> result;

        if(result == 0)
        {
            // player checked, action over
            std::cout << street << ". " << this->GetName() << " checked." << std::endl;
            this->Check();
            return;
        }
        else if (result >= minBet)
        {
            // player bet, add to pot and return bet amount
            std::cout << street << ". " << this->GetName() << " bet $" << result  << "." << std::endl;
            this->Bet(result);
            return;
        }
    }
    //check if player would be all in to call
    if(this->GetStack() + this->currentBet < bet)
    {
        // player would be all in, can only call or fold
        std::cout << street << ", action on "  << this->GetName() << ". Options:\n1) Enter '1' to call ALL IN.\n2) Enter -1 to fold." << std::endl;
        std::cin >> result;
        if(result == 1)
        {
            // player called all in
            std::cout << street << ". " << this->GetName() << " called ALL IN." << std::endl;
            double stack = this->GetStack();
            this->Call(bet - this->currentBet); // handles all in
            return;
        }
        // player folded
        this->Fold();
        std::cout << street << ". " << this->GetName() << "folded." << std::endl;
        return;
    }

    // player has no option to check, can either call, raise, or fold
    std::cout << street << ", action on "  << this->GetName() << ". Options:\n1) Enter '1' to call $" << bet - this->currentBet << ".\n2) Enter a bet amount >= " << 2 * bet << " to raise.\n3) Enter -1 to fold." << std::endl;
    std::cin >> result;

    if(result == 1)
    {
        // player called
        std::cout << street << ". " << this->GetName() << " called." << std::endl;
        double cur = this->currentBet;
        this->Call(bet - cur);
        return;
    }
    if(result >= 2 * bet)
    {
        // player raised
        std::cout << street << ". " << this->GetName() << " raised $" << result  << "." << std::endl;
        this->Bet(result);
        return;
    }
    // player folded
    if(result == -1)
    {
        this->Fold();
        std::cout << street << ". " << this->GetName() << " folded." << std::endl;
        return;
    }
    std::cout << "Invalid input, call assumed. ($" << bet - this->currentBet << "). " << std::endl;
    this->Call(bet - this->currentBet);
}

