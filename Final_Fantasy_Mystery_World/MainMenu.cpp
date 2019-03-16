#include "MainMenu.h"
#include "j1Scene.h"
#include "j1App.h"
#include "j1UIManager.h"
#include "GUI_Image.h"

MainMenu::MainMenu(){}

MainMenu::~MainMenu(){}

bool MainMenu::Awake()
{
	return true;
}

bool MainMenu::Start()
{
	SDL_Rect background_rect = { 0, 0, 1024, 768 };
	background = App->ui_manager->AddImage(0, 0, &background_rect, nullptr, this, nullptr);


	return true;
}

bool MainMenu::PreUpdate()
{
	return true;
}

bool MainMenu::Update(float dt)
{
	return true;
}

bool MainMenu::PostUpdate()
{
	return true;
}

bool MainMenu::CleanUp()
{
	return true;
}

