#include "App.h"
#include "u1ChButton.h"
#include "u1Image.h"
#include "u1Label.h"
#include "m1Textures.h"
#include "p2Log.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1MainMenu.h"
#include "m1GUI.h"
#include "m1DialogSystem.h"

u1ChButton::u1ChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, PlayerType type, bool draw, bool inter, bool drag, bool focus = true)
	:u1GUI(BUTTON, x, y, parent, idle, draw, inter, drag, focus)
{
	hovered_rect = hover;
	clicked_rect = push;
	player_type = type;
}

u1ChButton::~u1ChButton() {}

void u1ChButton::InnerDraw()
{
	switch (current_state)
	{
	case Mouse_Event::HOVER:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
		PrintInfo();
		break;
	case Mouse_Event::CLICKED_DOWN:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Mouse_Event::CLICKED_REPEAT:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Mouse_Event::CLICKED_UP:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Mouse_Event::NONE:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
		break;
	default:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F);
		break;
	}
}

void u1ChButton::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
{
	section = std_rect;
	hovered_rect = hl_rect;
	clicked_rect = click_rect;
}

void u1ChButton::PrintInfo()
{
	switch (player_type)
	{
	case PlayerType::WARRIOR:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 500, 175, &warrior_rect, false, SDL_FLIP_NONE, 0.0F);
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 370, 600, &warrior_info, false, SDL_FLIP_NONE, 0.0F);
		break;
	case PlayerType::ARCHER:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 580, 180, &archer_rect, false, SDL_FLIP_NONE, 0.0F);
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 370, 600, &archer_info, false, SDL_FLIP_NONE, 0.0F);
		break;
	case PlayerType::MAGE:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 580, 180, &mage_rect, false, SDL_FLIP_NONE, 0.0F);
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 370, 600, &mage_info, false, SDL_FLIP_NONE, 0.0F);
		break;
	}
}