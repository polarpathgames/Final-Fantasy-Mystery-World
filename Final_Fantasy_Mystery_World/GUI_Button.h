#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include "GUI.h"
#include "GUI_Label.h"

class GUI_Button : public GUI
{
public:
	GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rect2, SDL_Rect rect3, j1Module* callback, UI type, GUI* parent);
	~GUI_Button();

	void setAnimation(int state);
	void SetText(Gui_Label* text);

private:
	SDL_Rect normal;
	SDL_Rect mouse_in;
	SDL_Rect clicked;
	Gui_Label* text = nullptr;

};



#endif