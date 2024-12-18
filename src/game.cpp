#include "game.h"
#include <iostream>
#include <sstream>

nlohmann::json Game::GetGameState() const
{
    nlohmann::json state;
    
    // Example: Add players and their chip counts
    state["players"] = nlohmann::json::array();
    for (const auto& player : this->playerList) {
        std::string handString = player->GetHoleCards().first.ToString() + player->GetHoleCards().second.ToString();
        std::string active = player->GetAction() == Player::Action::FOLD ? "unactive": "active";
        state["players"].push_back({
            {"name", player->GetName()},
            {"chips", player->GetStack()},
            {"is_active", active},
            {"hand", handString} 
        });
    }

    state["pot"] = this->pot;

    std::string boardString = "";
    for(const Card& c: this->board.GetBoard())
    {
        boardString += c.ToString();
    }
    state["board"] = boardString;

    // add state for bet and/or who's turn it is

    return state;
}
Game::Game(std::vector<HumanPlayer> humans, std::vector<AIPlayer> cpu,  double sb, double bb)
{
    this->smallBlind = sb;
    this->bigBlind = bb;

    this->maxBuyIn = 100.0 * bb;


    for(auto p: humans)
    {
        this->playerList.push_back(std::make_shared<HumanPlayer>(p));
    }

    for(auto c : cpu)
    {
        this->playerList.push_back(std::make_shared<AIPlayer>(c));
    }

    this->button = this->playerList.size() - 1;
    this->turn = this->button; 

    this->deck.Shuffle();
    this->pot = 0.0;
}
bool Game::NextRound() 
{
    if(this->playerList[0]->currentBet != this->playerList[1]->currentBet)
    {
        return false;
    }
    // ways we can progress:
    // 1) check check
    // 2) bet call
    if(this->playerList[0]->GetAction() == Player::Action::CHECK && this->playerList[1]->GetAction() == Player::Action::CHECK)
    {
        return true;
    }
    if(this->playerList[0]->GetAction() == Player::Action::BET && this->playerList[1]->GetAction() == Player::Action::CALL)
    {
        return true;
    }
    if(this->playerList[0]->GetAction() == Player::Action::CALL && this->playerList[1]->GetAction() == Player::Action::BET)
    {
        return true;
    }

    // Continue pre-flop betting as one player has raised
    return false;
}

bool Game::HandOver()
{
    for(const auto p: this->playerList)
    {
        if(p->GetAction() == Player::Action::FOLD)
        {
            return true;
        }
    }
    return false;
}


void Game::ResetPlayers()
{
    for(const auto p: this->playerList)
    {
        p->SetAction(Player::Action::UNDECIDED);
        p->currentBet = 0;
    }
}

void Game::Reset()
{
    Deck newDeck;
    this->deck = newDeck;

    this->deck.Shuffle();

    this->pot = 0.0;

    this->ResetPlayers();

    // Move the button to the next player
    this->button = (button + 1) % playerList.size();

    this->SetPositions();
}
void Game::AwardPot()
{
    for(const auto p : this->playerList)
    {
        if(!(p->GetAction() == Player::Action::FOLD))
        {
            p->Win(this->pot);
            this->pot = 0;
        }
    }

}
bool Game::PlayBettingRound(const std::string& name)
{
    int curIdx = this->button == 1? 1: 0;
    int lastIdx = (curIdx == 0)? 1: 0;

    std::cout << playerList[0]->GetName() << ". Current bet: $" << playerList[0]->currentBet << std::endl;
    std::cout << playerList[1]->GetName() << ". Current bet: $" << playerList[1]->currentBet << std::endl;
    bool preflop = false;
    if(name == "Pre-flop")
    {
        // action starts on the button
        std::swap(curIdx, lastIdx);
        preflop = true;
    }
    

    this->playerList[lastIdx]->TakeAction(this->playerList[curIdx]->currentBet, this->bigBlind, name);

    if(this->playerList[lastIdx]->GetAction() == Player::Action::FOLD)
    {
        std::cout << this->playerList[lastIdx]->GetName() << " folded. Hand over." << std::endl;
        std::cout << this->playerList[curIdx]->GetName() << " wins $" << this->pot << std::endl;
        this->playerList[curIdx]->Win(this->pot);
        this->pot = 0;
        return false;
    }
    std::cout << playerList[0]->GetName() << ". Current bet: $" << playerList[0]->currentBet << std::endl;
    std::cout << playerList[1]->GetName() << ". Current bet: $" << playerList[1]->currentBet << std::endl;
    while(!Game::NextRound())
    {
        this->playerList[curIdx]->TakeAction(this->playerList[lastIdx]->currentBet, this->bigBlind, name);

        if(this->playerList[curIdx]->GetAction() == Player::Action::FOLD)
        {
            std::cout << this->playerList[curIdx]->GetName() << " folded. Hand over." << std::endl;
            std::cout << this->playerList[lastIdx]->GetName() << " wins $" << this->pot << std::endl;
            this->playerList[lastIdx]->Win(this->pot);
            this->pot = 0;
            return false;
        }
        std::cout << playerList[0]->GetName() << ". Current bet: $" << playerList[0]->currentBet << std::endl;
        std::cout << playerList[1]->GetName() << ". Current bet: $" << playerList[1]->currentBet << std::endl;
        // continuation condition
        std::swap(curIdx, lastIdx);
    }
    if(preflop)
    {
        this->pot = this->playerList[0]->currentBet + this->playerList[1]->currentBet;
    }
    else
    {
        this->pot += this->playerList[0]->currentBet + this->playerList[1]->currentBet;
    }
    
    if(this->playerList[0]->GetAction() == Player::Action::FOLD || this->playerList[0]->GetAction() == Player::Action::FOLD)
    {
        // give the pot to the correct person
        Game::AwardPot();
        return false;
    }
    
    std::cout << name << " over. $" << this->pot << " in the pot." << std::endl;
    this->ResetPlayers();
    return true;
}

