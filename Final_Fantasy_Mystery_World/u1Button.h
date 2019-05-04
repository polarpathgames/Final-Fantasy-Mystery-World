#ifndef __u1Button_H__
#define __u1Button_H__

#include "u1UI_Element.h"
#include "u1Label.h"

class u1Button : public u1GUI
{
public:
	u1Button() : u1GUI(BUTTON, 0, 0, nullptr, { 0,0,0,0 }) {}
	u1Button(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, bool draw, bool inter, bool drag, bool focus, const iPoint &focus_offset = { 0,0 }, SDL_Rect* clip_zone = nullptr);
	~u1Button();

	void InnerDraw();
	void PreUpdateElement();

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hover_rect, const SDL_Rect &click_rect);

private:
	//SDL_Rect idle_rect = { 0,0,0,0 }; idle rect is section rect
	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
	SDL_Rect* clip_zone = nullptr;
};

#endif