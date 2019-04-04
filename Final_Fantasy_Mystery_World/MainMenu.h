#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "j1Module.h"
#include <list>


struct SDL_Rect;
class GUI;
class GUI_Button;
class GUI_Label;
class GUI_Image;

class MainMenu : public j1Module
{
public:
	MainMenu();
	~MainMenu();

	bool Awake();
	bool Start();
	void CreateMainMenu();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Interact(GUI* interaction);

	void CreateCredits();
	void DestroyCredits();

private:

	GUI* background = nullptr;

	GUI_Button* new_game_button = nullptr;
	GUI_Label* new_game_label = nullptr;

	GUI_Button* load_game_button = nullptr;
	GUI_Label* load_game_label = nullptr;

	GUI_Button* options_button = nullptr;
	GUI_Label* options_label = nullptr;

	GUI_Button* credits_button = nullptr;
	GUI_Label* credits_label = nullptr;
	GUI_Image* credits_panel = nullptr;

	GUI_Button* exit_button = nullptr;
	GUI_Label* exit_text = nullptr;

	GUI_Button* button_retun = nullptr;
	GUI_Label* label_return = nullptr;
};

#endif