#include "App.h"
#include "u1Bar.h"
#include "u1Image.h"
#include "m1Scene.h"

u1Bar::u1Bar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback) :u1GUI(BAR, x, y, parent, {0, 0, 0, 0}, true, false, false, false)
{
	bar_type = type;

	this->max_capacity = max_capacity;
	current_capacity = max_capacity;

	if (type == HPBAR)
	{
		empty_bar = App->gui->AddImage(x, y, { 1024, 3098, 185, 25 }, App->scene, App->scene->bg_hud, true, false, false, false);
		full_hp = App->gui->AddImage(7, 5, { 1030, 3144, 172, 10 }, App->scene, empty_bar, true, false, false, false);
	}

	if (type == MANABAR)
	{
		empty_bar = App->gui->AddImage(x, y, { 1024, 3098, 185, 25 }, App->scene, App->scene->bg_hud, true, false, false, false);
		full_mana = App->gui->AddImage(7, 5, { 1030, 3180, 172, 10 }, App->scene, empty_bar, true, false, false, false);
	}
}

u1Bar::~u1Bar() {}