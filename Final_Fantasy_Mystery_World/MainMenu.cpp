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
#include "GUI.h"
#include "Brofiler/Brofiler.h"

MainMenu::MainMenu(){}

MainMenu::~MainMenu(){}

bool MainMenu::Awake()
{
	return true;
}

bool MainMenu::Start()
{

	CreateMainMenu();


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
		App->map->ChangeMap(Maps::LOBBY);
		ret = false;
	}

	if (interaction == load_game_button) {
		App->LoadGame("save_game.xml");
	}

	if (interaction == credits_button) {
		CreateCredits();
		App->ui_manager->DeleteUIElement(background);
	}

	if (interaction == button_retun) {
		CreateMainMenu();
		DestroyCredits();
	}

	return ret;
}

void MainMenu::CreateMainMenu()
{
	background = App->ui_manager->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->ui_manager->screen, true, false, false,false);

	int offsetY = 75;

	new_game_button = App->ui_manager->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	new_game_label = App->ui_manager->AddLabel(0, 0, "New Game",  new_game_button, BLACK, FontType::FF64, nullptr,false);
	new_game_label->SetPosRespectParent(CENTERED);

	load_game_button = App->ui_manager->AddButton(684, new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	load_game_label = App->ui_manager->AddLabel(0, 0, "Load Game",  load_game_button, BLACK, FontType::FF64, nullptr,false);
	load_game_label->SetPosRespectParent(CENTERED);

	exit_button = App->ui_manager->AddButton(684, load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	exit_text = App->ui_manager->AddLabel(0, 0, "Exit", exit_button, BLACK, FontType::FF64, nullptr,false);
	exit_text->SetPosRespectParent(CENTERED);

	credits_button = App->ui_manager->AddButton(684, exit_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	credits_label = App->ui_manager->AddLabel(0, 0, "Credits",  credits_button, BLACK, FontType::FF64, nullptr,false);
	credits_label->SetPosRespectParent(CENTERED);
}

void MainMenu::CreateCredits()
{
	credits_panel = App->ui_manager->AddImage(0, 0, { 0, 768, 1024, 768 }, this, App->ui_manager->screen, true, false, false,false);
	credits_panel->SetPosRespectParent(CENTERED);
	button_retun = App->ui_manager->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true,true);
	button_retun->AddListener(this);
	label_return = App->ui_manager->AddLabel(0, 0, "Return",  button_retun, BLACK, FontType::FF32, nullptr,false);
	label_return->SetPosRespectParent(CENTERED);
}

void MainMenu::DestroyCredits()
{
	App->ui_manager->DeleteUIElement(credits_panel);
}

