#ifndef __u1VerticalSlider_H__
#define __u1VerticalSlider_H__

#include "u1UI_Element.h"
#include "u1Button.h"


class u1VerticalSlider : public u1GUI
{
public:
	u1VerticalSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent);
	~u1VerticalSlider();

	void InnerDraw();
	void UpdateElement();

public:

	SDL_Rect background_rect{ 0,0,0,0 };
	SDL_Rect idle_rect{ 0,0,0,0 };
	SDL_Rect hover_rect{ 0,0,0,0 };
	SDL_Rect push_rect{ 0,0,0,0 };

	int offset_x = 0;
	iPoint background_pos{ 0,0 };

	int min_y = 0;
	int max_y = 0;

	int * position = nullptr;

};
#endif //__!__u1VerticalSlider_H__ 
