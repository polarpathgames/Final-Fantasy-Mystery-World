#include "App.h"
#include "u1Bar.h"
#include "u1Image.h"
#include "e1Player.h"
#include "u1Label.h"
#include "m1MenuManager.h"
#include "m1Scene.h"
#include "m1Render.h"

u1Bar::u1Bar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback) :u1GUI(BAR, x, y, parent, {0, 0, 0, 0}, true, false, false, false)
{
	bar_type = type;

	this->max_capacity = max_capacity;
	current_quantity = max_capacity;

	if (type == HPBAR)
	{
		current_width = max_width;
		empty_bar = App->gui->AddImage(x, y, { 1400, 3104, 185, 25 }, App->scene, App->scene->bg_hud, false, false, false, false);
		filled_bar = App->gui->AddImage(7, 5, { 1405, 3149, 172, 10 }, App->scene, empty_bar, false, false, false, false);
		PrintBarNumbers();
	}

	if (type == MANABAR)
	{
		current_width = max_width;
		empty_bar = App->gui->AddImage(x, y, { 1400, 3104, 185, 25 }, App->scene, App->scene->bg_hud, false, false, false, false);
		filled_bar = App->gui->AddImage(7, 5, { 1405, 3185, 172, 10 }, App->scene, empty_bar, false, false, false, false);
		PrintBarNumbers();
	}
	if (type == SKIPBAR)
	{
		current_quantity = 0;
		current_width = 0;
		max_width = 33;
		empty_bar = App->gui->AddImage(x, y, { 1486,2111,33,31 }, nullptr, App->gui->screen, true, false, false, false);
		filled_bar = App->gui->AddImage(x, y, { 1418,2111,0,31 }, nullptr, App->gui->screen, true, false, false, false);
	}

	
}

u1Bar::~u1Bar() {}

void u1Bar::UpdateBar(int quantity, UIType bar_type)
{
	if (empty_bar != nullptr)
	{
		targe_width = CalculateBar(quantity);

		if (targe_width != current_width) {
			has_change = true;
			/*
			current_width = new_width;
			App->gui->DeleteUIElement(filled_bar);
			if (bar_type == UIType::HPBAR)
			{
				filled_bar = App->gui->AddImage(7, 5, { 1405, 3149, current_width, 10 }, App->scene, empty_bar, false, false, false, false);
			}

			else if (bar_type == UIType::MANABAR)
			{
				filled_bar = App->gui->AddImage(7, 5, { 1405, 3185, current_width, 10 }, App->scene, empty_bar, false, false, false, false);
			}*/
		}
		
	}
	if (bar_type != SKIPBAR)
		PrintBarNumbers();
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

void u1Bar::InnerDraw()
{
	if (has_change) {
		if (current_width > targe_width) {
			current_width -= 100 * App->GetDeltaTime();
		}
		else if (current_width < targe_width) {
			current_width += 100 * App->GetDeltaTime();
		}
		else {
			has_change = false;
		}
		filled_bar->section.w = current_width;
	}

	if (drawable) {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), empty_bar->draw_offset.x, empty_bar->draw_offset.y, &empty_bar->section, false, SDL_FLIP_NONE, 0);
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), filled_bar->draw_offset.x, filled_bar->draw_offset.y, &filled_bar->section, false, SDL_FLIP_NONE, 0);
	}
}

void u1Bar::PrintBarNumbers()
{
	App->gui->DeleteUIElement(bar_numbers_label);

	if (current_quantity < 0)
		current_quantity = 0;

	std::string bar_nums_str = std::to_string(current_quantity) + "/" + std::to_string(max_capacity);
	const char* bar_nums_char = bar_nums_str.c_str();

	bar_numbers_label = App->gui->AddLabel(100, 5, bar_nums_char, filled_bar, BLACK, FontType::FF32, App->scene, false);

}

