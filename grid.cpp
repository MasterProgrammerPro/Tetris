#include "grid.h"

Grid::Grid()
:   col_num(DEFAULT_COL)
,   row_num(DEFAULT_ROW)
{
    grid = new int*[DEFAULT_ROW];
    for(int i = 0; i < DEFAULT_ROW; i++)
        grid[i] = new int[DEFAULT_COL];
}
    
Grid::Grid(int n_row, int n_col)
:   col_num(n_row)
,   row_num(n_col)
{
    grid = new int*[n_row];
    for(int i = 0; i < n_row; i++)
        grid[i] = new int[n_col];
}

Grid::~Grid()
{
    for(int i = 0; i < row_num; i++)
        delete grid[i];
    delete grid;
}

void Grid::init_state()
{
    for(int i = 0; i < row_num; i++)
        for(int j = 0; j < col_num; j++)
            grid[i][j] = EMPTY;
}

int Grid::getGridValue(int row, int col)
{
    return grid[row][col];
}

int Grid::getGridRow()
{
    return row_num;
}

int Grid::getGridCol()
{
    return col_num;
}

void Grid::setGridValue(int row, int col, int val)
{
    grid[row][col] = val;
}


// Test fonctions 
void Grid::RandomGrid()
{
    for(int i = 0; i < row_num; i++)
    {
        for(int j = 0; j < col_num; j++)
            grid[i][j] = (std::rand() % 5);
    }
}

void Grid::DisplayGrid()
{
    for(int i = 0; i < row_num; i++)
    {
        for(int j = 0; j < col_num; j++)
            std::cout << grid[i][j];
        std::cout << std::endl;
    }
}

void Grid::putPieceOnGrid(Block *t) //!
{
    // coordiantes of t on the grid
    int starting_x = t->getCurrentX();
    int starting_y = t->getCurrentY();

    // deletes prev position of the t
    for(int i = 0; i < DEFAULT_ROW; i++)
    {
        for(int j = 0; j < DEFAULT_COL; j++)
        {
            if(this->grid[i][j] == t->getColor())
            {
                this->grid[i][j] = EMPTY;
            }
        }
    }

    // place t on the grid
    for(int j = 0; j < 4; j++)
    {    
        for(int i = 0; i < 4; i++)
        {
            if(t->getShape()[i][j] == t->getColor())
            {
                 grid[starting_y + i][starting_x + j] = t->getShape()[i][j];
            }
        }
    }
}

int Grid::lineClear()
{
    int shouldClear, counter = 0;
    for(int i = 0; i < DEFAULT_ROW; i++)
    {
        shouldClear = 1;
        for(int j = 0; j < DEFAULT_COL && shouldClear; j++)
        {
            // shouldclear = 0 if there are empty places on the line
            if(this->getGridValue(i, j) == EMPTY || this->getGridValue(i, j) < NUM_COLORS)
            {
                shouldClear = 0;
            }
        }

        if(shouldClear == 1)
        {
            counter ++;
            // shifting the grid (above the line we cleared)
            for(int k = i; k>0; k--)
            {
                for(int l = 0; l < DEFAULT_COL; l++)
                {
                    int v = getGridValue(k-1, l);
                    this->setGridValue(k, l, v);
                }
            }

            for(int j = 0; j < DEFAULT_COL; j++)
            {
                this->setGridValue(0, j, EMPTY);
            }
        }
    }
    return counter;
}