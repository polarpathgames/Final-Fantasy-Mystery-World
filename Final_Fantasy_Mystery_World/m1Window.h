#ifndef __m1WINDOW_H__
#define __m1WINDOW_H__

#include "m1Module.h"
#include <string>
struct SDL_Window;
struct SDL_Surface;

class m1Window : public m1Module
{
public:

	m1Window();

	// Destructor
	virtual ~m1Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* new_title);

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

	// Retrieve window scale
	uint GetScale() const;

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

public:
	std::string	title;
	uint		width;
	uint		height;
	uint		scale;

	bool fullscreen = false;

};

#endif // __j1WINDOW_H__