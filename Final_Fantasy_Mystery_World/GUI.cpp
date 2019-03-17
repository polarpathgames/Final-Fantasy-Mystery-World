#include "j1App.h"
#include "j1UIManager.h"
#include "j1Render.h"
#include "GUI.h"

GUI::GUI(int x, int y, j1Module* callback, GUI* parent)
{
	this->parent = parent;
	this->callback = callback;
}

GUI::~GUI() {}

bool GUI::Update(float dt)
{
	bool ret = true;

	return ret;
}

void GUI::Draw(SDL_Texture* texture)
{
	App->render->Blit(texture, position.x, position.y, &animation_rect, false, SDL_FLIP_NONE, 0);
}

bool GUI::CleanUp()
{

	return true;
}