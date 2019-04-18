#ifndef _U1INPUTTEXT_H_
#define _U1INPUTTEXT_H_

#define MAX_CHARACTERS 10

#include "u1UI_Element.h"
#include "m1GUI.h"

class u1Image;

class u1InputText : public u1GUI {

public:

	u1InputText(const int & pos_x, const int & pos_y, const char* txt, const Color &c, FontType font, u1GUI* parent = nullptr,
		bool interactable = false, bool draggable = false, bool focus = false,
		bool has_background = false, const SDL_Color& bg_color = { 255,255,255,255 });
	~u1InputText();

	void UpdateElement();
	void InnerDraw();

	void SetText(const char* txt);

	void SetColor(const Color& c);

	void SetColor(const SDL_Color &c);

	std::string GetText();

	void ChangeFont(const char* f, const int &size);

private:
	void AddText(const char* txt);
	void DeleteText();

protected:

	FontType		id_font;
	SDL_Texture*	texture = nullptr;
	SDL_Color		color = { 255,255,255,255 };
	std::string		text;
	uint32			wrap = 0U;
	bool			has_background = false;
	SDL_Color		background_color = { 255,255,255,255 };
	SDL_Rect		input_box{ 0,0,0,0 };
	bool			first_update = true;


};







#endif // _U1INPUTTEXT_H_