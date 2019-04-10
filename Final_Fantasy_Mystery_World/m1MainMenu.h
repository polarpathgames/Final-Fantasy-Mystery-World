#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include <list>


struct SDL_Rect;
class u1GUI;
class u1Button;
class u1Label;
class u1Image;

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

	void CreateEndGame();
	void DestroyEndGame();

private:

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

	u1Button* exit_button = nullptr;
	u1Label* exit_text = nullptr;

	u1Button* button_retun = nullptr;
	u1Label* label_return = nullptr;

	u1Button* button_github = nullptr;
	u1Label* label_github = nullptr;
};

#endif