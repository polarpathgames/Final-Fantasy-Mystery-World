#include "m1MainMenu.h"
#include "m1Scene.h"
#include "App.h"
#include "m1Scene.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Input.h"
#include "p2Log.h"
#include "m1GUI.h"
#include "u1InputText.h"
#include "m1Map.h"
#include "u1Button.h"
#include "m1FadeToBlack.h"
#include "u1Label.h"
#include "u1CheckBox.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "u1Image.h"
#include "u1ChButton.h"
#include "u1UI_Element.h"
#include "Brofiler/Brofiler.h"
#include <shellapi.h>
#include "m1Audio.h"
#include "m1Window.h"
#include "m1MenuManager.h"

m1MainMenu::m1MainMenu()
{
	name.assign("main_menu");
}

m1MainMenu::~m1MainMenu(){}

bool m1MainMenu::Awake()
{
	return true;
}

bool m1MainMenu::Start()
{
	
	fx_push_button = App->audio->LoadFx("assets/audio/sfx/MainMenu_Confirm_Selection.wav");
	fx_push_button_return = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Message.wav");

	mus_main_menu = App->audio->LoadMusic("assets/audio/music/1.Final Fantasy TA - Main Theme.ogg");
	mus_credits = App->audio->LoadMusic("assets/audio/music/41.Final Fantasy TA - A Place We Should Return To.ogg");
	mus_selection = App->audio->LoadMusic("assets/audio/music/34.Final Fantasy TA - Confusion.ogg");

	App->menu_manager->CreateMainMenu();
	App->audio->PlayMusic(mus_main_menu, 5);

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

bool m1MainMenu::Interact(u1GUI* interaction)
{
	bool ret = true;


	if (interaction == App->menu_manager->main_menu.new_game_button) {
		App->audio->PlayFx(fx_push_button_return);
		App->menu_manager->CreateSelectChamp();
		App->menu_manager->DestroyMainMenu();
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.exit_game_button) {
		App->QuitGame();
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.credits_button) {
		App->menu_manager->CreateCredits();
		App->menu_manager->DestroyMainMenu();
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.options_button) {
		App->menu_manager->CreateOptions();
		App->menu_manager->DestroyMainMenu();
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.load_game_button) {
		App->menu_manager->DestroyMainMenu();
		active = false;
		App->entity_manager->Enable();
		App->map->Enable();
		App->scene->Enable();
		App->map->ChangeMap(Maps::HOME);
		App->scene->SetMenuState(StatesMenu::NO_MENU);
		App->LoadGame("save_game.xml");
		//App->scene->CreateHUD();
		ret = false;
	}

	// SELECT NAME ==============================================================================

	else if (interaction == App->menu_manager->input.button_okay) {
		if (!App->menu_manager->input.input_text->GetText().empty()) {
			App->globals.Reset();
			App->globals.player_name = App->menu_manager->input.input_text->GetText();
			App->menu_manager->DestroyNameMenu();
			active = false;
			App->entity_manager->Enable();
			App->map->Enable();
			App->scene->Enable();
			App->map->ChangeMap(Maps::TUTORIAL);
			App->scene->player->Init();
			App->scene->player->CenterPlayerInTile();
			App->render->CenterCameraOnPlayer(App->scene->player->position);
			App->scene->CreateHUD();
			App->scene->SetMenuState(StatesMenu::NO_MENU);
			ret = false;
		}
	}
	else {
		App->menu_manager->ManageInputText(interaction);
	}

	// SELECT PLAYER ==============================================================================================

	if (interaction == App->menu_manager->select_champ.button_warrior) {
		App->scene->player_type = PlayerType::WARRIOR;
		App->menu_manager->CreateNameMenu();
		App->menu_manager->DestroySelectChamp();
		entity_type = e1Entity::EntityType::WARRIOR;
		App->scene->player = (e1Player*)App->entity_manager->CreateEntity(entity_type, -100, -100, "warrior");
		ret = false;
	}
	else if (interaction == App->menu_manager->select_champ.button_archer) {
		App->scene->player_type = PlayerType::ARCHER;
		App->menu_manager->CreateNameMenu();
		App->menu_manager->DestroySelectChamp();
		entity_type = e1Entity::EntityType::ARCHER;
		App->scene->player = (e1Player*)App->entity_manager->CreateEntity(entity_type, -100, -100, "archer");
		ret = false;
	}
	else if (interaction == App->menu_manager->select_champ.button_mage) {
		App->scene->player_type = PlayerType::MAGE;
		App->menu_manager->CreateNameMenu();
		App->menu_manager->DestroySelectChamp();
		entity_type = e1Entity::EntityType::MAGE;
		App->scene->player = (e1Player*)App->entity_manager->CreateEntity(entity_type, -100, -100, "mage");
		ret = false;
	}

	else if (interaction == App->menu_manager->select_champ.return_select_champ_button) {
		App->menu_manager->CreateMainMenu();
		App->menu_manager->DestroySelectChamp();
		App->audio->PlayFx(fx_push_button_return);
		ret = false;
	}

	// Credits ============================================================================================================

	else if (interaction == App->menu_manager->credits.button_github) {
		ShellExecuteA(NULL, "open", "https://github.com/polarpathgames", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_youtube) {
		ShellExecuteA(NULL, "open", "https://www.youtube.com/channel/UCx2jJZu3o-egIp2R8nH6vuA", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_twitter) {
		ShellExecuteA(NULL, "open", "https://twitter.com/polarpathgames", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_christian) {
		ShellExecuteA(NULL, "open", "https://github.com/christt105", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_lluis) {
		ShellExecuteA(NULL, "open", "https://github.com/youis11", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_marc) {
		ShellExecuteA(NULL, "open", "https://github.com/optus23", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_enric) {
		ShellExecuteA(NULL, "open", "https://github.com/PerezEnric", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_oriol) {
		ShellExecuteA(NULL, "open", "https://github.com/OriolCS2", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_nadine) {
		ShellExecuteA(NULL, "open", "https://github.com/Nadine044", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_ivan) {
		ShellExecuteA(NULL, "open", "https://github.com/RoperoIvan", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (interaction == App->menu_manager->credits.button_credits_return_menu) {
		App->audio->PlayFx(fx_push_button_return);
		App->menu_manager->CreateMainMenu();
		App->menu_manager->DestroyCredits();
		ret = false;
	}


	/*if (interaction != nullptr && interaction != button_credits_return_menu && interaction != new_game_button && interaction != button_retun_to_options && interaction != button_retun_options && interaction != button_warrior && interaction != button_mage && interaction != button_archer)
		App->audio->PlayFx(fx_push_button);*/ // Create var in buttons to sound specific fx when click
	return ret;
}