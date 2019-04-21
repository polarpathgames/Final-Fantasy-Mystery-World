#include "u1HitPointLabel.h"
#include "m1Fonts.h"
#include "m1Render.h"
#include "App.h"
#include "m1Textures.h"

u1HitPointLabel::u1HitPointLabel(const int & x, const int & y, const char* text, u1GUI* parent, const Color & color, const FontType & type)
	: u1GUI(HIT_POINT_LABEL, x, y, parent, {0,0,0,0}, true, false, false, false)
{
	
	id_font = type;
	this->text.assign(text);
	SetColor(color);
	time = SDL_GetTicks();
	texture = App->fonts->Print(text, this->color, id_font);
	App->fonts->CalcSize(text, section.w, section.h, id_font);

}

void u1HitPointLabel::SetColor(const Color & c)
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

void u1HitPointLabel::UpdateElement()
{
	
}

void u1HitPointLabel::InnerDraw()
{
	if (alpha > 20) {
		alpha -= 60 * App->GetDeltaTime();
		App->tex->UnLoad(texture);
		texture = App->fonts->Print(text.data(), color, id_font, alpha);
	}
		


	App->render->Blit(texture, draw_offset.x, draw_offset.y, NULL, false, SDL_FLIP_NONE, 0.0F);
}
