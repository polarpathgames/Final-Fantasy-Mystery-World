#include "App.h"
#include "m1Fonts.h"
#include "u1Label.h"
#include "m1Textures.h"
#include "m1Render.h"
#include "p2Log.h"

u1Label::u1Label(const int & pos_x, const int & pos_y, const char * txt, const Color & c, FontType font, u1GUI * parent, bool interactable, bool draggable, uint32 wrap_length, bool focus)
	:u1GUI(LABEL, pos_x, pos_y, parent, { 0,0,0,0 }, true, false, false, focus)
{
	id_font = font;
	text.assign(txt);

	SetColor(c);
	if (wrap_length == 0U)
		texture = app->fonts->Print(text.data(), color, id_font);
	else texture = app->fonts->PrintWrapped(text.data(), color, id_font, wrap_length);

	app->fonts->CalcSize(txt, section.w, section.h, id_font);
}

u1Label::~u1Label()
{
	text.clear();
	app->tex->UnLoad(texture);
	texture = nullptr;
}

void u1Label::InnerDraw()
{
	app->render->Blit(texture, draw_offset.x, draw_offset.y, NULL, false, SDL_FLIP_NONE, 0.0F);
}

void u1Label::SetText(const char * txt)
{
	text.assign(txt);
	app->tex->UnLoad(texture);
	texture = app->fonts->Print(text.data(), color, id_font);
	app->fonts->CalcSize(text.data(), section.w, section.h, id_font);
}

void u1Label::SetColor(Color c)
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

void u1Label::SetColor(const SDL_Color & c)
{
	color = c;
}

std::string u1Label::GetText()
{
	return text;
}

void u1Label::ChangeFont(const char * f, const int & size)
{
	id_font = app->fonts->Load(f, size)->type;
	texture = app->fonts->Print(text.data(), color, id_font);
	app->fonts->CalcSize(text.data(), section.w, section.h, id_font);
}
