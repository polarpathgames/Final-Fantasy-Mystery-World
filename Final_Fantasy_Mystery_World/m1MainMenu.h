#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include <list>
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Rect;
class u1GUI;
class u1Button;
class u1Label;
class u1CheckBox;
class u1Image;
class u1ChButton;
class u1InputText;
class e1Player;

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
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Interact(u1GUI* interaction);

	void SetMainMenuState(const MainMenuStates &state);

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