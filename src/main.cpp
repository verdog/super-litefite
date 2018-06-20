/*
 * super litefite
 * a weird game by Josh Chandler
*/

#include <iostream>

#include "shoehorn/include/shoehorn.hpp"
#include "states/include/debugstate.hpp"

int main(int argc, char const *argv[])
{
    shoe::Game *game = new shoe::Game("super litefite");
    game->setGameSize(800, 450);
    game->setPixelScale(2);

    DebugState *debugState = new DebugState(game); 
    game->pushState(debugState);

    game->run();

    return 0;
}
