#ifndef _GUI_IMAGE_H__ 
#define _GUI_IMAGE_H__

#include "GUI.h"


class GUI_Image : public GUI
{
private:
	SDL_Rect image;

public:
	GUI_Image(int x, int y, UI type, SDL_Rect* rect = NULL);

};
#endif //_GUI_IMAGE_H__