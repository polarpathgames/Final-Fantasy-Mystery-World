#ifndef _U1INPUTTEXT_H_
#define _U1INPUTTEXT_H_

#include "u1UI_Element.h"
#include "m1GUI.h"

class u1InputText : public u1GUI {

public:

	u1InputText(const int & pos_x, const int & pos_y, const char* txt, const Color &c, FontType font, u1GUI* parent = nullptr,
		bool interactable = false, bool draggable = false, uint32 wrap_length = 0, bool focus = false,
		bool has_background = false, const SDL_Color& bg_color = { 255,255,255,255 });
	~u1InputText();

	void InnerDraw();

	void SetText(const char* txt);
	void SetTextWrapped(const char * txt);

	void SetColor(const Color& c);

	void SetColor(const SDL_Color &c);

	std::string GetText();

	void ChangeFont(const char* f, const int &size);

protected:

	FontType		id_font;
	SDL_Texture*	texture = nullptr;
	SDL_Color		color = { 255,255,255,255 };
	std::string		text;
	uint32			wrap = 0U;
	bool			has_background = false;
	SDL_Color		background_color = { 255,255,255,255 };

};







#endif // _U1INPUTTEXT_H_
