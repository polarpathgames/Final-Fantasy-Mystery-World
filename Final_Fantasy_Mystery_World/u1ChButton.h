#ifndef __u1ChButton_H__
#define __u1ChButton_H__

#include "u1Button.h"

class u1ChButton : public u1Button
{
public:
	u1ChButton() : u1Button() {}
	u1ChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, bool draw, bool inter, bool drag, bool focus);
	~u1ChButton();

	void PreUpdateElement();

	void AddElementsToShow(u1GUI* element);
	void AddElementsToShow(std::list<u1GUI*> elements);

private:
	std::list<u1GUI*> elements_to_show;
};

#endif