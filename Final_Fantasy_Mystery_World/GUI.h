#ifndef __GUI_H__
#define __GUI_H__

#include "j1UIManager.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

class GUI
{
public:
	GUI(int x, int y, j1Module* callback, GUI* parent);
	virtual ~GUI();

	virtual bool PreUpdate() { return true; }
	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; }
	virtual void Draw(SDL_Texture* texture);
	virtual bool CleanUp();

public:
	UI type = UI::NON;
	iPoint position;
	GUI* parent = nullptr;
	SDL_Texture* texture = nullptr;
	j1Module* callback = nullptr;
	Animation* current_animation = nullptr;

	SDL_Rect animation_rect = {0, 0, 0, 0};
};


#endif // !__GUI_H__
