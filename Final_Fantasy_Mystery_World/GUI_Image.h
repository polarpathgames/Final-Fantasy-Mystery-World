#ifndef _GUI_IMAGE_H__ 
#define _GUI_IMAGE_H__

#include "GUI.h"


class GUI_Image : public GUI
{
public:
	GUI_Image() : GUI(IMAGE, 0, 0, nullptr, { 0,0,0,0 }) {}
	GUI_Image(const int& pos_x,const int& pos_y, const SDL_Rect &image, GUI* parent, bool inter = true, bool drag = false, bool draw = true, bool clipable = false);
	~GUI_Image() {}

};
#endif //_GUI_IMAGE_H__