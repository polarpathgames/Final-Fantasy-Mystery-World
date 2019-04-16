#ifndef __u1ChButton_H__
#define __u1ChButton_H__

#include "u1UI_Element.h"
#include "u1Label.h"

class u1Label;
class u1Image;

enum class PlayerType;

enum class PlayerButton
{
	WARRIOR,
	ARCHER,
	MAGE,

	NONE,
};

class u1ChButton : public u1GUI
{
public:
	u1ChButton() : u1GUI(BUTTON, 0, 0, nullptr, { 0,0,0,0 }) {}
	u1ChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, PlayerType type, bool draw, bool inter, bool drag, bool focus);
	~u1ChButton();

	void InnerDraw();
	void PrintInfo();

	void SetRects(const SDL_Rect &std_rect, const SDL_Rect &hover_rect, const SDL_Rect &click_rect);

private:
	//SDL_Rect idle_rect = { 0,0,0,0 }; idle rect is section rect
	SDL_Rect hovered_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };

	u1Image* warrior_image = nullptr;
	u1Image* archer_image = nullptr;
	u1Image* mage_image = nullptr;

	SDL_Rect warrior_rect = { 1052, 4079, 327, 358 };
	SDL_Rect archer_rect = { 1701, 4079, 194, 369 };
	SDL_Rect mage_rect = { 1414, 4079, 218, 363 };

	PlayerType player_type;
};

#endif