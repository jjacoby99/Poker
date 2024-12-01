#include <iostream>
#include "sim.h"
#include "game.h"
#include "HumanPlayer.h"
#include "/Users/joshjacoby/Desktop/Code/Poker/Poker/include/httplib.h"
#include "/Users/joshjacoby/Desktop/Code/Libraries/json-develop/include/nlohmann/json.hpp"

int main() {

    httplib::Server svr;

    int players = 2;
    int bb = 2;
    int sb = 1;

    HumanPlayer hero(200.0, "Hero");
    HumanPlayer villain(200.0, "Villain");

    Game game({hero,villain}, {}, sb, bb);

    game.Play();

    return 0;
}