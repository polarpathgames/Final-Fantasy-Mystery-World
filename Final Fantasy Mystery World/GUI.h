#ifndef __GUI_H__
#define __GUI_H__

#include "j1UIManager.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

class GUI
{
public:
	GUI(int x, int y);
	virtual ~GUI();

	virtual bool Update(float dt);
	virtual void Draw(SDL_Texture* texture);
	virtual bool CleanUp();

public:
	UI type = UI::NON;
	iPoint position;

	SDL_Rect atlas_rect;
};


#endif // !__GUI_H__
