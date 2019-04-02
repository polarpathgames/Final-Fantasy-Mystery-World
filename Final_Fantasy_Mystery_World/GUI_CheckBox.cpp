#include "GUI_CheckBox.h"
#include "j1App.h"
#include "GUI.h"
#include "j1UIManager.h"
#include "j1Render.h"

GUI_CheckBox::GUI_CheckBox(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, GUI* parent)
	:GUI(CHECKBOX, x, y, parent, idle, true, true)
{
	hovered_rect = hover;
	clicked_rect = push;
}

void GUI_CheckBox::InnerDraw()
{
	if (drawable) 
	{
		App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F, true);

		if (box_clicked) 
		{
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect,  false, SDL_FLIP_NONE, 0.0F, true);
		}
	}
}

void GUI_CheckBox::AddOptions(GUI_CheckBox* option) {
	if (std::find(options.begin(), options.end(), option) == options.end()) { //options.find(option) == -1
		options.push_back(option);
	}
	if (std::find(option->options.begin(), option->options.end(), this) == option->options.end()) { //option->options.find(this) == -1
		option->options.push_back(this);
	}
}

void GUI_CheckBox::Clicked() {
	box_clicked = !box_clicked;
	if (is_option) {
		for (std::list<GUI_CheckBox*>::iterator item = options.begin(); item != options.end(); ++item) {
			(*item)->box_clicked = false;
		}
	}
}

bool GUI_CheckBox::GetIsClicked()const {
	return box_clicked;
}

void GUI_CheckBox::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
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