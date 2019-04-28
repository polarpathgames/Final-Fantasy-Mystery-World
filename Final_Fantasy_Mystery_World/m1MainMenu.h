#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include "SDL_mixer/include/SDL_mixer.h"

enum class MainMenuStates {
	MAIN_MENU,
	OPTIONS_MENU,
	CREDITS_MENU,
	SELECTION_MENU,
	CONTROLS_MENU,
	CHOOSE_NAME_MENU,

	NONE
};

class m1MainMenu : public m1Module
{
public:
	m1MainMenu();
	~m1MainMenu();

	bool Awake();
	bool Start();
	bool Update(float dt);

	bool Interact(u1GUI* interaction);

private:

	MainMenuStates main_states = MainMenuStates::NONE;

public:

	Mix_Chunk* fx_push_button;
	Mix_Chunk* fx_push_button_return;

	Mix_Music* mus_main_menu;
	Mix_Music* mus_credits;
	Mix_Music* mus_selection;

};
#endif