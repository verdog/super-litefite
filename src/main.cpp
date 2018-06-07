/*
 * super litefite
 * a weird game by Josh Chandler
*/

#include <iostream>

#include "shoehorn/include/shoehorn.hpp"

int main(int argc, char const *argv[])
{
    shoe::Game *game = new shoe::Game("super litefite");
    game->setWindowSize(1600, 900);

    shoe::GameState *myState = new shoe::GameState(game);
    game->pushState(myState);

    game->run();

    return 0;
}
