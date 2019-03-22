#include "MainMenu.h"
#include "j1Scene.h"
#include "j1App.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1UIManager.h"
#include "j1Map.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
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
	background = App->ui_manager->AddImage(0, 0, &background_rect, this, nullptr);

	exit_button = (GUI_Button*)App->ui_manager->AddButton(350, 300, {1659, 1575,33,33}, { 0, 0,100,100 }, { 0, 0,10,10 }, this, nullptr);
	//exit_text = (GUI_Label*)App->ui_manager->AddLabel(10, 10, "exit", this, exit_button);
	//exit_button->SetText(exit_text);

	new_game_button = (GUI_Button*)App->ui_manager->AddButton(0, 0, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, nullptr);
	new_game_label = (GUI_Label*)App->ui_manager->AddLabel(0, 0, std::string("New Game"), nullptr, nullptr);
	new_game_button->SetText(new_game_label);

	//labels.push_back(exit_text);

	App->map->active = false;
	App->scene->active = false;
	App->entity_manager->active = false;


	return true;
}

bool MainMenu::PreUpdate()
{
	return true;
}

bool MainMenu::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
	App->ui_manager->DestroyUI();
	active = false; //desactivates main menu
	App->entity_manager->active = true;
	App->map->active = true;
	App->scene->active = true;
	App->map->ChangeMap(Maps::TUTORIAL);
	App->scene->CreateEntities();
	}
	

	App->input->GetMousePosition(mouse_x, mouse_y);

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

void MainMenu::Interact(GUI* interaction)
{
	if (interaction == exit_button)
		App->ui_manager->DestroyUI();
}

