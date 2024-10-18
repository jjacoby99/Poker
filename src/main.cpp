#include <iostream>
#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/sim.h"

int main() {
    Card As(Card::Suit::SPADES, Card::FaceValue::ACE);
    Card Ac(Card::Suit::CLUBS, Card::FaceValue::ACE);

    std::pair<Card, Card> h1 = {As, Ac};

    Card Kh(Card::Suit::HEARTS, Card::FaceValue::KING);
    Card Kd(Card::Suit::DIAMONDS, Card::FaceValue::KING);

    std::pair<Card, Card> h2 = {Kh, Kd};


    Sim s1(h1, h2);

    double numSims = 100000;

    /*
    // Start time
    auto start = std::chrono::high_resolution_clock::now();

    // Run your simulation
    runSimulation();

    // End time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    std::chrono::duration<double> duration = end - start;

    // Output the duration in seconds
    std::cout << "Simulation runtime: " << duration.count() << " seconds" << std::endl;
    */
    
    auto start = std::chrono::high_resolution_clock::now();
    double h1Equity = s1.CalculateEquity(numSims);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Aces vs Kings equity preflop: " << h1Equity << ". Ran " << numSims << " simulations." << std::endl;
    std::cout << "Pruning simulation runtime: " << duration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    h1Equity = s1.CalculateEquityNoPruning(numSims);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Aces vs Kings equity preflop: " << h1Equity << ". Ran " << numSims << " simulations." << std::endl;
    std::cout << "No Pruning simulation runtime: " << duration.count() << " seconds" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    h1Equity = s1.CalculateEquity(numSims, 8);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Aces vs Kings equity preflop: " << h1Equity << ". Ran " << numSims << " simulations." << std::endl;
    std::cout << "Multithreading simulation runtime: " << duration.count() << " seconds" << std::endl;

    return 0;
}