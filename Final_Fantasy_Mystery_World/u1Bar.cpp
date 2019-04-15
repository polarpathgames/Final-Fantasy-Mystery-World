#include "App.h"
#include "u1Bar.h"
#include "u1Image.h"
#include "e1Player.h"
#include "m1Scene.h"

u1Bar::u1Bar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback) :u1GUI(BAR, x, y, parent, {0, 0, 0, 0}, true, false, false, false)
{
	bar_type = type;

	this->max_capacity = max_capacity;
	current_quantity = max_capacity;

	if (type == HPBAR)
	{
		current_width = max_width;
		empty_bar = App->gui->AddImage(x, y, { 1024, 3098, 185, 25 }, App->scene, App->scene->bg_hud, true, false, false, false);
		hp_bar = App->gui->AddImage(7, 5, { 1030, 3144, 172, 10 }, App->scene, empty_bar, true, false, false, false);
	}

	if (type == MANABAR)
	{
		current_width = max_width;
		empty_bar = App->gui->AddImage(x, y, { 1024, 3098, 185, 25 }, App->scene, App->scene->bg_hud, true, false, false, false);
		mana_bar = App->gui->AddImage(7, 5, { 1030, 3180, 172, 10 }, App->scene, empty_bar, true, false, false, false);
	}
}

u1Bar::~u1Bar() {}

void u1Bar::UpdateBar(int quantity, UIType bar_type)
{
	if (empty_bar != nullptr)
	{
		if (bar_type == UIType::HPBAR)
		{
			current_width = CalculateBar(quantity);
			App->gui->DeleteUIElement(hp_bar);
			hp_bar = App->gui->AddImage(7, 5, { 1030, 3144, current_width, 10 }, App->scene, empty_bar, true, false, false, false);
		}

		if (bar_type == UIType::MANABAR)
		{
			current_width = CalculateBar(quantity);
			App->gui->DeleteUIElement(mana_bar);
			mana_bar = App->gui->AddImage(7, 5, { 1030, 3180, current_width, 10 }, App->scene, empty_bar, true, false, false, false);
		}
	}
}

int u1Bar::CalculateBar(int quantity)
{

	int new_width = current_width;
	int new_quantity = (current_quantity + quantity);
	current_quantity += quantity;

	if (max_capacity != 0)
		new_width = (new_quantity * max_width) / max_capacity;

	if (current_quantity <= 0) {
		current_quantity = 0;
		return 0;
	}

	if (current_quantity >= max_capacity) {
		current_quantity = max_capacity;
		return max_width;
	}

	return new_width;

}