void PrintHoleCards(const std::shared_ptr<Player> p)
{
    std::cout << p->GetName() << " has " << p->GetHoleCards().first << p->GetHoleCards().second << std::endl;
}
void PrintBestHand(const std::shared_ptr<Player> p, const Board& b)
{
    auto bestHand = Hand::BestHand(b, p->GetHoleCards());
    std::cout << p->GetName() << "'s best hand: " << Hand::HandRankingToEnglish(bestHand.second) << ": ";
    
    for(Card c : bestHand.first)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
void Game::SetPositions()
{
    if(this->button == 0)
    {
        this->playerList[0]->SetPosition(Player::Position::IP);
        this->playerList[1]->SetPosition(Player::Position::OOP);
        return;
    }
    this->playerList[0]->SetPosition(Player::Position::OOP);
    this->playerList[1]->SetPosition(Player::Position::IP);
}

void Game::Play()
{

    int hands = 1;
    this->SetPositions();
    while(hands <= 10)
    {
        
        // while nobody has folded, keep playing the hand
        while(!Game::HandOver())
        {
            this->preFlop = true;
            std::cout << "Hand " << hands << " beginning." << std::endl;
            
            std::cout << this->playerList[0]->GetName() << " has $" << this->playerList[0]->GetStack() << " in their stack." << std::endl;
            std::cout << this->playerList[1]->GetName() << " has $" << this->playerList[1]->GetStack() << " in their stack." << std::endl;

            std::cout << "Hole cards being dealt..." << std::endl;
            
            // deal hole carrds
            this->playerList[0]->SetHoleCards({this->deck.Deal(1)[0], this->deck.Deal(1)[0]});
            this->playerList[1]->SetHoleCards({this->deck.Deal(1)[0], this->deck.Deal(1)[0]});


            // state positions
            std::cout << this->playerList[0]->GetName() << " is " << (this->playerList[0]->GetPosition() == Player::Position::IP ? "in position.": "out of position.") << std::endl;
            std::cout << this->playerList[1]->GetName() << " is " << (this->playerList[1]->GetPosition() == Player::Position::IP ? "in position.": "out of position.") << std::endl;

            PrintHoleCards(this->playerList[0]);
            PrintHoleCards(this->playerList[1]);
        
            size_t bbIdx = this->button == 1? 0: 1;
            this->pot += this->playerList[bbIdx]->PostBlind(this->bigBlind) + this->playerList[this->button]->PostBlind(this->smallBlind);
            
            
            std::cout << playerList[0]->GetName() << " posted the big blind ($" << this->bigBlind << ")." << std::endl;
            std::cout << playerList[1]->GetName() << " posted the small blind ($" << this->smallBlind << ")." << std::endl;

            
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
                auto player0BestHand = Hand::BestHand(this->board, playerList[0]->GetHoleCards());
                auto player1BestHand = Hand::BestHand(this->board, playerList[1]->GetHoleCards());

                bool compare = Hand::CompareHands(player0BestHand.first, player1BestHand.first);
                
                if(compare)
                {
                    //player1 won the hand
                    std::cout << playerList[1]->GetName() << " won the pot worth $" << this->pot << std::endl;
                    std::cout << "Hand classification: " << Hand::HandRankingToEnglish(player1BestHand.second);
                    std::cout << "Five card hand: ";
                    for(Card c: player1BestHand.first)
                    {
                        std::cout << c << " ";
                    }
                    std::cout << std::endl;
                    playerList[1]->Win(this->pot);
                }
                else
                {
                    // player 0 won the hand 
                    std::cout << playerList[0]->GetName() << " won the pot worth $" << this->pot << std::endl;
                    std::cout << "Hand classification: " << Hand::HandRankingToEnglish(player0BestHand.second);
                    std::cout << "Five card hand: ";
                    for(Card c: player0BestHand.first)
                    {
                        std::cout << c << " ";
                    }
                    std::cout << std::endl;
                    playerList[0]->Win(this->pot);
                }
            }
        }
        this->Reset();
        hands++;
    }
    
}




