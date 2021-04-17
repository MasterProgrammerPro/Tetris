// Libraries
#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "game.h"
#include "grid.h"
#include "gamecore.h"



int main(int argc, char**argv)
{
    // Initialize graphics library
    int game_mode;

    if(argc == 2)
    {
        if(!strcmp(argv[1], "single")) {
            std::cout << "launching game - single player " << std::endl;
            game_mode = SINGLE;
        }
        else if(!strcmp(argv[1], "pc")) {
            std::cout << "launching game - against pc" << std::endl;
            game_mode = PC;
        }
        else {
            std::cout << "To play single player: ./TETRIS single" << std::endl;
            std::cout << "To play against pc: ./TETRIS pc" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        std::cout << "To play single player: ./TETRIS single" << std::endl;
        std::cout << "To play against pc: ./TETRIS pc" << std::endl;
        exit(EXIT_FAILURE);
    }

    // initializing SDL library
    if (!Core::GameCore::initialize()) {
        std::cout << "game cannot be initialized" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << argc << std::endl;

    Game* game = new Game(game_mode); 

    // initialization of the game
    game->initialize();
    // game loop    
    game->loop();
    // finilize game
    game->finalize();
	delete game;
	game = nullptr;

    Core::GameCore::finalize();


    return 0;
}