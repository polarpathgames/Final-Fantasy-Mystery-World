#include "j1App.h"
#include "p2Defs.h"
#include "GUI_Image.h"


GUI_Image::GUI_Image(int x, int y, UI type,  SDL_Rect* rect) : GUI(x, y)
{
	position.x = x;
	position.y = y;
	this->type = type;

}