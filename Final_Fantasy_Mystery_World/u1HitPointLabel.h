#ifndef _U1HITPOINTLABEL_H_
#define _U1HITPOINTLABEL_H_

#include "u1UI_Element.h"

class u1HitPointLabel : public u1GUI {

public:

	u1HitPointLabel(const int &x, const int &y, const char* text, u1GUI* parent,const Color &color, const FontType &type);
	~u1HitPointLabel();
	void SetColor(const Color& c);

	void UpdateElement();
	void InnerDraw();

protected:

	FontType		id_font;
	SDL_Texture*	texture = nullptr;
	SDL_Color		color = { 255,255,255,255 };
	std::string		text;
	Color			color_type;
	float time = 0;
	int alpha = 255;
};



#endif // !_U1HITPOINTLABEL_H_

