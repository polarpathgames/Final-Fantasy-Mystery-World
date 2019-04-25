#include "App.h"
#include "c1CutsceneImage.h"
#include "m1GUI.h"
#include "u1Image.h"
#include "SDL/include/SDL_rect.h"

c1CutsceneImage::c1CutsceneImage(int pos_x, int pos_y, SDL_Rect rect, bool image)
{
	this->image = App->gui->AddImage(pos_x, pos_y, rect, nullptr, App->gui->screen, image, false, false, false);
}

c1CutsceneImage::~c1CutsceneImage()
{
	App->gui->DeleteUIElement(image);
}


void c1CutsceneImage::ChangeState(bool active)
{
	image->drawable = active;
}