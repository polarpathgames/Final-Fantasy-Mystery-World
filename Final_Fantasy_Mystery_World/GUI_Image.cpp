#include "j1App.h"
#include "p2Defs.h"
#include "GUI_Image.h"

GUI_Image::GUI_Image(const int & pos_x, const int & pos_y, const SDL_Rect & image, GUI * parent, bool draw, bool inter, bool drag)
	:GUI(IMAGE,pos_x,pos_y,parent,image,draw,inter,drag)	{}
