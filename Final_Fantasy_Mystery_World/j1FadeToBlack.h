#ifndef __J1FADETOBLACK_H__
#define __J1FADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"


enum class Maps;

class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack();
	~j1FadeToBlack();

	bool Start();
	bool Update(float dt);
	bool FadeToBlack(j1Module* module_off, j1Module* module_on , float time = 1.0f);
	bool FadeToBlack(j1Module* module_off,  float time = 1.0f);
	bool FadeToBlack(float time, j1Module* module_on);
	bool FadeToBlack(float time);
	bool FadeToBlack(Maps type, float time = 1.0f);
	bool FadeToBlack(j1Module* module_off, Maps type, float time = 1.0f);
	bool IsFading() const;

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

private:

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	j1Module* to_enable = nullptr;
	j1Module* to_disable = nullptr;
	
	Maps map_to_change;
	bool want_to_change_map = false;
};

#endif