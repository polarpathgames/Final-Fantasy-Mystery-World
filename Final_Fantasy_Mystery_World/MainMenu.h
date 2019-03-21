#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "j1Module.h"
#include <list>


struct SDL_Rect;
class GUI;
class GUI_Button;
class GUI_Label;

class MainMenu : public j1Module
{
public:
	MainMenu();
	~MainMenu();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	void Interact(GUI* interaction);

private:

	//SDL_Rect bck = { 0, 0, 480, 360 };
	GUI* background = nullptr;

	GUI_Button* exit_button = nullptr;
	GUI_Label* exit_text = nullptr;
	std::list<GUI*> labels;

	int mouse_x, mouse_y;

};

#endif