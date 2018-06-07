/*
 * super litefite
 * a weird game by Josh Chandler
*/

#include <iostream>

#include "shoehorn/include/shoehorn.hpp"

int main(int argc, char const *argv[])
{
    shoe::Game game("super litefite");
    game.setWindowSize(1600, 900);

    shoe::GameState myState(&game);
    game.pushState(&myState);

    game.run();

    return 0;
}
