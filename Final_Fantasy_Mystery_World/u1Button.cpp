#include "App.h"
#include "u1Button.h"
#include "u1Label.h"
#include "m1Textures.h"
#include "p2Log.h"
#include "m1Render.h"
#include "m1Scene.h"

u1Button::u1Button(const int & x, const int & y, const SDL_Rect & idle, const SDL_Rect & hover, const SDL_Rect & push, u1GUI * parent, bool draw, bool inter, bool drag, bool focus, const iPoint & focus_offset, SDL_Rect * clip_zone, const SDL_Rect & on_hover_extra_image, const iPoint & extra_image_offset)
	:u1GUI(BUTTON, x, y, parent, idle, draw, inter, drag, focus)
{

	hovered_rect = hover;
	clicked_rect = push;

	if (clip_zone != nullptr) {
		this->clip_zone = clip_zone;
		clipable = true;
		new_clip = true;
	}

	this->focus_offset = focus_offset;

	extra_image = on_hover_extra_image;
 	this->offset_extra_image = extra_image_offset;
	this->offset_extra_image.y += GetGlobalRect()->y;
}

u1Button::~u1Button() {}

void u1Button::InnerDraw()
{

	if (extra_image.w != 0 && extra_image.h != 0) {
		if (App->gui->GetFocus() == (u1GUI*)this)
			App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + offset_extra_image.x, offset_extra_image.y, &extra_image, false, SDL_FLIP_NONE, 0.0F);
	}

	if (!drawable)
		return;

	switch (current_state)
	{
	case Element_Event::HOVER:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F, clip_zone);
		break;
	case Element_Event::CLICKED_DOWN:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F, clip_zone);
		break;
	case Element_Event::CLICKED_REPEAT:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &clicked_rect, false, SDL_FLIP_NONE, 0.0F, clip_zone);
		break;
	case Element_Event::CLICKED_UP:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &hovered_rect, false, SDL_FLIP_NONE, 0.0F, clip_zone);
		break;
	case Element_Event::NONE:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F, clip_zone);
		break;
	default:
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0.0F,clip_zone);
		break;
	}



}

void u1Button::PreUpdateElement()
{
	if (clip_zone != nullptr) {
		if (clip_zone->x < GetGlobalRect()->x + GetGlobalRect()->w &&
			clip_zone->x + clip_zone->w > GetGlobalRect()->x &&
			clip_zone->y < GetGlobalRect()->y + GetGlobalRect()->h - 10 &&
			clip_zone->h + clip_zone->y - 20> GetGlobalRect()->y) {
			interactable = true;
			allow_focus = true;
		}
		else {
			interactable = false;
			allow_focus = false;
			if (App->gui->GetFocus() == (u1GUI*)this)
				App->gui->FocusFirstUIFocusable();
		}
	}
}

void u1Button::SetRects(const SDL_Rect &std_rect, const SDL_Rect &hl_rect, const SDL_Rect &click_rect)
{
	section = std_rect;
	hovered_rect = hl_rect;
	clicked_rect = click_rect;
}