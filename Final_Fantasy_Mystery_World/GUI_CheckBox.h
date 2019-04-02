#ifndef __GUI_CHECKBOX_H__
#define __GUI_CHECKBOX_H__

#include "GUI.h"

#include <list>

class GUI_CheckBox :public GUI {

public:

	GUI_CheckBox(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, GUI* parent);
	~GUI_CheckBox() {};

	void InnerDraw();

	void AddOptions(GUI_CheckBox* option);
	void Clicked();
	bool GetIsClicked()const;

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect);

public:
	bool is_option = false;

private:
	bool box_clicked = false;
	std::list<GUI_CheckBox*> options;

	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
};

#endif // !_GUI_CHECKBOX_
