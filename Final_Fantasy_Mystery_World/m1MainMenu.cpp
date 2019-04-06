#include "m1MainMenu.h"
#include "m1Scene.h"
#include "App.h"
#include "m1Scene.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1Input.h"
#include "m1GUI.h"
#include "m1Map.h"
#include "u1Button.h"
#include "m1FadeToBlack.h"
#include "u1Label.h"
#include "u1Image.h"
#include "u1UI_Element.h"
#include "Brofiler/Brofiler.h"

m1MainMenu::m1MainMenu(){}

m1MainMenu::~m1MainMenu(){}

bool m1MainMenu::Awake()
{
	return true;
}

bool m1MainMenu::Start()
{

	CreateMainMenu();


	return true;
}

bool m1MainMenu::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateMainMenu", Profiler::Color::Orange);
	return true;
}

bool m1MainMenu::Update(float dt)
{
	BROFILER_CATEGORY("UpdateMainMenu", Profiler::Color::Aqua);
	return true;
}

bool m1MainMenu::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateMainMenu", Profiler::Color::Purple);
	return true;
}

bool m1MainMenu::CleanUp()
{
	return true;
}

bool m1MainMenu::Interact(u1GUI* interaction)
{
	bool ret = true;
	if (interaction == exit_button) {
		app->QuitGame();
		ret = false;
	}

	if (interaction == new_game_button) {
		app->gui->DeleteAllUIElements();
		active = false; //desactivates main menu
		app->entity_manager->Enable();
		app->map->Enable();
		app->scene->Enable();
		app->map->ChangeMap(Maps::LOBBY);
		ret = false;
	}

	if (interaction == load_game_button) {
		app->LoadGame("save_game.xml");
	}

	if (interaction == options_button) {
		app->scene->CreateOptionsMenu();
		app->gui->DeleteUIElement(background);
	}

	if (interaction == credits_button) {
		CreateCredits();
		app->gui->DeleteUIElement(background);
	}

	if (interaction == button_retun) {
		CreateMainMenu();
		DestroyCredits();
	}

	return ret;
}

void m1MainMenu::CreateMainMenu()
{
	background = app->gui->AddImage(0, 0, { 0, 0, 1024, 768 }, this, app->gui->screen, true, false, false,false);

	int offsetY = 75;

	new_game_button = app->gui->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	new_game_label = app->gui->AddLabel(0, 0, "New Game",  new_game_button, BLACK, FontType::FF64, nullptr,false);
	new_game_label->SetPosRespectParent(CENTERED);

	load_game_button = app->gui->AddButton(684, new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	load_game_label = app->gui->AddLabel(0, 0, "Load Game",  load_game_button, BLACK, FontType::FF64, nullptr,false);
	load_game_label->SetPosRespectParent(CENTERED);

	options_button = app->gui->AddButton(684, load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	options_label = app->gui->AddLabel(0, 0, "Options", options_button, BLACK, FontType::FF64, nullptr, false);
	options_label->SetPosRespectParent(CENTERED);

	credits_button = app->gui->AddButton(684, options_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	credits_label = app->gui->AddLabel(0, 0, "Credits",  credits_button, BLACK, FontType::FF64, nullptr,false);
	credits_label->SetPosRespectParent(CENTERED);

	exit_button = app->gui->AddButton(684, credits_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	exit_text = app->gui->AddLabel(0, 0, "Exit", exit_button, BLACK, FontType::FF64, nullptr, false);
	exit_text->SetPosRespectParent(CENTERED);
}

void m1MainMenu::CreateCredits()
{
	credits_panel = app->gui->AddImage(0, 0, { 0, 768, 1024, 768 }, this, app->gui->screen, true, false, false,false);
	credits_panel->SetPosRespectParent(CENTERED);
	button_retun = app->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true,true);
	button_retun->AddListener(this);
	label_return = app->gui->AddLabel(0, 0, "Return",  button_retun, BLACK, FontType::FF32, nullptr,false);
	label_return->SetPosRespectParent(CENTERED);
}

void m1MainMenu::DestroyCredits()
{
	app->gui->DeleteUIElement(credits_panel);
}

