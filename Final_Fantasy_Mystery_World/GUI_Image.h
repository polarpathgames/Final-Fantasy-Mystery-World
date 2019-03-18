#ifndef _GUI_IMAGE_H__ 
#define _GUI_IMAGE_H__

#include "GUI.h"


class GUI_Image : public GUI
{
private:
	SDL_Rect image;

public:
	GUI_Image(int x, int y, UIType type, GUI* parent, Animation* anim, j1Module* callback, SDL_Rect* rect = NULL);

};
#endif //_GUI_IMAGE_H__