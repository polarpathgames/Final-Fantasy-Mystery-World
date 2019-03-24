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
#include "j1FadeToBlack.h"
#include "GUI_Label.h"
#include "GUI_Image.h"
#include "Brofiler/Brofiler.h"

MainMenu::MainMenu(){}

MainMenu::~MainMenu(){}

bool MainMenu::Awake()
{
	return true;
}

bool MainMenu::Start()
{
	background = App->ui_manager->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->ui_manager->screen, true, false, false);

	int offsetY = 75;

	new_game_button = App->ui_manager->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, true, false, true);
	new_game_label = App->ui_manager->AddLabel(0, 0, "New Game", 12, new_game_button, BLACK, "fonts/Munro.ttf", nullptr);
	new_game_label->SetPosRespectParent(CENTERED);

	load_game_button = App->ui_manager->AddButton(684, new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, true, false, true);
	load_game_label = App->ui_manager->AddLabel(0, 0, "Load Game", 12, load_game_button, BLACK, "fonts/Munro.ttf", nullptr);
	load_game_label->SetPosRespectParent(CENTERED);

	exit_button = App->ui_manager->AddButton(684, load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, true, false, true);
	exit_text = App->ui_manager->AddLabel(0, 0, "Exit", 20, exit_button, BLACK, "fonts/Munro.ttf", nullptr);
	exit_text->SetPosRespectParent(CENTERED);
	
	credits_button = App->ui_manager->AddButton(684, exit_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, true, false, true);
	credits_label = App->ui_manager->AddLabel(0, 0, "Credits", 12, credits_button, BLACK, "fonts/Munro.ttf", nullptr);
	credits_label->SetPosRespectParent(CENTERED);

	return true;
}

bool MainMenu::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateMainMenu", Profiler::Color::Orange);
	return true;
}

bool MainMenu::Update(float dt)
{
	BROFILER_CATEGORY("UpdateMainMenu", Profiler::Color::Aqua);
	return true;
}

bool MainMenu::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateMainMenu", Profiler::Color::Purple);
	return true;
}

bool MainMenu::CleanUp()
{
	return true;
}

bool MainMenu::Interact(GUI* interaction)
{
	bool ret = true;
	if (interaction == exit_button) {
		App->QuitGame();
		ret = false;
	}

	if (interaction == new_game_button) {
		App->ui_manager->DeleteAllUIElements();
		active = false; //desactivates main menu
		App->entity_manager->Enable();
		App->map->Enable();
		App->scene->Enable();
		App->map->ChangeMap(Maps::TUTORIAL);
		ret = false;
	}

	if (interaction == load_game_button) {
		//Load Game
	}

	if (interaction == credits_button) {
		//Credits
	}
	return ret;
}

