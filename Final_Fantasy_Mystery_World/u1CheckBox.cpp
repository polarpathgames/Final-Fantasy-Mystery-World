#include "u1CheckBox.h"
#include "App.h"
#include "u1UI_Element.h"
#include "m1GUI.h"
#include "m1Render.h"

u1CheckBox::u1CheckBox(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent)
	:u1GUI(CHECKBOX, x, y, parent, idle, true, true)
{
	hovered_rect = hover;
	clicked_rect = push;
}

void u1CheckBox::InnerDraw()
{
	if (drawable) 
	{
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F, true);

		if (box_clicked) 
		{
			App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect,  false, SDL_FLIP_NONE, 0.0F, true);
		}
	}
}

void u1CheckBox::AddOptions(u1CheckBox* option) {
	if (std::find(options.begin(), options.end(), option) == options.end()) { //options.find(option) == -1
		options.push_back(option);
	}
	if (std::find(option->options.begin(), option->options.end(), this) == option->options.end()) { //option->options.find(this) == -1
		option->options.push_back(this);
	}
}

void u1CheckBox::Clicked() {
	box_clicked = !box_clicked;
	if (is_option) {
		for (std::list<u1CheckBox*>::iterator item = options.begin(); item != options.end(); ++item) {
			(*item)->box_clicked = false;
		}
	}
}

bool u1CheckBox::GetIsClicked()const {
	return box_clicked;
}

void u1CheckBox::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
{
	section = std_rect;
	hovered_rect = hl_rect;
	clicked_rect = click_rect;

	App->render->DrawQuad(section, 255, 0, 0, 255, true, false);

	if (section.x == 0 && section.y == 0) {
		section.x = std_rect.w;
		section.y = std_rect.h;
	}
}