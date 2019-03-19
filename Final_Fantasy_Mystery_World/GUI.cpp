#include "j1App.h"
#include "j1UIManager.h"
#include "j1Render.h"
#include "GUI_Button.h"
#include "j1Input.h"
#include "p2Log.h"
#include "GUI.h"

GUI::GUI(UIType type, const int &x, const int &y, GUI* parent, const int &width = 0, const int &height = 0)
	:type(type),position({x,y,width,height}),parent(parent) {}

GUI::~GUI() {}

bool GUI::Update(float dt)
{
	bool ret = true;

	return ret;
}

void GUI::Draw()
{
	App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), position.x, position.y, &section, false, SDL_FLIP_NONE, 0);
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

void GUI::DebugDraw()
{
	App->render->DrawQuad({ position.x,position.y,section.w,section.h }, 255, 0, 0, 1, false, false);
}
