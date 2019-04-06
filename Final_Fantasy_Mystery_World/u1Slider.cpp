#include "j1App.h"
#include "GUI_Button.h"
#include "p2Log.h"
#include "j1UIManager.h"
#include "GUI_Slider.h"
#include "j1Render.h"

GUI_Slider::GUI_Slider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, GUI * parent) 
	:GUI(SLIDER, x, y, parent, rect, true, true)
{

	slider_rect = rect;

	section = rect;
	
	//callback & parent?
	slider_btn = App->ui_manager->AddButton(x,y, idle, hover, push, nullptr, parent, true, true, true,false);
}

GUI_Slider::~GUI_Slider()
{
}

void GUI_Slider::SetButton(GUI_Button * slider_btn)
{
	this->slider_btn = slider_btn;
}

void GUI_Slider::SetValue(int value)
{
	if (horizontal) {
		this->value = value;
		slider_btn->SetPos(((this->section.w - slider_btn->GetRect().w) * this->value / 100) + this->GetLocalPosition().x + 1, this->GetLocalPosition().y + (this->section.h / 2) - (slider_btn->GetRect().h / 2));
	}
	else {
		this->value = value;
		slider_btn->SetPos(this->GetLocalPosition().x + (this->section.w / 2) - (slider_btn->GetRect().w / 2), ((this->section.h - slider_btn->GetRect().h) * this->value / 100) + this->GetLocalPosition().y);
	}
}

uint GUI_Slider::GetValue() const
{
	int ret = 0;
	if (horizontal)
		ret = (slider_btn->position.x - position.x) * 100 / (section.w - slider_btn->GetRect().w);
	else
		ret = (slider_btn->position.y - position.y) * 100 / (section.h - slider_btn->GetRect().h);
	ret = ret / 10;
	ret = ret * 10;

	return ret;
}

GUI_Button * GUI_Slider::GetButton() const
{
	return slider_btn;
}

bool GUI_Slider::Update(float dt)
{
	bool ret = true;

	//slider_btn->Enabled(enabled);

	return ret;
}

bool GUI_Slider::PostUpdate()
{
	bool ret = true;

	App->render->Blit((SDL_Texture*)App->ui_manager->GetAtlas(), draw_offset.x, draw_offset.y, &slider_rect, false, SDL_FLIP_NONE, 0.0F, true);
	slider_btn->InnerDraw();

	return ret;
}