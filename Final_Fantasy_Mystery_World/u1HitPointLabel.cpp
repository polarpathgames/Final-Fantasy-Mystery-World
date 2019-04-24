#include "u1HitPointLabel.h"
#include "m1Fonts.h"
#include "m1Render.h"
#include "App.h"
#include "m1Textures.h"
#include "p2Log.h"

u1HitPointLabel::u1HitPointLabel(const int & x, const int & y, const char* text, u1GUI* parent, const Color & color, const FontType & type)
	: u1GUI(HIT_POINT_LABEL, x, y, parent, {0,0,0,0}, true, false, false, false)
{
	
	id_font = type;
	this->text.assign(text);
	SetColor(color);
	color_type = color;
	time = SDL_GetTicks();
	texture = App->fonts->Print(text, this->color, id_font);
	App->fonts->CalcSize(text, section.w, section.h, id_font);

}

u1HitPointLabel::~u1HitPointLabel()
{
	text.clear();
	App->tex->UnLoad(texture);
	texture = nullptr;
}

void u1HitPointLabel::SetColor(const Color & c)
{
	switch (c) {
	case RED: //Granate
		color = { 190,11,20,color.a };
		break;
	case GREEN:
		color = { 0,255,0,color.a };
		break;
	case BLUE: //Azul mana
		color = { 20, 116, 225,color.a };
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
	if (time < SDL_GetTicks() - 500) {
		if (alpha > 0) {
			switch (color_type) {
			case RED:
				position.y += 100 * App->GetDeltaTime();
				break;
			case BLUE: {
				const char* minus = text.data();
				const char* min = "-";
				if (minus[0] == min[0])
					position.y += 100 * App->GetDeltaTime();
				else 
					position.y -= 100 * App->GetDeltaTime();
				break; }
			case GREEN:
				position.y -= 100 * App->GetDeltaTime();
				break;
			case YELLOW: {
				const char* minus = text.data();
				const char* min = "-";
				if (minus[0] == min[0])
					position.y += 100 * App->GetDeltaTime();
				else
					position.y -= 100 * App->GetDeltaTime();
				break; }
				break;
			default:
				break;
			}
			
			alpha -= 250 * App->GetDeltaTime();
			if (alpha >= 1) {
				App->tex->UnLoad(texture);
				texture = App->fonts->Print(text.data(), color, id_font, alpha);
			}
		}
		else to_delete = true;
	}
	App->render->Blit(texture, draw_offset.x, draw_offset.y, NULL, false, SDL_FLIP_NONE, 0.0F);
}
