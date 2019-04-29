#include "App.h"
#include "u1ChButton.h"
#include "u1Image.h"
#include "u1Label.h"
#include "m1Textures.h"
#include "p2Log.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1MainMenu.h"
#include "m1GUI.h"
#include "m1DialogSystem.h"

u1ChButton::u1ChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, bool draw, bool inter, bool drag, bool focus = true)
	:u1Button(x, y, idle, hover, push, parent, draw, inter, drag, focus) {}

u1ChButton::~u1ChButton() {
	elements_to_show.clear();
}

void u1ChButton::PreUpdateElement()
{
	if (current_state == Element_Event::HOVER_ENTER || current_state == Element_Event::HOVER) {
		for (std::list<u1GUI*>::iterator item = elements_to_show.begin(); item != elements_to_show.end(); ++item) {
			(*item)->drawable = true;
		}
	}
	else if(current_state == Element_Event::HOVER_EXIT) {
		for (std::list<u1GUI*>::iterator item = elements_to_show.begin(); item != elements_to_show.end(); ++item) {
			(*item)->drawable = false;
		}
	}
}

void u1ChButton::AddElementsToShow(u1GUI * element)
{
	element->drawable = false;
	elements_to_show.push_back(element);
}

void u1ChButton::AddElementsToShow(std::list<u1GUI*> elements)
{
	for (std::list<u1GUI*>::iterator item = elements.begin(); item != elements.end(); ++item) {
		(*item)->drawable = false;
		elements_to_show.push_back(*item);
	}
}