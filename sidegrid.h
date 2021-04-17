#ifndef _SIDEGRID_H_
#define _SIDEGRID_H_

#include "grid.h"
#include "block.h"

#include <vector>
#include <iostream>

#define DEFAULT_GRID_NUM    3
#define DEFAULT_XY          4

//This class will represent small screens to show next blocks
class SideGrid
{
public:
    //Constructor
    SideGrid();
    //Destructor
    ~SideGrid();

    // sets initial values
    void initialize();

    // get-set methodes
    int getGridNum();
    int getSizeX();
    int getSizeY();
    int getGridValue(int num, int row, int col);
    void setGrid(int num, int type);
    
    // shifts the grid
    void shiftGrid();


private:
    int ***side_grids;
    int grid_num;
    int size_x;
    int size_y;

    // Utility methodes

    void init(int num);

};

#endif
