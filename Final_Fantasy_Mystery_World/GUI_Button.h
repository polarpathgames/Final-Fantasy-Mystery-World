#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include "GUI.h"
#include "GUI_Label.h"

class GUI_Button : public GUI
{
public:
	GUI_Button(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, GUI* parent, bool draw, bool inter, bool drag, bool focus);
	~GUI_Button();

	void InnerDraw();

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hover_rect, const SDL_Rect &click_rect);

private:
	//SDL_Rect idle_rect = { 0,0,0,0 }; idle rect is section rect
	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
};



#endif