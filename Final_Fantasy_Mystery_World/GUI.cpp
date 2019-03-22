#include "j1App.h"
#include "j1UIManager.h"
#include "j1Render.h"
#include "GUI_Button.h"
#include "j1Window.h"
#include "j1Input.h"
#include "p2Log.h"
#include "GUI.h"

GUI::GUI(UIType type, const int &x, const int &y, GUI* parent, const SDL_Rect &section, bool drag, bool inter, bool draw)
	:type(type), position({ x,y }), section(section), parent(parent), drawable(draw), interactable(inter), draggable(drag)
{
	if (parent != nullptr) {
		parent->childs.push_back(this);
	}
}

GUI::~GUI() {}

void GUI::Draw()
{
	draw_offset.x = position.x;
	draw_offset.y = position.y;

	if (parent != nullptr) {
		for (GUI* p = parent; p; p = p->parent) {
			draw_offset += p->position;
		}
	}

	InnerDraw();

	if (App->ui_manager->debug_ui) {
		DebugDraw();
	}
}

void GUI::InnerDraw()
{
	App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), position.x, position.y, &section, false, SDL_FLIP_NONE, 0);
}

bool GUI::Update()
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && (mouse.x != last_mouse.x || mouse.y != last_mouse.y)) {
		if (draggable) {

			int x_motion = mouse.x - last_mouse.x, y_motion = mouse.y - last_mouse.y;
			SetPos(GetLocalPosition().x + x_motion * App->win->GetScale(), GetLocalPosition().y + y_motion * App->win->GetScale());
		}
	}
	last_mouse = mouse;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		for (std::list<j1Module*>::iterator module = listeners.begin(); module != listeners.end(); ++module) {
			(*module)->Interact(this);
		}
	}
	
	return true;
}

bool GUI::CleanUp()
{

	return true;
}

bool GUI::MouseIn(GUI* element)
{
	GUI_Button* ex2 = (GUI_Button*)element;

	/*if (element->type == BUTTON)
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
	}*/
	return false;
}

void GUI::SetPos(const int & x, const int & y)
{
	position.create(x,y);
}

UIType GUI::GetType() const
{
	return type;
}

int GUI::GetPriority() const
{
	return priority;
}

iPoint GUI::GetGlobalPosition() const
{
	return draw_offset;
}

iPoint GUI::GetLocalPosition() const
{
	return { position.x, position.y };
}

void GUI::DebugDraw()
{
	App->render->DrawQuad({ position.x,position.y,section.w,section.h }, 255, 0, 0, 255, false, false);
}

void GUI::AddListener(j1Module * module)
{
	if (std::find(listeners.begin(),listeners.end(),module) == listeners.end()) { //if module is not in listeners list -> push back
		listeners.push_back(module);
	}
}

void GUI::DeleteListener(j1Module * module)
{
	listeners.remove(module);
}
