#ifndef __u1Slider_H__
#define __u1Slider_H__

#include "u1UI_Element.h"
#include "u1Button.h"

class u1Button;

class u1Slider : public u1GUI
{
public:
	SDL_Rect slider_rect = { 0,0,0,0 };

private:
	uint value = 0u;
	u1Button* slider_btn = nullptr;
	bool horizontal = true;

public:
	u1Slider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, u1GUI* parent);
	~u1Slider();

	void SetButton(u1Button* slider_btn);
	void SetValue(int value);

	uint GetValue() const;
	u1Button* GetButton() const;

	bool Update(float dt);
	bool PostUpdate();
};
#endif //__!u1Slider_H__ 
