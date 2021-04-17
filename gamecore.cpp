#include "gamecore.h"

Core::GameCore::GameCore()
{    
}

bool Core::GameCore::initialize()
{
	//random number gen
	std::srand(time(nullptr));

    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		return false;
	}

    return true;
}

bool Core::GameCore::finalize()
{
    // Quit graph library
	SDL_Quit();

    return true;
} 
