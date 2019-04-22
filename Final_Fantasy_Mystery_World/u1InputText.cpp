#include "u1InputText.h"
#include "u1UI_Element.h"
#include "m1GUI.h"
#include "m1Render.h"
#include "App.h"
#include "m1Textures.h"
#include "m1Fonts.h"
#include "m1Input.h"


u1InputText::u1InputText(const int & pos_x, const int & pos_y, const char * txt, const Color & c, FontType font, const SDL_Rect& rect,u1GUI * parent)
	:u1GUI(INPUT_BOX, pos_x, pos_y, parent, { 0,0,0,0 },true, false, true, true),

	id_font(font)
{		
	this->interactable = true;
	this->allow_focus = true;

	text.assign(txt);
	box = rect;
	SetColor(c);

	texture = App->fonts->Print("f", color, id_font);

	cursor = DBG_NEW Animation();
	cursor->PushBack({ 1608,3102,2,30 });
	cursor->PushBack({ 0,0,0,0 });
	cursor->speed = 2.0F;

	uint width_ = 0u;
	App->tex->GetSize(texture, width_, HEIGHT);

	SetText("");

	section.w = box.w;
	section.h = box.h;
}

u1InputText::~u1InputText()
{
	SDL_StopTextInput();
	delete cursor;
	cursor = nullptr;

}

void u1InputText::UpdateElement() 
{
	if (text.length() <= MAX_CHARACTERS) {
		SDL_StartTextInput();
		if (!App->input->text_input.empty()) {
			std::string t = App->input->text_input;
			App->input->text_input.clear();
			AddText(t.data());
		}
	}
	else 
		App->input->text_input.clear();

	if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && !text.empty())
	{
		DeleteText();
	}
}

void u1InputText::InnerDraw()
{
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &box, false);

	uint width_ = 0u, height_ = 0u;
	App->tex->GetSize(texture, width_, height_);
	iPoint pos{ 0,0 };
	pos.x = (box.w - (int)width_)*0.5F;
	pos.y = (box.h - (int)HEIGHT)*0.5F;
	pos += draw_offset;

	App->render->Blit(texture, pos.x, pos.y, NULL, false, SDL_FLIP_NONE, 0.0F);

	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), pos.x + width_, pos.y + HEIGHT*0.4F, &(cursor->GetCurrentFrame(App->GetDeltaTime())), false, SDL_FLIP_NONE, 0.0F);
}

void u1InputText::SetText(const char * txt)
{
	text = txt;
	App->tex->UnLoad(texture);
	texture = App->fonts->Print(text.data(), color, id_font);
}

void u1InputText::AddText(const char * txt)
{
	if (text.length() <= MAX_CHARACTERS) {
		text += txt;
		App->tex->UnLoad(texture);
		texture = App->fonts->Print(text.data(), color, id_font);
	}
}

void u1InputText::DeleteText()
{
	if (!text.empty()) {
		text.pop_back();
		App->tex->UnLoad(texture);
		texture = App->fonts->Print(text.data(), color, id_font);
	}
}


void u1InputText::SetColor(const Color & c)
{
	switch (c) {
	case RED:
		color = { 255,0,0,color.a };
		break;
	case GREEN:
		color = { 0,255,0,color.a };
		break;
	case BLUE:
		color = { 0,0,255,color.a };
		break;
	case YELLOW:
		color = { 255,255,0,color.a };
		break;
	case GREY:
		color = { 150,150,150,color.a };
		break;
	case BLACK:
		color = { 0,0,0,color.a };
		break;
	case WHITE:
		color = { 255,255,255,color.a };
		break;
	default:
		color = { 255,255,255,color.a };
		break;
	}
}

void u1InputText::SetColor(const SDL_Color & c)
{
	color = c;
}

std::string u1InputText::GetText()
{
	return text;
}

void u1InputText::ChangeFont(const char * f, const int & size)
{
	id_font = App->fonts->Load(f, size)->type;
	texture = App->fonts->Print(text.data(), color, id_font);

}





