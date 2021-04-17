#include "game.h"

//Constructor
Game::Game()
:	window_( nullptr )
,	board_( nullptr )
,	sprites_()    //new private values will be added after this point 
,	difficulty( MEDIUM )
, 	grid_pc(nullptr)
,	current_block(nullptr)
{
	grid = new Grid();
	side_grid = new SideGrid();
}

//Constructor
Game::Game(int mode)
:	window_( nullptr )
,	board_( nullptr )
,	sprites_()    //new private values will be added after this point 
,	difficulty( MEDIUM )
,	current_block(nullptr)
{
	this->mode = mode;

	if (mode == SINGLE) {
		grid = new Grid();
		side_grid = new SideGrid();

	}
	else {
		grid = new Grid();
		side_grid = new SideGrid();
	
		grid_pc = new Grid();
		side_grid_pc = new SideGrid();

	}
}

// Deconstructor
Game::~Game()
{
	for ( auto sprite : sprites_ )
	{
		delete sprite;
		sprite = nullptr;
	}
	sprites_.clear();
	
	delete board_;
	board_ = nullptr;

	delete window_;
	window_ = nullptr;
}

void Game::initialize()
{
	std::cout << "initializing game" << std::endl;
	//random number gen
	std::srand(std::time(nullptr));

	difficulty = 1; // in secs, gets hard when it gets low
	total_lines_cleared = 0; // number of total line cleared
	score = 0; // game score

	if(mode == SINGLE)
		window_ = new Window( "TETRIS", (DEFAULT_COL + 6 ) * BLOCK_SIZE, (DEFAULT_ROW ) * BLOCK_SIZE);
	else 
		window_ = new Window( "TETRIS", (DEFAULT_COL + 6 ) * BLOCK_SIZE * 2, (DEFAULT_ROW ) * BLOCK_SIZE);
	window_->initialize();

	// Initializing Empty Grid
	// If mode is "against pc" then init pc grid
	grid->init_state();
	if(mode == PC) { // If mode is "against pc" then init 
		grid_pc->init_state();
	}

	//Initialize Empty Side Grid
	// If mode is "against pc" then init pc side grid
	side_grid->initialize();
	if(mode == PC) {
		side_grid_pc->initialize();
	}
    //Textures
	board_ = new Surface();
	const std::string image = "./Blocks.bmp";
	board_->load( image.c_str() );

	//Factory for creating new blocks
	factory = new BlockFactory;


	// Creating future blocks
	while( next_blocks.size() < side_grid->getGridNum())
	{
		Block * new_next_block = factory->generateRandBlock();
		next_blocks.push(new_next_block);

		side_grid->shiftGrid();
		side_grid->setGrid(side_grid->getGridNum() - 1, new_next_block->getType());		
	}
	// Taking current block from next block queue
	if( current_block == nullptr)
	{
		current_block = next_blocks.front();
		next_blocks.pop();
	}

	// - EMPTY tile
	sprites_.emplace_back( new Sprite( board_, 0, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - RED
	sprites_.emplace_back( new Sprite( board_, 60, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - BLUE
	sprites_.emplace_back( new Sprite( board_, 120, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - GREEN
	sprites_.emplace_back( new Sprite( board_, 90, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - YELLOW
	sprites_.emplace_back( new Sprite( board_, 30, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - WHITE
	sprites_.emplace_back( new Sprite( board_, 150, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - PURPLE
	sprites_.emplace_back( new Sprite( board_, 180, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - ORANGE
	sprites_.emplace_back( new Sprite( board_, 210, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - LIGHT_BLUE
	sprites_.emplace_back( new Sprite( board_, 240, 0, BLOCK_SIZE, BLOCK_SIZE));
	// - BACKGROUND
	sprites_.emplace_back( new Sprite( board_, 270, 0, BLOCK_SIZE, BLOCK_SIZE));


}

void Game::keyboard(const std::uint8_t* keys)
{
	// Down Arrow Key (Soft Drop)
    if (keys[SDL_SCANCODE_DOWN])
	{
		if(this->canDrop())
		{
			this->current_block->moveDown();
		}
		return;
	}

	// Up Arrow Key (Rotate)
	if (keys[SDL_SCANCODE_UP])
	{
		this->rotate();
		return;
	}

	// Right Arrow Key (Move block to the right)
	if(keys[SDL_SCANCODE_RIGHT])
	{
		if(this->canGoRight())
		{
			this->current_block->goRight();
		}
		return;
	}

	// Left Arrow Key (Move block to the left)
	if(keys[SDL_SCANCODE_LEFT])
	{
		if(this->canGoLeft())
		{
			this->current_block->goLeft();
		}
		return;
	}

	// Space button (Hard Drop)
	if(keys[SDL_SCANCODE_SPACE]) //Not Always Stable
	{
		this->hardDrop();
		this->lock();
		return;
	}
}

void Game::finalize()
{
	std::cout << "finalizing game" <<std::endl;

	std::cout << "score:" << this->score <<std::endl;

	delete grid;
	delete side_grid;
	delete factory;

	if(mode == PC){
		delete grid_pc;
		delete side_grid_pc;
	}

}

void Game::draw(double dt)
{
	// Drawing background
	drawBackground();

	if(mode == SINGLE){
		// Drawing player grid
		drawGameGrid(0, 0);
		for(int i = 0, n = side_grid->getGridNum(); i < n; i++)
			drawSideGrid(i, 1 + (i * 5), 11);
	}
	else {
		// Drawing player grid
		drawGameGrid(0, 0);
		for(int i = 0, n = side_grid->getGridNum(); i < n; i++)
			drawSideGrid(i, 1 + (i * 5), 11);

		drawGameGridPC(0, 16);
		for(int i = 0, n = side_grid_pc->getGridNum(); i < n; i++)
			drawSideGridPC(i, 1 + (i * 5), 11 + 16);
	}


}

void Game::loop()
{
	// to keep track of time
	Uint64 now = SDL_GetPerformanceCounter(); // timers
	Uint64 prev = now;
	
	// keeps track of for how long current block stayed put
	double dropTime = 0;
	
	// keeps track of the difficulty
	double current_difficulty = difficulty;
	
	// keeps track of for how long current block touched the ground 
	double contactTime = 0;

	// becomes true when game ends
    bool quit = false;

	// number of lines cleared in this loop
	int lineClearedNow = 0;
	

	// game loop
	while ( !quit )
	{
		// Event management
		SDL_Event event;
		while ( !quit && SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
				case SDL_KEYDOWN:
				{
					// Keyboard management
					const Uint8* state = SDL_GetKeyboardState(NULL);
					keyboard( state );
					quit |= state[ SDL_SCANCODE_ESCAPE ];
					break;
				}
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
		

    	// Rendering stage
		prev = now;
		now = SDL_GetPerformanceCounter();
		double delta_t = (double)((now - prev) / (double)SDL_GetPerformanceFrequency());
		draw( delta_t );

		// test if we need to move the block down
		if(dropTime > current_difficulty)
		{
			if(this->canDrop())
			{
				this->current_block->moveDown();
				dropTime = 0;
			}
			else
			{
				contactTime += delta_t;
			}
		}
		else
		{
			dropTime += delta_t;
		}

		// current block can touch the ground for 0.3 second, after it gets locked in place
		if(contactTime > 0.3f)
		{
			this->lock();
			dropTime = 0;
			contactTime = 0;
			// after we locked the previous block, tests if we can place the next block on the grid
			if(!this->canPut())
			{
				quit = true;
			}
		}

        // Update window (refresh)
		lineClearedNow = grid->lineClear();
		total_lines_cleared += lineClearedNow;
		this->score += 40*lineClearedNow;
		if(current_difficulty > 0.5)
			current_difficulty = difficulty - 0.02 * total_lines_cleared;

		// update the positionning of current block
		grid->putPieceOnGrid(this->current_block);

		// updates the window
		window_->update();
    }
}

/********************* Utility Functions ******************************/
/**********************************************************************/
void Game::drawBackground()
{
	for ( int i = 0, h = window_->height(); i <= h; i += sprites_[ 7 ]->height() )
	{
		for ( int j = 0, w = window_->width(); j <= w; j += sprites_[ 7 ]->width() )
		{
			window_->draw( *sprites_[ 9 ], j, i );
		}
	}
}


// Drawing players grid
void Game::drawGameGrid(int start_x,int start_y)
{
	for ( int i = 0, h = grid->getGridRow(); i < h; i += 1 )
	{
		for ( int j = 0, w = grid->getGridCol(); j < w; j += 1 )
		{
			if (grid->getGridValue(i,j)%NUM_COLORS == EMPTY)
				window_->draw( *sprites_[ 0 ] , (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE);
			else if (grid->getGridValue(i,j)%NUM_COLORS == RED)
				window_->draw( *sprites_[ 1 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == BLUE)
				window_->draw( *sprites_[ 2 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == GREEN)
				window_->draw( *sprites_[ 3 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == YELLOW)
				window_->draw( *sprites_[ 4 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == WHITE)
				window_->draw( *sprites_[ 5 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == PURPLE)
				window_->draw( *sprites_[ 6 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == ORANGE)
				window_->draw( *sprites_[ 7 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid->getGridValue(i,j)%NUM_COLORS == LIGHT_BLUE)
				window_->draw( *sprites_[ 8 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
		}
	}
}

// Drawing players sidegrid
void Game::drawSideGrid(int num, int start_x,int start_y)
{
	for ( int i = 0, h = side_grid->getSizeY(); i < h; i += 1 )
	{
		for ( int j = 0, w = side_grid->getSizeX(); j < w; j += 1 )
		{
			if (side_grid->getGridValue(num, i , j) == EMPTY)
				window_->draw( *sprites_[ 0 ] , (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE);
			else if (side_grid->getGridValue(num, i,j) == RED)
				window_->draw( *sprites_[ 1 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == BLUE)
				window_->draw( *sprites_[ 2 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == GREEN)
				window_->draw( *sprites_[ 3 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == YELLOW)
				window_->draw( *sprites_[ 4 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == WHITE)
				window_->draw( *sprites_[ 5 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == PURPLE)
				window_->draw( *sprites_[ 6 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == ORANGE)
				window_->draw( *sprites_[ 7 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid->getGridValue(num, i,j) == LIGHT_BLUE)
				window_->draw( *sprites_[ 8 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
		}
	}
}

// Drawing PC grid
void Game::drawGameGridPC(int start_x,int start_y)
{
	for ( int i = 0, h = grid_pc->getGridRow(); i < h; i += 1 )
	{
		for ( int j = 0, w = grid_pc->getGridCol(); j < w; j += 1 )
		{
			if (grid_pc->getGridValue(i,j)%NUM_COLORS == EMPTY)
				window_->draw( *sprites_[ 0 ] , (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE);
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == RED)
				window_->draw( *sprites_[ 1 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == BLUE)
				window_->draw( *sprites_[ 2 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == GREEN)
				window_->draw( *sprites_[ 3 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == YELLOW)
				window_->draw( *sprites_[ 4 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == WHITE)
				window_->draw( *sprites_[ 5 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == PURPLE)
				window_->draw( *sprites_[ 6 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == ORANGE)
				window_->draw( *sprites_[ 7 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (grid_pc->getGridValue(i,j)%NUM_COLORS == LIGHT_BLUE)
				window_->draw( *sprites_[ 8 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
		}
	}
}

// Drawing PC side grid
void Game::drawSideGridPC(int num, int start_x,int start_y)
{
	for ( int i = 0, h = side_grid_pc->getSizeY(); i < h; i += 1 )
	{
		for ( int j = 0, w = side_grid_pc->getSizeX(); j < w; j += 1 )
		{
			if (side_grid_pc->getGridValue(num, i , j) == EMPTY)
				window_->draw( *sprites_[ 0 ] , (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE);
			else if (side_grid_pc->getGridValue(num, i,j) == RED)
				window_->draw( *sprites_[ 1 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == BLUE)
				window_->draw( *sprites_[ 2 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == GREEN)
				window_->draw( *sprites_[ 3 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == YELLOW)
				window_->draw( *sprites_[ 4 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == WHITE)
				window_->draw( *sprites_[ 5 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == PURPLE)
				window_->draw( *sprites_[ 6 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == ORANGE)
				window_->draw( *sprites_[ 7 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
			else if (side_grid_pc->getGridValue(num, i,j) == LIGHT_BLUE)
				window_->draw( *sprites_[ 8 ], (j + start_y) * BLOCK_SIZE, (i + start_x) * BLOCK_SIZE );
		}
	}
}

void Game::rotate()
{
	// roatte only if we can actually rotate the block
	if(this->canRotate())
	{
		this->current_block->rotate();
	}
}


// rotates the block and looks if there are anything collading with the rotated block (or test if its in bounds)
int Game::canRotate()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] != EMPTY)
			{
				float cx = this->current_block->getCenterOfRotationX();
                float cy = this->current_block->getCenterOfRotationY();
				int c = this->current_block->getCurrentX();
				int r = this->current_block->getCurrentY();
                int newR = j-cx+cy;
                int newC = cy-i+cx;
				if(newR+r >= DEFAULT_ROW || newC+c < 0 || newC+c >= DEFAULT_COL || newR+r < 0) // NEED MORE TESTS
				{
					return 0;
				}
				if(this->grid->getGridValue(r+newR+1, c+newC) != EMPTY && this->grid->getGridValue(r+newR+1, c+newC) != this->current_block->getColor())
				{
					return 0;
				}
			}
		}
	}
	return 1;
}


// test if we can move the block downwards
int Game::canDrop()
{
	int c = this->current_block->getCurrentX();
	int r = this->current_block->getCurrentY();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				// test to see if our block is on the ground level
				if(r + i == DEFAULT_ROW -1)
				{
					return 0;
				}
				// test to see if there are any other blocks blocking our way
				if(this->grid->getGridValue(r+i+1, c+j) != EMPTY && this->grid->getGridValue(r+i+1, c+j) != this->current_block->getColor())
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int Game::canGoRight()
{
	int c = this->current_block->getCurrentX();
	int r = this->current_block->getCurrentY();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				// test to see if we are on edge of the grid
				if(c + j == DEFAULT_COL -1)
				{
					return 0;
				}
				// test to see if there are any other blocks blocking our way
				if(this->grid->getGridValue(r+i, c+j+1) != EMPTY && this->grid->getGridValue(r+i, c+j+1) != this->current_block->getColor())
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int Game::canGoLeft()
{
	int c = this->current_block->getCurrentX();
	int r = this->current_block->getCurrentY();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				// test to see if we are on edge of the grid
				if(c + j == 0)
				{
					return 0;
				}

				// test to see if there are any other blocks blocking our way
				if(this->grid->getGridValue(r+i, c+j-1) != EMPTY && this->grid->getGridValue(r+i, c+j-1) != this->current_block->getColor())
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

// writes the current block semi-permanantly on the grid, destructs current block
void Game::lock()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				int r = this->current_block->getCurrentY();
				int c = this->current_block->getCurrentX();
				this->grid->setGridValue(r+i, c+j, this->current_block->getColor()+NUM_COLORS);
			}
		}
	}
	// call destructor
	delete this->current_block;
	this->current_block = next_blocks.front();
	this->next_blocks.pop();

	Block * new_next_block = factory->generateRandBlock();
	next_blocks.push(new_next_block);

	side_grid->shiftGrid();
	side_grid->setGrid(side_grid->getGridNum() - 1, new_next_block->getType());	
}

void Game::hardDrop()
{
	int r = this->current_block->getCurrentY();
	int c = this->current_block->getCurrentX();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			// erase the blocks from the grid
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				this->grid->setGridValue(r+i, c+j, EMPTY);
			}
		}
	}

	// drops the block until we no longer can
	while(this->canDrop())
	{
		this->current_block->moveDown();
	}
}

// test to see if we can put the current block on the grid, game end when we cant
int Game::canPut()
{
	int r = this->current_block->getCurrentY();
	int c = this->current_block->getCurrentX();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(this->current_block->getShape()[i][j] == this->current_block->getColor())
			{
				if(this->grid->getGridValue(r+i, c+j) != EMPTY)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}