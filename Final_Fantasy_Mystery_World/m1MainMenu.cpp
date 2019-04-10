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
#include <windows.h>


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
	if (App->scene->control_to_change != nullptr && !App->scene->control_to_change->Update()) {
		delete App->scene->control_to_change;
		App->scene->control_to_change = nullptr;
	}
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
		App->QuitGame();
		ret = false;
	}

	if (interaction == new_game_button) {
		App->gui->DeleteAllUIElements();
		active = false; //desactivates main menu
		App->entity_manager->Enable();
		App->map->Enable();
		App->scene->Enable();
		App->map->ChangeMap(Maps::LOBBY);
		App->scene->SetMenuState(StatesMenu::NO_MENU);
		ret = false;
	}

	if (interaction == load_game_button) {
		App->LoadGame("save_game.xml");
	}

	if (interaction == options_button) {
		App->scene->CreateOptionsMenu();
		App->gui->DeleteUIElement(background);
	}

	if (interaction == credits_button) {
		CreateCredits();
		App->gui->DeleteUIElement(background);
	}

	if (interaction == button_retun) {
		CreateMainMenu();
		DestroyCredits();
	}

	if (interaction == button_github) {
		ShellExecuteA(NULL, "open", "https://github.com/polarpathgames", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_youtube) {
		ShellExecuteA(NULL, "open", "https://www.youtube.com/channel/UCx2jJZu3o-egIp2R8nH6vuA", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_twitter) {
		ShellExecuteA(NULL, "open", "https://twitter.com/polarpathgames", NULL, NULL, SW_SHOWNORMAL);
	}

	if (interaction == button_christian) {
		ShellExecuteA(NULL, "open", "https://github.com/christt105", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_lluis) {
		ShellExecuteA(NULL, "open", "https://github.com/youis11", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_marc) {
		ShellExecuteA(NULL, "open", "https://github.com/optus23", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_enric) {
		ShellExecuteA(NULL, "open", "https://github.com/PerezEnric", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_oriol) {
		ShellExecuteA(NULL, "open", "https://github.com/OriolCS2", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_nadine) {
		ShellExecuteA(NULL, "open", "https://github.com/Nadine044", NULL, NULL, SW_SHOWNORMAL);
	}
	if (interaction == button_ivan) {
		ShellExecuteA(NULL, "open", "https://github.com/RoperoIvan", NULL, NULL, SW_SHOWNORMAL);
	}
	return ret;
}

void m1MainMenu::CreateMainMenu()
{
	background = App->gui->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->gui->screen, true, false, false,false);

	int offsetY = 75;

	new_game_button = App->gui->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	new_game_label = App->gui->AddLabel(0, 0, "New Game",  new_game_button, BLACK, FontType::FF64, nullptr,false);
	new_game_label->SetPosRespectParent(CENTERED);

	load_game_button = App->gui->AddButton(684, new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	load_game_label = App->gui->AddLabel(0, 0, "Load Game",  load_game_button, BLACK, FontType::FF64, nullptr,false);
	load_game_label->SetPosRespectParent(CENTERED);

	options_button = App->gui->AddButton(684, load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	options_label = App->gui->AddLabel(0, 0, "Options", options_button, BLACK, FontType::FF64, nullptr, false);
	options_label->SetPosRespectParent(CENTERED);

	credits_button = App->gui->AddButton(684, options_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true,true);
	credits_label = App->gui->AddLabel(0, 0, "Credits",  credits_button, BLACK, FontType::FF64, nullptr,false);
	credits_label->SetPosRespectParent(CENTERED);

	exit_button = App->gui->AddButton(684, credits_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, background, false, false, true, true);
	exit_text = App->gui->AddLabel(0, 0, "Exit", exit_button, BLACK, FontType::FF64, nullptr, false);
	exit_text->SetPosRespectParent(CENTERED);
}

void m1MainMenu::CreateCredits()
{
	credits_panel = App->gui->AddImage(0, 0, { 0, 2304, 1024, 768 }, this, App->gui->screen, true, false, false,false);
	credits_panel->SetPosRespectParent(CENTERED);

	button_christian = App->gui->AddButton(325, 290, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_christian = App->gui->AddLabel(0, 0, "Christian Martinez - Lead", button_christian, WHITE, FontType::FF100, nullptr, false);
	label_christian->SetPosRespectParent(LEFT_CENTERED);

	button_lluis = App->gui->AddButton(85, 350, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_lluis = App->gui->AddLabel(0, 0, "Lluis Moreu - Manager", button_lluis, WHITE, FontType::FF100, nullptr, false);
	label_lluis->SetPosRespectParent(LEFT_CENTERED);

	button_marc = App->gui->AddButton(85, 400, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_marc = App->gui->AddLabel(0, 0, "Marc Galvez - Design", button_marc, WHITE, FontType::FF100, nullptr, false);
	label_marc->SetPosRespectParent(LEFT_CENTERED);

	button_enric = App->gui->AddButton(85, 450, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_enric = App->gui->AddLabel(0, 0, "Enric Perez - UI", button_enric, WHITE, FontType::FF100, nullptr, false);
	label_enric->SetPosRespectParent(LEFT_CENTERED);

	button_oriol = App->gui->AddButton(555, 350, { 1850,1637,350,50 }, { 1850,1637,1980,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_oriol = App->gui->AddLabel(0, 0, "Oriol Capdevila - Code", button_oriol, WHITE, FontType::FF100, nullptr, false);
	label_oriol->SetPosRespectParent(LEFT_CENTERED);

	button_nadine = App->gui->AddButton(555, 400, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_nadine  = App->gui->AddLabel(0, 0, "Nadine Gutierrez - Art", button_nadine, WHITE, FontType::FF100, nullptr, false);
	label_nadine->SetPosRespectParent(LEFT_CENTERED);

	button_ivan = App->gui->AddButton(555, 450, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_ivan = App->gui->AddLabel(0, 0, "Ivan Ropero - QA", button_ivan, WHITE, FontType::FF100, nullptr, false);
	label_ivan->SetPosRespectParent(LEFT_CENTERED);

	button_retun = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true,true);
	label_return = App->gui->AddLabel(0, 0, "Return",  button_retun, WHITE, FontType::FF64, nullptr,false);
	label_return->SetPosRespectParent(CENTERED);

	button_github = App->gui->AddButton(710, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_github = App->gui->AddLabel(0, 0, ".", button_github, WHITE, FontType::FF32, nullptr, false);
	label_github->SetPosRespectParent(CENTERED);

	button_twitter = App->gui->AddButton(410, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_twitter = App->gui->AddLabel(0, 0, ".", button_twitter, WHITE, FontType::FF32, nullptr, false);
	label_twitter->SetPosRespectParent(CENTERED);

	button_youtube = App->gui->AddButton(110, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_youtube = App->gui->AddLabel(0, 0, ".", button_youtube, WHITE, FontType::FF32, nullptr, false);
	label_youtube->SetPosRespectParent(CENTERED);
}

void m1MainMenu::DestroyCredits()
{
	App->gui->DeleteUIElement(credits_panel);
}

void m1MainMenu::CreateEndGame()
{
	end_game_panel = App->gui->AddImage(0, 0, { 0, 768, 1024, 768 }, this, App->gui->screen, true, false, false, false);
	end_game_panel->SetPosRespectParent(CENTERED);

	button_retun = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, end_game_panel, false, false, true, true);
	label_return = App->gui->AddLabel(0, 0, "Return", button_retun, BLACK, FontType::FF32, nullptr, false);
	label_return->SetPosRespectParent(CENTERED);

	button_github = App->gui->AddButton(110, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, end_game_panel, false, false, true, true);
	label_github = App->gui->AddLabel(0, 0, "Github", button_github, BLACK, FontType::FF32, nullptr, false);
	label_github->SetPosRespectParent(CENTERED);
}

void m1MainMenu::DestroyEndGame()
{
	App->gui->DeleteUIElement(end_game_panel);
}

