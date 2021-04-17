#include "sidegrid.h"

SideGrid::SideGrid()
:   grid_num(DEFAULT_GRID_NUM)
,   size_x(DEFAULT_XY)
,   size_y(DEFAULT_XY)
{
    side_grids = new int**[DEFAULT_GRID_NUM];
    for(int i = 0; i < DEFAULT_GRID_NUM; i++){
        side_grids[i] = new int*[DEFAULT_XY];
        for(int j = 0; j < DEFAULT_XY; j++)
            side_grids[i][j] = new int[DEFAULT_XY];
    }
}

SideGrid::~SideGrid()
{
    for(int i = 0; i < DEFAULT_GRID_NUM; i++){
        for(int j = 0; j < DEFAULT_XY; j++)
            delete side_grids[i][j];
    }
    for(int i = 0; i < DEFAULT_GRID_NUM; i++)
        delete side_grids[i];
    delete side_grids;
}

void SideGrid::initialize()
{
    for(int i = 0; i < grid_num; i++)
        init(i);
}


int SideGrid::getGridNum()
{
    return grid_num;
}

int SideGrid::getSizeX()
{
    return size_x;
}

int SideGrid::getSizeY()
{
    return size_y;
}

int SideGrid::getGridValue(int num, int row, int col)
{
    return side_grids[num][row][col];
}

void SideGrid::setGrid(int num, int type)
{
    init(num);
    if(type == O){
        side_grids[num][1][1] = YELLOW;
        side_grids[num][1][2] = YELLOW;
        side_grids[num][2][1] = YELLOW;
        side_grids[num][2][2] = YELLOW;
    }
    else if(type == I){
        side_grids[num][2][0] = LIGHT_BLUE;
        side_grids[num][2][1] = LIGHT_BLUE;
        side_grids[num][2][2] = LIGHT_BLUE;
        side_grids[num][2][3] = LIGHT_BLUE;
    }
    else if(type == Z)
    {
        side_grids[num][1][0] = RED;
        side_grids[num][1][1] = RED;
        side_grids[num][2][1] = RED;
        side_grids[num][2][2] = RED;
    }
    else if(type == S)
    {
        side_grids[num][2][1] = GREEN;
        side_grids[num][2][2] = GREEN;
        side_grids[num][3][0] = GREEN;
        side_grids[num][3][1] = GREEN;
    }
    else if(type == L)
    {
        side_grids[num][1][2] = ORANGE;
        side_grids[num][2][0] = ORANGE;
        side_grids[num][2][1] = ORANGE;
        side_grids[num][2][2] = ORANGE;
    }
    else if(type == J)
    {
        side_grids[num][1][0] = BLUE;
        side_grids[num][2][0] = BLUE;
        side_grids[num][2][1] = BLUE;
        side_grids[num][2][2] = BLUE;
    }
    else if(type == T)
    {
        side_grids[num][1][1] = PURPLE;
        side_grids[num][2][0] = PURPLE;
        side_grids[num][2][1] = PURPLE;
        side_grids[num][2][2] = PURPLE;
    }
}

void SideGrid::shiftGrid()
{

    for(int k = 0; k < grid_num - 1; k++) 
        for(int i = 0; i < size_y; i++)
            for(int j = 0; j < size_x; j++)
                side_grids[k][i][j] = side_grids[k + 1][i][j]; 
    init(grid_num - 1);
}

/************************ Utility Function******************************/
void SideGrid::init(int num)
{
    for(int j = 0; j < size_y; j++)
        for(int k = 0; k < size_y; k++)
            side_grids[num][j][k] = EMPTY;
}

