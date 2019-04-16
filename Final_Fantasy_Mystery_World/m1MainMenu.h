#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include <list>


struct SDL_Rect;
class u1GUI;
class u1Button;
class u1Label;
class u1Image;


enum class MainMenuStates {
	MAIN_MENU,
	OPTIONS_MENU,
	CREDITS_MENU,
	SELECTION_MENU,
	CONTROLS_MENU,

	NONE
};

class m1MainMenu : public m1Module
{
public:
	m1MainMenu();
	~m1MainMenu();

	bool Awake();
	bool Start();
	void CreateMainMenu();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Interact(u1GUI* interaction);

	void CreateCredits();
	void DestroyCredits();

	
	void CreateGameOver();
	void DestroyGameOver();

	void CreateSelectChamp();
	void DestroySelectChamp();

	void SetMainMenuState(const MainMenuStates &state);

	void DestroyMainMenu();

private:

	MainMenuStates main_states = MainMenuStates::NONE;

	u1GUI* background = nullptr;

	u1Button* new_game_button = nullptr;
	u1Label* new_game_label = nullptr;

	u1Button* load_game_button = nullptr;
	u1Label* load_game_label = nullptr;

	u1Button* options_button = nullptr;
	u1Label* options_label = nullptr;

	u1Button* credits_button = nullptr;
	u1Label* credits_label = nullptr;
	u1Image* credits_panel = nullptr;

	u1Button* button_christian = nullptr;
	u1Label* label_christian = nullptr;
	u1Button* button_lluis = nullptr;
	u1Label* label_lluis = nullptr;
	u1Button* button_marc = nullptr;
	u1Label* label_marc = nullptr;
	u1Button* button_enric = nullptr;
	u1Label* label_enric = nullptr;
	u1Button* button_nadine = nullptr;
	u1Label* label_nadine = nullptr;
	u1Button* button_ivan = nullptr;
	u1Label* label_ivan = nullptr;
	u1Button* button_oriol = nullptr;
	u1Label* label_oriol = nullptr;

	u1Button* exit_button = nullptr;
	u1Label* exit_text = nullptr;

	u1Button* button_retun = nullptr;
	u1Label* label_return = nullptr;

	u1Button* button_github = nullptr;
	u1Label* label_github = nullptr;

	u1Button* button_twitter = nullptr;
	u1Label* label_twitter = nullptr;
	
	u1Button* button_youtube = nullptr;
	u1Label* label_youtube = nullptr;

	u1Image* game_over_panel = nullptr;

	u1Button* button_continue_lobby = nullptr;
	u1Label* label_continue_lobby = nullptr; 
	
	u1Button* button_return_main = nullptr;
	u1Label* label_continue_main = nullptr;
	
	u1Button* button_warrior = nullptr;
	u1Button* button_archer = nullptr;
	u1Button* button_mage = nullptr;
};

#endif