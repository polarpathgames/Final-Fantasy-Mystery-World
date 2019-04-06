#include "App.h"
#include "u1Button.h"
#include "u1Label.h"
#include "m1Textures.h"
#include "p2Log.h"
#include "m1Render.h"
#include "m1Scene.h"

u1Button::u1Button(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, bool draw, bool inter, bool drag, bool focus = true)
	:u1GUI(BUTTON, x, y, parent, idle, draw, inter, drag, focus)
{
	hovered_rect = hover;
	clicked_rect = push;

}

u1Button::~u1Button() {}

void u1Button::InnerDraw()
{
		switch (current_state)
		{
		case Mouse_Event::HOVER:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_DOWN:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_REPEAT:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::CLICKED_UP:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
			break;
		case Mouse_Event::NONE:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
			break;
		default:
			app->render->Blit((SDL_Texture*)app->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
			break;
		}
}

void u1Button::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
{
	section = std_rect;
	hovered_rect = hl_rect;
	clicked_rect = click_rect;
}