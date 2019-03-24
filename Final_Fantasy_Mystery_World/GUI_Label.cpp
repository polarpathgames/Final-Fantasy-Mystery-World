#include "j1App.h"
#include "j1Fonts.h"
#include "GUI_Label.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"

GUI_Label::GUI_Label(const int & pos_x, const int & pos_y, const char * txt, const Color & c, const char * path_font, const uint & size, GUI * parent, bool interactable, bool draggable, uint32 wrap_length)
	:GUI(LABEL, pos_x, pos_y, parent, { 0,0,0,0 })
{
	font = App->fonts->Load(path_font, size);
	text.assign(txt);

	SetColor(c);
	if (wrap_length == 0U)
		texture = App->fonts->Print(text.data(), color, font);
	else texture = App->fonts->PrintWrapped(text.data(), color, font, wrap_length);

	App->fonts->CalcSize(txt, section.w, section.h, font);
}
GUI_Label::~GUI_Label()
{
	text.clear();
	App->tex->UnLoad(texture);	
	App->fonts->UnLoad(font);
	font = nullptr;
	texture = nullptr;
}

void GUI_Label::InnerDraw()
{
	App->render->Blit(texture, draw_offset.x, draw_offset.y, NULL, false, SDL_FLIP_NONE, 0.0F);
}

void GUI_Label::SetText(const char * txt)
{
	text.assign(txt);
	App->tex->UnLoad(texture);
	texture = App->fonts->Print(text.data(), color, font);
	App->fonts->CalcSize(text.data(), section.w, section.h, font);
}

void GUI_Label::SetColor(Color c)
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
	texture = App->fonts->Print(text.data(), color, font);
}

void GUI_Label::SetColor(const SDL_Color & c)
{
	color = c;
	texture = App->fonts->Print(text.data(), color, font);
}

void GUI_Label::ChangeFont(const char * f, const int & size)
{
	font = App->fonts->Load(f, size);
	texture = App->fonts->Print(text.data(), color, font);
	App->fonts->CalcSize(text.data(), section.w, section.h, font);
}
