#include "j1App.h"
#include "j1UIManager.h"
#include "j1Render.h"
#include "GUI_Button.h"
#include "j1Window.h"
#include "j1Input.h"
#include "p2Log.h"
#include "GUI.h"

GUI::GUI(UIType type, const int &x, const int &y, GUI* parent, const SDL_Rect &section, bool draw, bool inter, bool drag, bool focus)
	:type(type), position({ x,y }), section(section), parent(parent), drawable(draw), interactable(inter), draggable(drag), allow_focus(focus)
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
		for (GUI* p = parent; p != nullptr; p = p->parent) {
			draw_offset += p->position;
		}
	}

	if (drawable)
		InnerDraw();

	if (App->ui_manager->debug_ui) {
		DebugDraw();
	}
}

void GUI::InnerDraw()
{
	App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0);
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

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		for (std::list<j1Module*>::iterator module = listeners.begin(); module != listeners.end(); ++module) {
			if (*module != nullptr)
				if (!(*module)->Interact(this))
					break;
		}
	}
	
	return true;
}

bool GUI::CleanUp()
{

	return true;
}

void GUI::SetPos(const int & x, const int & y)
{
	position.create(x,y);
}

void GUI::SetPosRespectParent(Position_Type pos, const int& margin)
{
	int x = 0, y = 0;
	switch (pos)
	{
	case CENTERED:
		x = (parent->section.w - section.w) * 0.5F;
		y = (parent->section.h - section.h) * 0.5F;
		break;
	case CENTERED_UP:
		x = (parent->section.w - section.w) * 0.5F;
		y = margin;
		break;
	case CENTERED_DOWN:
		x = (parent->section.w - section.w) * 0.5F;
		y = parent->section.h - section.h - margin;
		break;
	case LEFT_CENTERED:
		x = margin;
		y = (parent->section.h - section.h) * 0.5F;
		break;
	case LEFT_UP:
		x = margin;
		y = margin;
		break;
	case LEFT_DOWN:
		x = margin;
		y = parent->section.h - section.h - margin;
		break;
	case RIGHT_CENTERED:
		x = parent->section.w - section.w - margin;
		y = (parent->section.h - section.h) * 0.5F;
		break;
	case RIGHT_UP:
		x = parent->section.w - section.w - margin;
		y = margin;
		break;
	case RIGHT_DOWN:
		x = parent->section.w - section.w - margin;
		y = parent->section.h - section.h - margin;
		break;
	default:
		x = (parent->section.w - section.w) * 0.5F;
		y = (parent->section.h - section.h) * 0.5F;
		break;
	}
	SetPos(x, y);
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

SDL_Rect GUI::GetRect() const
{
	return section;
}

void GUI::DebugDraw()
{
	App->render->DrawQuad({ draw_offset.x,draw_offset.y,section.w,section.h }, 255, 0, 0, 255, false, false);
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