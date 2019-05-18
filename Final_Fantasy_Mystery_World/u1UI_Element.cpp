#include "App.h"
#include "m1GUI.h"
#include "m1Render.h"
#include "u1Button.h"
#include "m1Window.h"
#include "m1Audio.h"
#include "m1MainMenu.h"
#include "m1Input.h"
#include "m1Input.h"
#include "p2Log.h"
#include "u1UI_Element.h"

u1GUI::u1GUI(UIType type, const int &x, const int &y, u1GUI* parent, const SDL_Rect &section, bool draw, bool inter, bool drag, bool focus)
	:type(type), position({ x,y }), section(section), parent(parent), drawable(draw), interactable(inter), draggable(drag), allow_focus(focus)
{
	if (parent != nullptr) {
		parent->childs.push_back(this);
	}
	focus_type = FocusType::SQUARE_FOCUS;
}

u1GUI::~u1GUI() {

	if (new_clip) {
		delete clip_zone;
		clip_zone = nullptr;
	}
}

void u1GUI::Draw()
{
	draw_offset.x = position.x;
	draw_offset.y = position.y;

	if (parent != nullptr) {
		for (u1GUI* p = parent; p != nullptr; p = p->parent) {
			draw_offset += p->position;
		}
	}
	global_rect = { draw_offset.x,draw_offset.y,section.w,section.h };

	InnerDraw();

	if (App->gui->debug_ui) {
		DebugDraw();
	}
}

void u1GUI::InnerDraw()
{
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &section, false, SDL_FLIP_NONE, 0);
}

void u1GUI::PreUpdate()
{
	PreUpdateElement();

	switch (current_state)
	{
	case Element_Event::HOVER_ENTER:
		current_state = Element_Event::HOVER;
		break;
	case Element_Event::HOVER_EXIT:
		current_state = Element_Event::NONE;
		break;
	case Element_Event::CLICKED_UP:
		current_state = Element_Event::NONE;
		break;
	}
}

void u1GUI::SetFocus(const FocusType & focus) {
	focus_type = focus;
}

bool u1GUI::Update()
{
	UpdateElement();

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	if (current_state == Element_Event::CLICKED_REPEAT && draggable) {

		if (mouse.x != last_mouse.x || mouse.y != last_mouse.y) {

			int x_motion = mouse.x - last_mouse.x, y_motion = mouse.y - last_mouse.y;
			switch (type) {
			case UIType::VERTICAL_SLIDER:
				SetPos(GetLocalPosition().x, GetLocalPosition().y + y_motion * App->win->GetScale());
				break;
			default:
				SetPos(GetLocalPosition().x + x_motion * App->win->GetScale(), GetLocalPosition().y + y_motion * App->win->GetScale());
				break;
			}
		}
		
	}
	last_mouse = mouse;

	if (current_state == Element_Event::CLICKED_DOWN || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
		for (std::list<m1Module*>::iterator module = listeners.begin(); module != listeners.end(); ++module) {
			if (*module != nullptr)
				if (!(*module)->Interact(this))
					break;
		}
	}
	
	return true;
}

bool u1GUI::CleanUp()
{

	return true;
}

void u1GUI::SetPos(const int & x, const int & y)
{
	position.create(x,y);
}

void u1GUI::SetPosRespectParent(Position_Type pos, const int& margin)
{
	int x = 0, y = 0;
	switch (pos)
	{
	case CENTERED:
		x = (parent->section.w - section.w) * 0.5F + margin;
		y = (parent->section.h - section.h) * 0.5F;
		break;
	case CENTERED_UP:
		x = (parent->section.w - section.w) * 0.5F + margin;
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

UIType u1GUI::GetType() const
{
	return type;
}

int u1GUI::GetPriority() const
{
	return priority;
}

iPoint u1GUI::GetGlobalPosition() const
{
	return draw_offset;
}

iPoint u1GUI::GetLocalPosition() const
{
	return { position.x, position.y };
}

SDL_Rect u1GUI::GetRect() const
{
	return section;
}

void u1GUI::DebugDraw()
{
	App->render->DrawQuad({ draw_offset.x,draw_offset.y,section.w,section.h }, 255, 0, 0, 255, false, false);
}

void u1GUI::AddListener(m1Module * module)
{
	if (std::find(listeners.begin(),listeners.end(),module) == listeners.end()) { //if module is not in listeners list -> push back
		listeners.push_back(module);
	}
}

void u1GUI::DeleteListener(m1Module * module)
{
	listeners.remove(module);
}

SDL_Rect* u1GUI::GetGlobalRect()
{
	if (parent != nullptr) {
		draw_offset.x = position.x;
		draw_offset.y = position.y;
		if (parent != nullptr) {
			for (u1GUI* p = parent; p != nullptr; p = p->parent) {
				draw_offset += p->position;
			}
		}
		global_rect = { draw_offset.x,draw_offset.y,section.w,section.h };
		return &global_rect;
	}

}

void u1GUI::SetClipZone(const SDL_Rect & clip_zone)
{
	if (this->clip_zone != nullptr)
		delete this->clip_zone;

	this->clip_zone = new SDL_Rect();
	this->clip_zone->x = clip_zone.x;
	this->clip_zone->y = clip_zone.y;
	this->clip_zone->h = clip_zone.h;
	this->clip_zone->w = clip_zone.w;
	new_clip = true;

}

void u1GUI::ResetClipZone()
{
	if (new_clip) {
		new_clip = false;
		delete clip_zone;
		clip_zone = nullptr;
	}
}
