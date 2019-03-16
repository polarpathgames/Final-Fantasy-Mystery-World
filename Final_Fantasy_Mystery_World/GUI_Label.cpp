#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_Label.h"
#include "j1Textures.h"
#include "p2Log.h"

Gui_Label::Gui_Label(int x, int y, std::string text, j1Module* callback, UI type, GUI* parent) : GUI(x, y, callback, parent)
{
	position.x = x;
	position.y = y;
	this->type = type;
	this->text = text;

	int w = 0, h = 0;

	App->fonts->CalcSize(this->text.c_str(), w, h, App->fonts->default);
	animation_rect.w = w;
	animation_rect.h = h;
	texture = App->fonts->Print(text.c_str(), { 0, 0, 0, 255 }, App->fonts->default);
}
Gui_Label::~Gui_Label()
{
	text.clear();
	App->tex->UnLoad(texture);
	text = nullptr;
	texture = nullptr;
	delete texture;
}