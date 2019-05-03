#include "u1VerticalSlider.h"
#include "u1UI_Element.h"
#include "m1GUI.h"

u1VerticalSlider::u1VerticalSlider(const int & x, const int & y, const SDL_Rect & rect, const SDL_Rect & idle, const SDL_Rect & hover, const SDL_Rect & push, u1GUI * parent)
	: u1GUI(VERTICAL_SLIDER, x, y, parent, idle, true, true, true, true)
{

	background_rect = rect;
	idle_rect = idle;
	hover_rect = hover;
	push_rect = push;





}

u1VerticalSlider::~u1VerticalSlider()
{
}
