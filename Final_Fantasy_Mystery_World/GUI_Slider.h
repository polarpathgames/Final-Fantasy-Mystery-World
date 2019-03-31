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
	//GUI_Slider(iPoint pos, SDL_Rect rectangle, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, bool horizontal, SDL_Texture* texture = nullptr);
	~GUI_Slider();

	void SetButton(GUI_Button* slider_btn);
	void SetValue(int value);

	uint GetValue() const;
	GUI_Button* GetButton() const;

	bool Update(float dt);
	bool PostUpdate();
};
#endif //__!GUI_SLIDER_H__ 
