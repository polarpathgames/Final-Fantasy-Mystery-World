#include "j1App.h"
//#include "j1Fonts.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Scene.h"

GUI_Button::GUI_Button(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, GUI* parent, bool draw, bool inter, bool drag, bool focus = true)
	:GUI(BUTTON, x, y, parent, idle, draw, inter, drag, focus)
{
	hovered_rect = hover;
	clicked_rect = push;

}

GUI_Button::~GUI_Button() {}

void GUI_Button::InnerDraw()
{
		switch (current_state)
		{
		case Mouse_Event::HOVER:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_DOWN:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_REPEAT:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_UP:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::NONE:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
			break;
		default:
			App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
			break;
		}
}

void GUI_Button::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
{
	section = std_rect;
	hovered_rect = hl_rect;
	clicked_rect = click_rect;
}