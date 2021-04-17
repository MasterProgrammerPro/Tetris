#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <cstdint>
#include <vector>
#include <SDL.h>
#include <string>
#include <cstdlib>
#include <queue>
#include <chrono>

//for random
#include <ctime>

#include "window.h"
#include "grid.h"
#include "sidegrid.h"
#include "block.h"
#include "blockfactory.h"

//Difficulty
#define EASY        1
#define MEDIUM      2
#define HARD        3

//Game mode
#define SINGLE  1
#define PC      2

// Project
class Window;
class Surface;
class Sprite;

class Game
{
public:
    
    // Constructor
    Game();
    Game(int mode);
    // Destructor
    virtual ~Game();
    // Methodes 
    void initialize();
    void finalize();
    void loop();

protected:
    //Graphics window
    Window* window_;

    void draw(double dt);

    void keyboard(const std::uint8_t* keys);

private:
    //graph data
    Surface* board_;
    std::vector< Sprite* > sprites_;

    //Game data
    double difficulty;
    int total_lines_cleared;
    int mode;
    unsigned score;

    BlockFactory *factory;

    // Single Player    
    Grid *grid;
    Block *current_block;
    std::queue<Block *> next_blocks;
    SideGrid *side_grid;

    //PC mode variables (not yet implemented)
    Grid *grid_pc;
    Block *current_block_pc;
    std::queue<Block *> next_blocks_pc;
    SideGrid *side_grid_pc;

    // Utility Functions
    //void DisplayDifficulty();
    void drawBackground();
    void drawGameGrid(int start_x,int start_y);
    void drawSideGrid(int num, int start_x,int start_y);
    void drawGameGridPC(int start_x,int start_y);
    void drawSideGridPC(int num, int start_x,int start_y);

    // Movement utility functions
    
    // test to see if the current block drop
    int canDrop();

    // test to see if we can rotate the current block
    int canRotate();

    // rotate the current block
    void rotate();

    // test for horizontal movements
    int canGoLeft();
    int canGoRight();

    // locks the current block in place
    void lock();

    // drops the current block all the way down
    void hardDrop();

    // test to see if we can place the current block on the grid (test to see if the game ended)
    int canPut();
};



#endif