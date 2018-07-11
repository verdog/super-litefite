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
    std::shared_ptr<shoe::Game> game = std::shared_ptr<shoe::Game>(new shoe::Game("super litefite"));
    game->setGameSize(800, 450);
    game->setPixelScale(2);

    std::shared_ptr<DebugState> debugState = std::shared_ptr<DebugState>(new DebugState(game));
    game->pushState(debugState);

    game->run();

    return 0;
}
