#include "surface.h"

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// Graphics library
#include <SDL.h>

// Project
#include "sprite.h"



/******************************************************************************
 * Default constructor
 ******************************************************************************/
Surface::Surface()
:	surface_( nullptr )
,	manageSurface_( true )
{
}

/******************************************************************************
 * Constructor
 ******************************************************************************/
Surface::Surface( const std::string& bmp_file )
:	surface_( nullptr )
,	manageSurface_( true )
{
	surface_ = SDL_LoadBMP( "./sprites.bmp" );
	SDL_SetColorKey( surface_, true, 0 );
}

/******************************************************************************
 * Constructor
 ******************************************************************************/
Surface::Surface( SDL_Surface* surface )
:	surface_( surface )
,	manageSurface_( false )
{
}

/******************************************************************************
 * Destructor
 ******************************************************************************/
Surface::~Surface()
{
	if ( manageSurface_ )
	{
		SDL_FreeSurface( surface_ );
	}
}


void Surface::initialize()
{
}


void Surface::finalize()
{
}

void Surface::load( const std::string& bmp_file )
{
	surface_ = SDL_LoadBMP( bmp_file.c_str() );
	SDL_SetColorKey( surface_, true, 0 ); // 0: 00/00/00 noir -> transparent
}


void Surface::draw( const Sprite& sprite, int x, int y )
{
	SDL_Rect dst{ x, y, 0, 0 };
	SDL_BlitSurface( sprite.surface_->surface_, sprite.geometry_, surface_, &dst );
}
