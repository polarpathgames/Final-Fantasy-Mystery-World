#include "App.h"
#include "p2Defs.h"
#include "u1Image.h"
#include "App.h"
#include "m1Render.h"

u1Image::u1Image(const int & pos_x, const int & pos_y, const SDL_Rect & image, u1GUI * parent, bool draw, bool inter, bool drag, bool focus, Animation* anim, SDL_Rect* clip_zone)
	:u1GUI(IMAGE, pos_x, pos_y, parent, image, draw, inter, drag, focus) {
	if (anim != nullptr) {
		img_anim = anim;
	}
	if (clip_zone != NULL)
		this->clip_zone = clip_zone;
}

u1Image::~u1Image()
{
	if (img_anim != nullptr) {
		delete img_anim;
		img_anim = nullptr;
	}

	if (new_clip) {
		delete clip_zone;
		clip_zone = nullptr;
	}
}

void u1Image::InnerDraw()
{

	if (!drawable)
		return;

	if (img_anim != nullptr) {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &img_anim->GetCurrentFrame(App->GetDeltaTime()), false, SDL_FLIP_NONE, 0);
		if (img_anim->Finished())
			to_delete = true;
	}
	else {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0, clip_zone);
	}

}

void u1Image::SetClipZone(const SDL_Rect & clip_zone)
{

	if (this->clip_zone == nullptr) {
		new_clip = true;
		this->clip_zone = new SDL_Rect();
		this->clip_zone->x = clip_zone.x;
		this->clip_zone->y = clip_zone.y;
		this->clip_zone->h = clip_zone.h;
		this->clip_zone->w = clip_zone.w;
	}
	else {
		this->clip_zone->x = clip_zone.x;
		this->clip_zone->y = clip_zone.y;
		this->clip_zone->h = clip_zone.h;
		this->clip_zone->w = clip_zone.w;
	}

}

void u1Image::ResetClipZone()
{
	if (new_clip) {
		new_clip = false;
		delete clip_zone;
		clip_zone = nullptr;
	}
}


