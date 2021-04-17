#ifndef _GAME_CORE_H_
#define _GAME_CORE_H_

#include <SDL.h>
#include <stdlib.h>
#include <iostream>


namespace Core
{

class GameCore
{
public:
    static bool initialize();
    
    static bool finalize();


protected:

private:
    GameCore(); 
    //With private constructor, we cannot create an instance of this class



};

}

#endif