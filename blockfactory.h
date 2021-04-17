#ifndef _BLOCKFACTORY_H_
#define _BLOCKFACTORY_H_

#include "block.h"

class BlockFactory
{
public:
    Block* generateRandBlock();

private:
    int randomPiece();
};




#endif