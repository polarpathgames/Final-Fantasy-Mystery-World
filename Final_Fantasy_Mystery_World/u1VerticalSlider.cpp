#include "u1VerticalSlider.h"
#include "u1UI_Element.h"
#include "m1GUI.h"
#include "m1Render.h"
#include "App.h"

u1VerticalSlider::u1VerticalSlider(const int & x, const int & y, const SDL_Rect & rect, const SDL_Rect & idle, const SDL_Rect & hover, const SDL_Rect & push, u1GUI * parent)
	: u1GUI(VERTICAL_SLIDER, x, y, parent, idle, true, true, true, true)
{

	background_rect = rect;
	idle_rect = idle;
	hover_rect = hover;
	push_rect = push;

	offset_x = (rect.w - idle.w) / 2;



}

u1VerticalSlider::~u1VerticalSlider()
{
}

void u1VerticalSlider::InnerDraw()
{

	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &background_rect, false, SDL_FLIP_NONE, 0.0F);
	switch (current_state)
	{
	case Element_Event::HOVER:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &hover_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Element_Event::CLICKED_DOWN:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &push_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Element_Event::CLICKED_REPEAT:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &push_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Element_Event::CLICKED_UP:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &idle_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	case Element_Event::NONE:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &idle_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	default:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_x, draw_offset.y, &idle_rect, false, SDL_FLIP_NONE, 0.0F);
		break;
	}



}
