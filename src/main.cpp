/*
 * super litefite
 * a weird game by Josh Chandler
*/

#include <iostream>
#include <memory>

#include "shoehorn/include/shoehorn.hpp"
#include "states/include/debugstate.hpp"

int main(int argc, char const *argv[])
{
    shoe::Game *game = new shoe::Game("super litefite");
    game->setGameSize(800, 450);
    game->setPixelScale(2);

    game->pushState(std::shared_ptr<DebugState>(new DebugState(game)));

    game->run();

    return 0;
}
