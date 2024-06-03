// Pac-Man.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init game engine
    Game game;
    game.run();

    return 0;
}


