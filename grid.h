#ifndef _GRID_H_
#define _GRID_H_

#include <stdlib.h>
#include <iostream>
#include <ctime>

#define BLOCK_SIZE   30


#include "block.h"

class Grid
{
private:
    // gird
    int **grid;

    // number of rows
    int row_num;

    // number of columns
    int col_num;

public:
    //Constructors
    Grid();
    Grid(int n_row, int n_col);
    
    //Destructor
    ~Grid();

    //gives grid initial values
    void init_state(); 

    // Places block t on the grid
    void putPieceOnGrid(Block *t);


    // get number of rows/columns
    int getGridRow();
    int getGridCol();

    // changing the grid[row][col] to val
    int getGridValue(int row, int col);
    void setGridValue(int row, int col, int val);


    // sets the grid randomly (for testing purposes)
    void RandomGrid();

    // displaying grid
    void DisplayGrid();

    // check if there are any lines to clear in the grid. returns number of lines cleared
    int lineClear();
};



#endif