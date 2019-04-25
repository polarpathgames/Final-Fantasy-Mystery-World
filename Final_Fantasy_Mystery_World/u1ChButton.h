#ifndef __u1ChButton_H__
#define __u1ChButton_H__

#include "u1UI_Element.h"
#include "u1Label.h"

class u1Label;
class u1Image;

enum class PlayerType;


class u1ChButton : public u1GUI
{
public:
	u1ChButton() : u1GUI(BUTTON, 0, 0, nullptr, { 0,0,0,0 }) {}
	u1ChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, PlayerType type, bool draw, bool inter, bool drag, bool focus);
	~u1ChButton();

	void InnerDraw();

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hover_rect, const SDL_Rect &click_rect);

	void PrintImages();

private:
	//SDL_Rect idle_rect = { 0,0,0,0 }; idle rect is section rect
	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };

	PlayerType player_type;

};

#endif