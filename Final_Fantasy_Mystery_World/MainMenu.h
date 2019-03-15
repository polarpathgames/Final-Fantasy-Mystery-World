#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "j1Module.h"


struct SDL_Rect;
class GUI;

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

private:

	//SDL_Rect bck = { 0, 0, 480, 360 };
	GUI* background = nullptr;
};

#endif