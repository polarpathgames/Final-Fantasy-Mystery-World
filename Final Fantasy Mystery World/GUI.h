#ifndef __GUI_H__
#define __GUI_H__

#include "j1UIManager.h"
#include "p2Point.h"

struct SDL_Texture;

class GUI
{
public:
	GUI(int x, int y);
	virtual ~GUI();

	virtual bool Update(float dt);
	virtual void Draw(SDL_Texture* texture);

public:
	UI type = UI::NONE;
	iPoint position;

};


#endif // !__GUI_H__
