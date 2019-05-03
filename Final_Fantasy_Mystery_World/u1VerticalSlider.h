#ifndef __u1VerticalSlider_H__
#define __u1VerticalSlider_H__

#include "u1UI_Element.h"
#include "u1Button.h"

class u1Button;

class u1VerticalSlider : public u1GUI
{
public:
	u1VerticalSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent);
	~u1VerticalSlider();

public:

	SDL_Rect background_rect{ 0,0,0,0 };
	SDL_Rect idle_rect{ 0,0,0,0 };
	SDL_Rect hover_rect{ 0,0,0,0 };
	SDL_Rect push_rect{ 0,0,0,0 };


};
#endif //__!__u1VerticalSlider_H__ 
