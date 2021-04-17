#include "blockfactory.h"

Block* BlockFactory::generateRandBlock()
{
	Block * new_block;
	int r_val;
	r_val = this->randomPiece();
	if(r_val == O) new_block = new O_Block();
	else if(r_val == I) new_block = new I_Block();
	else if(r_val == Z) new_block = new Z_Block();
	else if(r_val == S) new_block = new S_Block();
	else if(r_val == L) new_block = new L_Block();
	else if(r_val == J) new_block = new J_Block();
	else if(r_val == T) new_block = new T_Block();

	// To see which block we are creating
	/*
	char blocknames[7] = {'O','I','Z','S','L','J','T'};
	std::cout << "block type: " << blocknames[r_val - 1] << std::endl; 
	*/

	return new_block;
}

int BlockFactory::randomPiece()
{
	int r, min = 1, max = 7;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

	do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}