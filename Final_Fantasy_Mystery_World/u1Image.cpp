#include "App.h"
#include "p2Defs.h"
#include "u1Image.h"
#include "App.h"
#include "m1Render.h"

u1Image::u1Image(const int & pos_x, const int & pos_y, const SDL_Rect & image, u1GUI * parent, bool draw, bool inter, bool drag, bool focus, Animation* anim)
	:u1GUI(IMAGE, pos_x, pos_y, parent, image, draw, inter, drag, focus) {
	if (anim != nullptr) {
		img_anim = anim;
	}
}

u1Image::~u1Image()
{
	if (img_anim != nullptr) {
		delete img_anim;
		img_anim = nullptr;
	}
}

void u1Image::InnerDraw()
{
	if (img_anim != nullptr) {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &img_anim->GetCurrentFrame(App->GetDeltaTime()), false, SDL_FLIP_NONE, 0);
		if (img_anim->Finished())
			to_delete = true;
	}
	else {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0);
	}

}


