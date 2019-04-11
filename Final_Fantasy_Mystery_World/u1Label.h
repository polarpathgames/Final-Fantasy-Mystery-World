#ifndef _u1Label_H__ 
#define _u1Label_H__

#include "u1UI_Element.h"
#include "m1Fonts.h"
#include <string>

class u1Label : public u1GUI
{
private:
	SDL_Rect img_normal;

public:
	u1Label() : u1GUI(LABEL, 0, 0, nullptr, { 0,0,0,0 }) {	}
	u1Label(const int & pos_x, const int & pos_y, const char* txt, const Color &c, FontType font, u1GUI* parent = nullptr,
		bool interactable = false, bool draggable = false, uint32 wrap_length = 0, bool focus = false,
		bool has_background = false, const SDL_Color& bg_color = { 255,255,255,255 });
	~u1Label();

	void InnerDraw();

	void SetText(const char* txt);

	void SetColor(const Color& c);

	void SetColor(const SDL_Color &c);

	std::string GetText();

	void ChangeFont(const char* f, const int &size);

protected:

	FontType		id_font;
	SDL_Texture*	texture = nullptr;
	SDL_Color		color = { 255,255,255,255 };
	std::string		text;
	bool			has_background = false;
	SDL_Color		background_color = { 255,255,255,255 };
};
#endif //_u1Label_H_