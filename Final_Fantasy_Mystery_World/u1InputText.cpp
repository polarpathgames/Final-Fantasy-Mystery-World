#include "u1InputText.h"
#include "u1UI_Element.h"
#include "m1GUI.h"
#include "m1Render.h"
#include "App.h"
#include "m1Textures.h"
#include "m1Fonts.h"
#include "m1Input.h"


u1InputText::u1InputText(const int & pos_x, const int & pos_y, const char * txt, const Color & c, FontType font, u1GUI * parent,
	bool interactable, bool draggable, bool focus,
	bool has_background, const SDL_Color& bg_color)
	:u1GUI(LABEL, pos_x, pos_y, parent, { 0,0,0,0 },true, false, true, focus),

	id_font(font), has_background(has_background), background_color(bg_color)
{		
	text.assign(txt);
	this->interactable = true;
	this->allow_focus = true;
	SetColor(c);

	texture = App->fonts->Print(text.data(), color, id_font);
	App->fonts->CalcSize(txt, section.w, section.h, id_font);

	cursor = new Animation();
	cursor->PushBack({ 1608,3102,2,30 });
	cursor->PushBack({ 0,0,0,0 });
	cursor->speed = 2.0F;
	cursor->loop = true;
	uint width_ = 0u;
	App->tex->GetSize(texture, width_, HEIGHT);
}

u1InputText::~u1InputText()
{
	SDL_StopTextInput();
	delete cursor;
	cursor = nullptr;

}

void u1InputText::UpdateElement() 
{

	if (text.length() <= MAX_CHARACTERS || first_update) {
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
	if (has_background) {
		App->render->DrawQuad({ draw_offset.x,draw_offset.y,section.w,section.h }, background_color.r, background_color.g, background_color.b, background_color.a, true, false);
	}

	App->render->Blit(texture, draw_offset.x, draw_offset.y, NULL, false, SDL_FLIP_NONE, 0.0F);

	uint width_ = 0u, height_ = 0u;
	App->tex->GetSize(texture, width_, height_);

	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x + width_, draw_offset.y + HEIGHT*0.4F, &(cursor->GetCurrentFrame(App->GetDeltaTime())), false, SDL_FLIP_NONE, 0.0F);
}

void u1InputText::SetText(const char * txt)
{
	text = txt;
	App->tex->UnLoad(texture);
	texture = App->fonts->Print(text.data(), color, id_font);
	App->fonts->CalcSize(text.data(), section.w, section.h, id_font);
}

void u1InputText::AddText(const char * txt)
{
	if (first_update) {
		text.clear();
		first_update = false;
	}
	text += txt;
	App->tex->UnLoad(texture);
	texture = App->fonts->Print(text.data(), color, id_font);
	App->fonts->CalcSize(text.data(), section.w, section.h, id_font);
}

void u1InputText::DeleteText()
{
	text.pop_back();
	App->tex->UnLoad(texture);
	texture = App->fonts->Print(text.data(), color, id_font);
	App->fonts->CalcSize(text.data(), section.w, section.h, id_font);
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
	App->fonts->CalcSize(text.data(), section.w, section.h, id_font);
}





