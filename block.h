#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <stdlib.h>
#include <iostream>
#include <ctime>

//#include "grid.h"

//Rotations
#define ROTATION_1  1
#define ROTATION_2  2
#define ROTATION_3  3
#define ROTATION_4  4

// Default Size vals
#define DEFAULT_ROW     20
#define DEFAULT_COL     10

#define COLOR int
#define NUM_COLORS  10

#define EMPTY       0
#define BACKGROUND  9

#define RED         1
#define BLUE        2
#define GREEN       3
#define YELLOW      4
#define WHITE       5
#define PURPLE      6
#define ORANGE      7
#define LIGHT_BLUE  8

// Block Types

#define O           1
#define I           2
#define Z           3
#define S           4
#define L           5
#define J           6
#define T           7

class Block
{
public:
    
    ~Block();

    int getType();
    
    int getCurrentX();
    void setCurrentX(int new_x);

    int getCurrentY();
    void setCurrentY(int new_y);

    int getColor();
    void setColor(COLOR color);

    // returns the shape
    int **getShape();

    // get- set of center of rotations
    float getCenterOfRotationX();
    float getCenterOfRotationY();

    // decrement current_y
    void moveDown();

    // rotate the shape around his center of rotation
    void rotate();

    // increment/decrement current_x
    void goRight();
    void goLeft();

protected:
    // shape of the block (O, I, Z, S, J, L, T)
    int type;

    // current coordinates of the block
    int current_x;
    int current_y;
    
    // color of the block
    int color;

    // shape of the block (4x4 array) 
    int **shape;

    // center of rotation of the block
    float centerOfRotation_x; //!
    float centerOfRotation_y; //!

};

class O_Block : public Block
{
public:
    O_Block();
};

class I_Block : public Block
{
public:
    I_Block();
};

class Z_Block : public Block
{
public:
    Z_Block();
};

class S_Block : public Block
{
public:
    S_Block();
};

class L_Block : public Block
{
public:
    L_Block();
};

class J_Block : public Block
{
public:
    J_Block();
};

class T_Block : public Block
{
public:
    T_Block();
};


#endif