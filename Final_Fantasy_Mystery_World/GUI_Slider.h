#ifndef __GUI_SLIDER_H__
#define __GUI_SLIDER_H__

#include "GUI.h"
#include "GUI_Button.h"

class GUI_Button;

class GUI_Slider : public GUI
{
public:
	SDL_Rect slider_rect = { 0,0,0,0 };

private:
	uint value = 0u;
	GUI_Button* slider_btn = nullptr;
	bool horizontal = true;

public:
	GUI_Slider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, GUI* parent);
	~GUI_Slider();

	void SetButton(GUI_Button* slider_btn);
	void SetValue(int value);

	uint GetValue() const;
	GUI_Button* GetButton() const;

	bool Update(float dt);
	bool PostUpdate();
};
#endif //__!GUI_SLIDER_H__ 
