#include "j1App.h"
#include "j1UIManager.h"
#include "j1Render.h"
#include "GUI_Button.h"
#include "j1Input.h"
#include "p2Log.h"
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

bool GUI::MouseIn(GUI* element)
{
	GUI_Button* ex2 = (GUI_Button*)element;

	if (element->type == BUTTON)
	{
		if (mouse_x > element->position.x && mouse_x < element->position.x + animation_rect.w && mouse_y > element->position.y && mouse_y < element->position.y + element->animation_rect.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				element->callback->Interact(element);
				LOG("IS CLICKED");
				return true;
			}
		}
	}
}