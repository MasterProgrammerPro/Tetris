#include "block.h"

/******************************************************************************/
/**************************** Block Methods ***********************************/

Block::~Block()
{
    for(int i = 0; i < 4; i++)
        delete shape[i];
    delete shape;
}

int Block::getType() 
{
    return type;
}

int Block::getCurrentX()
{
    return current_x;
}

void Block::setCurrentX(int new_x)
{
    current_x = new_x;
}

int Block::getCurrentY()
{
    return current_y;
}

void Block::setCurrentY(int new_y)
{
    current_y = new_y;
}

COLOR Block::getColor()
{
    return this->color;
}

void Block::setColor(COLOR color)
{
    this->color = color;
}

int** Block::getShape()
{
    return this->shape;
}

float Block::getCenterOfRotationX()
{
    return this->centerOfRotation_x;
}

float Block::getCenterOfRotationY()
{
    return this->centerOfRotation_y;
}

void Block::moveDown()
{
    this->current_y++;
}

void Block::goRight()
{
    this->current_x++;
}

void Block::goLeft()
{
    this->current_x--;
}

/******************************************************************************/
/******************************************************************************/

/**************************** Constructors ***********************************/
O_Block::O_Block()
{
    this->type = O;

    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.5f;
    this->centerOfRotation_y = 1.5f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(YELLOW);

    this->shape[1][1] = this->color;
    this->shape[1][2] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;

}

I_Block::I_Block()
{
    this->type = I;

    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.5f;
    this->centerOfRotation_y = 1.5f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(LIGHT_BLUE);

    this->shape[2][0] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;
    this->shape[2][3] = this->color;

}

Z_Block::Z_Block()
{
    this->type = Z;
    
    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.0f;
    this->centerOfRotation_y = 2.0f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(RED);

    this->shape[1][0] = this->color;
    this->shape[1][1] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;

}

S_Block::S_Block()
{
    this->type = S;


    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -2;
    this->centerOfRotation_x = 1.0f;
    this->centerOfRotation_y = 2.0f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(GREEN);

    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;
    this->shape[3][0] = this->color;
    this->shape[3][1] = this->color;

}


L_Block::L_Block()
{
    this->type = L;


    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.0f;
    this->centerOfRotation_y = 2.0f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(ORANGE);

    this->shape[1][2] = this->color;
    this->shape[2][0] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;

}

J_Block::J_Block()
{
    this->type = J;



    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.0f;
    this->centerOfRotation_y = 2.0f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(BLUE);

    this->shape[1][0] = this->color;
    this->shape[2][0] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;

}

T_Block::T_Block()
{
    this->type = T;


    this->current_x = (DEFAULT_COL/2)-2;
    this->current_y = -1;
    this->centerOfRotation_x = 1.0f;
    this->centerOfRotation_y = 2.0f;

    shape = new int*[4];
    for(int i = 0; i < 4; i++)
        shape[i] = new int[4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = EMPTY;
        }
    }

    setColor(PURPLE);

    this->shape[1][1] = this->color;
    this->shape[2][0] = this->color;
    this->shape[2][1] = this->color;
    this->shape[2][2] = this->color;

}

void Block::rotate()
{
    int rotated[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            rotated[i][j] = EMPTY;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(this->shape[i][j] == this->getColor())
            {
                float cx = this->centerOfRotation_x;
                float cy = this->centerOfRotation_y;
                int newR = j-cx+cy;
                int newC = cy-i+cx;
                rotated[newR][newC] = this->getColor();
            }
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->shape[i][j] = rotated[i][j];
        }
    }
    
}
