#include "j1App.h"
//#include "j1Fonts.h"
#include "GUI_button.h"
//#include "GUI_Label.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "j1Scene.h"

GUI_Button::GUI_Button(int x, int y, SDL_Rect rect, SDL_Rect rec2, SDL_Rect rect3, j1Module* callback, UI type, GUI* parent) : GUI(x, y, callback, parent)
{

	position.x = x;
	position.y = y;
	this->type = type;
	this->normal = rect;
	this->mouse_in = rec2;
	this->clicked = rect3;
	this->animation_rect = normal;

}

GUI_Button::~GUI_Button()
{
	/*if (text != nullptr)
	{
		App->tex->UnLoad(texture);
		text = nullptr;
		delete text;
	}*/

}

void GUI_Button::setAnimation(int state)
{
	if (state == 1)
		animation_rect = normal;

	else if (state == 2)
		animation_rect = mouse_in;

	else if (state == 3)
		animation_rect = clicked;
}

