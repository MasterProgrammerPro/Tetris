#ifndef _WINDOW_
#define _WINDOW_

// STL
#include <string>

// Project
#include "surface.h"
#include "sprite.h"

// Graphics library
struct SDL_Window;

// Project
class Surface;
class Sprite;

/**
  * @class Window
  *
  * @brief The Window class provides interface to the underlying graphics library's window management.
  */

class Window
{
public:

	Window();
	Window( const std::string& name, const int w, const int h );
	virtual ~Window();

	inline int width() const;
	inline int height() const;

	void initialize();
	void finalize();

	void draw( const Sprite& sprite, int x, int y );

	void update() const;


protected:

	//Graphics library
	SDL_Window* window_;

	//Associated underlying surface
	Surface* surface_;

	//Size 
	int w_;
	int h_;

	//Name
	std::string title_;
};

#include "window.inl"

#endif
