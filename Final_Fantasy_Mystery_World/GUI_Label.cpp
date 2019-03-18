#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_Label.h"
#include "j1Textures.h"
#include "p2Log.h"

GUI_Label::GUI_Label(int x, int y, std::string text, j1Module* callback, UIType type, GUI* parent) : GUI(x, y, callback, parent)
{
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;

	int w = 0, h = 0;

	App->fonts->CalcSize(this->text.c_str(), w, h, App->fonts->default);
	texture = App->fonts->Print(text.c_str(), { 0, 0, 0, 255 }, App->fonts->default);
	animation_rect.w = w;
	animation_rect.h = h;
}
GUI_Label::~GUI_Label()
{
	text.clear();
	App->tex->UnLoad(texture);
	texture = nullptr;
	delete texture;
}