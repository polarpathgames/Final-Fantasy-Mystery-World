#include "MainMenu.h"
#include "j1Scene.h"
#include "j1App.h"
#include "j1Scene.h"
#include "EntityManager.h"
#include "j1Map.h"
#include "j1Input.h"
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
	if (first_update)
	{
	App->main_menu->Start();
	App->entity_manager->active = false;
	App->map->active = false;
	first_update = false;
	}

	if (App->main_menu->active == true)
	{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
	App->ui_manager->DestroyUI();
	active = false; //desactivates main menu
	App->entity_manager->active = true;
	App->map->active = true;
	}
	}

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

