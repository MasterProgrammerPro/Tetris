#include "window.h"


// Graphics library
#include <SDL.h>

//Default constructor
Window::Window()
:	window_( nullptr )
,	surface_( nullptr )
,	w_( 200 )
,	h_( 200 )
,	title_( "NoName" )
{
}

//Constructor
Window::Window( const std::string& name, int w, int h )
:	window_( nullptr )
,	surface_( nullptr )
,	w_( w )
,	h_( h )
,	title_( name )
{
}

//Destructor
Window::~Window()
{
}

//Initialize
void Window::initialize()
{
	window_ = SDL_CreateWindow( title_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_, h_, SDL_WINDOW_SHOWN );

	SDL_Surface* surface = SDL_GetWindowSurface(window_);
	surface_ = new Surface( surface );
}

//Finalize
void Window::finalize()
{
	SDL_DestroyWindow( window_ );
}

//draw()
void Window::draw( const Sprite& sprite, int x, int y )
{
	surface_->draw( sprite, x, y );
}

//update()
void Window::update() const
{
	// Copy the window surface to the screen
	SDL_UpdateWindowSurface( window_ );
}
