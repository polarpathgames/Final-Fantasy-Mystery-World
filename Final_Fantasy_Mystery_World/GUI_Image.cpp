#include "j1App.h"
#include "p2Defs.h"
#include "GUI_Image.h"


GUI_Image::GUI_Image(int x, int y, UIType type, GUI* parent, Animation* anim, j1Module* callback, SDL_Rect* rect) : GUI(x, y, callback, parent)
{
	position.x = x;
	position.y = y;
	this->type = type;
	animation_rect = *rect;

}