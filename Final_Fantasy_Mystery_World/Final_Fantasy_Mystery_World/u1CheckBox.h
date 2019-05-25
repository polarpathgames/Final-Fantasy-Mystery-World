#ifndef __u1CheckBox_H__
#define __u1CheckBox_H__

#include "u1UI_Element.h"

#include <list>

class u1CheckBox :public u1GUI {

public:

	u1CheckBox(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent);
	~u1CheckBox() {};

	void InnerDraw();

	void AddOptions(u1CheckBox* option);
	void Clicked();
	bool GetIsClicked()const;

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect);

public:
	bool is_option = false;
	bool box_clicked = false;
private:
	
	std::list<u1CheckBox*> options;

	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
};

#endif // !_u1CheckBox_
