#include "m1MainMenu.h"
#include "m1Scene.h"
#include "App.h"
#include "m1Scene.h"
#include "m1EntityManager.h"
#include "m1Map.h"
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
#include <windows.h>
#include "m1Audio.h"
#include "m1Window.h"

m1MainMenu::m1MainMenu(){}

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
	CreateMainMenu();
	main_states = MainMenuStates::MAIN_MENU;
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

	App->audio->UnLoadFx(fx_push_button);
	App->audio->UnLoadFx(fx_push_button_return);
	App->audio->UnLoadMusic(mus_credits);
	App->audio->UnLoadMusic(mus_main_menu);
	App->audio->UnLoadMusic(mus_selection);

	return true;
}

bool m1MainMenu::Interact(u1GUI* interaction)
{
	bool ret = true;

	switch (main_states) {
	case MainMenuStates::MAIN_MENU:
		if (interaction == new_game_button) {
			App->audio->PlayFx(fx_push_button_return);
			CreateSelectChamp();
			DestroyMainMenu();
			main_states = MainMenuStates::SELECTION_MENU;
			ret = false;
		}
		if (interaction == exit_button) {
			App->QuitGame();
			ret = false;
		}
		if (interaction == credits_button) {
			CreateCredits();
			DestroyMainMenu();
			main_states = MainMenuStates::CREDITS_MENU;
			ret = false;
		}
		if (interaction == options_button) {
			CreateOptions();
			DestroyMainMenu();
			main_states = MainMenuStates::OPTIONS_MENU;
			ret = false;
		}
		if (interaction == load_game_button) {
			App->LoadGame("save_game.xml");
			ret = false;
		}
		break;
	case MainMenuStates::CONTROLS_MENU:
		if (interaction == button_retun_to_options) {
			App->audio->PlayFx(fx_push_button_return);
			CreateOptions();
			DestroyControls();
			main_states = MainMenuStates::OPTIONS_MENU;
			ret = false;
		}
		if (interaction == button_up) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_up, &App->input->keyboard_buttons.buttons_code.UP, &App->input->keyboard_buttons.buttons_char.UP, false);
		}
		if (interaction == button_right) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_right, &App->input->keyboard_buttons.buttons_code.RIGHT, &App->input->keyboard_buttons.buttons_char.RIGHT, false);
		}
		if (interaction == button_left) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_left, &App->input->keyboard_buttons.buttons_code.LEFT, &App->input->keyboard_buttons.buttons_char.LEFT, false);
		}
		if (interaction == button_down) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_down, &App->input->keyboard_buttons.buttons_code.DOWN, &App->input->keyboard_buttons.buttons_char.DOWN, false);
		}
		if (interaction == button_diagonals) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_diagonals, &App->input->keyboard_buttons.buttons_code.DIAGONALS, &App->input->keyboard_buttons.buttons_char.DIAGONALS, false);
		}
		if (interaction == button_direction_up) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_up, &App->input->keyboard_buttons.buttons_code.DIRECTION_UP, &App->input->keyboard_buttons.buttons_char.DIRECTION_UP, false);
		}
		if (interaction == button_direction_right) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_right, &App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT, &App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, false);
		}
		if (interaction == button_direction_left) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_left, &App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT, &App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, false);
		}
		if (interaction == button_direction_down) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_down, &App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN, &App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, false);
		}
		if (interaction == button_basic_attack) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_basic_attack, &App->input->keyboard_buttons.buttons_code.BASIC_ATTACK, &App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, false);
		}
		if (interaction == Cbutton_direction_up) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_up, &App->input->controller_Buttons.buttons_code.DIRECTION_UP, &App->input->controller_Buttons.buttons_char.DIRECTION_UP, true);
		}
		if (interaction == Cbutton_direction_right) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_right, &App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT, &App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, true);
		}
		if (interaction == Cbutton_direction_left) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_left, &App->input->controller_Buttons.buttons_code.DIRECTION_LEFT, &App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, true);
		}
		if (interaction == Cbutton_direction_down) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_down, &App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN, &App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, true);
		}
		if (interaction == Cbutton_diagonals) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_diagonals, &App->input->controller_Buttons.buttons_code.DIAGONALS, &App->input->controller_Buttons.buttons_char.DIAGONALS, true);
		}
		if (interaction == Cbutton_basic_attack) {
			if (App->scene->control_to_change != nullptr)
				delete App->scene->control_to_change;
			App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_basic_attack, &App->input->controller_Buttons.buttons_code.BASIC_ATTACK, &App->input->controller_Buttons.buttons_char.BASIC_ATTACK, true);
		}
		break;
	case MainMenuStates::CHOOSE_NAME_MENU:
		if (interaction == button_okay) {
			if (!input_text->GetText().empty()) {
				App->globals.player_name = input_text->GetText();
				DestroyNameMenu();
				active = false;
				App->entity_manager->Enable();
				App->map->Enable();
				App->scene->Enable();
				//App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
				App->map->ChangeMap(Maps::LOBBY);
				App->scene->SetMenuState(StatesMenu::NO_MENU);
				ret = false;
			}
		}
		break;
	case MainMenuStates::SELECTION_MENU:
		if (interaction == button_warrior) {
			App->scene->player_type = PlayerType::WARRIOR;
			CreateNameMenu();
			DestroySelectChamp();
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}
		if (interaction == button_archer) {
			App->scene->player_type = PlayerType::ARCHER;
			CreateNameMenu();
			DestroySelectChamp();
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}
		if (interaction == button_mage) {
			App->scene->player_type = PlayerType::MAGE;
			CreateNameMenu();
			DestroySelectChamp();
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}
		App->audio->PlayFx(fx_push_button_return);

		break;
	case MainMenuStates::OPTIONS_MENU:
		if (interaction == button_retun_options) {
			App->audio->PlayFx(App->main_menu->fx_push_button_return);
			CreateMainMenu();
			DestroyOptions();
			main_states = MainMenuStates::MAIN_MENU;
			ret = false;
		}
		if (interaction == button_controls) {
			CreateControls();
			DestroyOptions();
			main_states = MainMenuStates::CONTROLS_MENU;
			ret = false;
		}
		if (interaction == checkbox_fps)
		{
			checkbox_fps->Clicked();
			if (App->capactivated) {
				App->capactivated = false;
			}
			else {
				App->capactivated = true;
			}
			//App->GetFrameRate();
		}
		
		if (interaction == checkbox_fullscreen)
		{
			checkbox_fullscreen->Clicked();

			if (App->win->fullscreen) {
				App->win->fullscreen = false;
				SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_SHOWN);
			}
			else {
				App->win->fullscreen = true;
				SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN);
			}
		}
		if (interaction == button_music_volume) {
			App->audio->StopMusic(-2);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction ==button_fx_volume) {
			App->audio->StopMusic(-3);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == minus_music_btn) {
			App->audio->VolumeDown(-2);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == plus_music_btn) {
			App->audio->VolumeUp(-2);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == minus_fx_btn) {
			App->audio->VolumeDown(-3);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == plus_fx_btn) {
			App->audio->VolumeUp(-3); 
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == minus_general_btn) {
			App->audio->VolumeDown(-1);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		if (interaction == plus_general_btn) {
			App->audio->VolumeUp(-1);
			label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
			label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
			label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		}
		break;
	case MainMenuStates::CREDITS_MENU:
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
		if (interaction == button_retun) {
			App->audio->PlayFx(fx_push_button_return);
			CreateMainMenu();
			DestroyCredits();
			main_states = MainMenuStates::MAIN_MENU;
			ret = false;
		}
		
		break;
	}
	if (interaction != nullptr && interaction != button_retun && interaction != new_game_button && interaction != button_retun_to_options && interaction != button_retun_options && interaction != button_warrior && interaction != button_mage && interaction != button_archer)
		App->audio->PlayFx(fx_push_button);
	return ret;
}

void m1MainMenu::CreateMainMenu()
{
	background = App->gui->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->gui->screen, true, false, false,false);
	App->audio->PlayMusic(mus_main_menu, 5);
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
	App->audio->PlayMusic(mus_credits, 0.5);
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


void m1MainMenu::CreateSelectChamp()
{

	select_champ_panel = App->gui->AddImage(0, 0, { 1024, 3256, 1024, 768 }, this, App->gui->screen, true, false, false, false);

	warrior_image = App->gui->AddImage(500, 175, { 1052, 4079, 327, 358 }, App->main_menu, select_champ_panel, true, false, false, false);
	archer_image = App->gui->AddImage(580, 180, { 1701, 4079, 194, 369 }, App->main_menu, select_champ_panel, false, false, false, false);
	mage_image = App->gui->AddImage(580, 180, { 1414, 4079, 218, 363 }, App->main_menu, select_champ_panel, false, false, false, false);

	warrior_info = App->gui->AddImage(370, 600, { 99, 4120, 585, 97 }, App->main_menu, select_champ_panel, true, false, false, false);
	archer_info = App->gui->AddImage(370, 600, { 99, 4273, 537, 97 }, App->main_menu, select_champ_panel, false, false, false, false);
	mage_info = App->gui->AddImage(370, 600, { 98, 4414, 518, 97 }, App->main_menu, select_champ_panel, false, false, false, false);

	button_warrior = App->gui->AddChButton(100, 250, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::WARRIOR, true, false, true, true);
	label_warrior = App->gui->AddLabel(65, -13, "Warrior", button_warrior, BLACK, FontType::FF64, nullptr,false);
	button_archer = App->gui->AddChButton(100, 350, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::ARCHER, true, false, true, true);
	label_archer = App->gui->AddLabel(68, -13, "Archer", button_archer, BLACK, FontType::FF64, nullptr, false);
	button_mage = App->gui->AddChButton(100, 450, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::MAGE, true, false, true, true);
	label_mage = App->gui->AddLabel(75, -13, "Mage", button_mage, BLACK, FontType::FF64, nullptr, false);

	App->audio->PlayMusic(mus_selection, 0.5);



	App->gui->FocusButton((u1Button*)button_warrior);


}

void m1MainMenu::DestroySelectChamp()
{
	App->gui->DeleteUIElement(select_champ_panel);
}

void m1MainMenu::SetMainMenuState(const MainMenuStates & state)
{
	main_states = state;
}

void m1MainMenu::DestroyMainMenu()
{
	App->gui->DeleteUIElement(background);
}

void m1MainMenu::CreateOptions()
{
	options_panel = App->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, App->gui->screen, true, false, false, false);
	options_panel->SetPosRespectParent(CENTERED);

	button_general_volume = App->gui->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_general_volume = App->gui->AddLabel(0, 0, "General Volume", button_general_volume, BLACK, FontType::FF48, nullptr, false);
	label_general_volume->SetPosRespectParent(LEFT_CENTERED);
	minus_general_btn = App->gui->AddButton(715, 185, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options_panel, true, false, true, true);
	plus_general_btn = App->gui->AddButton(805, 185, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options_panel, true, false, true, true);
	label_general_value = App->gui->AddLabel(760, 172, "", options_panel, BLACK, FontType::FF48, nullptr, false);

	button_music_volume = App->gui->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_music_volume = App->gui->AddLabel(0, 0, "Music Volume", button_music_volume, BLACK, FontType::FF48, nullptr, false);
	label_music_volume->SetPosRespectParent(LEFT_CENTERED);
	minus_music_btn = App->gui->AddButton(715, 263, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options_panel, true, false, true, true);
	plus_music_btn = App->gui->AddButton(805, 263, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options_panel, true, false, true, true);
	label_music_value = App->gui->AddLabel(760, 250, "", options_panel, BLACK, FontType::FF48, nullptr, false);

	button_fx_volume = App->gui->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_fx_volume = App->gui->AddLabel(0, 0, "FX Volume", button_fx_volume, BLACK, FontType::FF48, nullptr, false);
	label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	minus_fx_btn = App->gui->AddButton(715, 343, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options_panel, true, false, true, true);
	plus_fx_btn = App->gui->AddButton(805, 343, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options_panel, true, false, true, true);
	label_fx_value = App->gui->AddLabel(760, 330, "", options_panel, BLACK, FontType::FF48, nullptr, false);

	label_fps = App->gui->AddLabel(491, 413, "FPS Caps", options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fps = App->gui->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->box_clicked = App->capactivated;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);

	label_fullscreen = App->gui->AddLabel(491, 503, "Fullscreen", options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fullscreen = App->gui->AddCheckBox(760, 503, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fullscreen->is_option = true;
	checkbox_fullscreen->box_clicked = App->win->fullscreen;
	checkbox_fullscreen->draggable = false;
	checkbox_fullscreen->drawable = true;
	checkbox_fullscreen->interactable = true;
	checkbox_fullscreen->AddListener(this);

	button_controls = App->gui->AddButton(491, 595, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_controls = App->gui->AddLabel(0, 0, "Controls", button_controls, BLACK, FontType::FF48, nullptr, false);
	label_controls->SetPosRespectParent(LEFT_CENTERED);

	button_retun_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_return_options = App->gui->AddLabel(0, 0, "Return", button_retun_options, BLACK, FontType::FF48, nullptr, false);
	label_return_options->SetPosRespectParent(CENTERED);

	label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
	label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
	label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());

}

void m1MainMenu::DestroyOptions()
{
	App->gui->DeleteUIElement(options_panel);

}

void m1MainMenu::CreateControls()
{

	controls_panel = App->gui->AddImage(0, 0, { 0,3256,1024,768 }, this, App->gui->screen, true, false, false, false);
	controls_panel->SetPosRespectParent(CENTERED);


	button_retun_to_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	label_return_to_options = App->gui->AddLabel(0, 0, "Return", button_retun_to_options, BLACK, FontType::FF48, nullptr, false);
	label_return_to_options->SetPosRespectParent(CENTERED);

	// Actions
	// KEYS/BUTTONS
	int offset_between_y = 35;
	int actions_offset_x = 200;
	int first_control_y = 130;

	label_up = App->gui->AddLabel(actions_offset_x, first_control_y, "Move Up", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_right = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y, "Move Right", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_left = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 2, "Move Left", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_down = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 3, "Move Down", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_diagonals = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 4, "Use Diagonals", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_up = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 5, "Look Up", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_right = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 6, "Look Right", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_left = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 7, "Look Left", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_down = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 8, "Look Down", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_basic_attack = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 9, "Basic Attack", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_abilities = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 10, "Show Abilities", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_ability1 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 11, "Ability 1", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_ability2 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 12, "Ability 2", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_ability3 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 13, "Ability 3", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_interact = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 14, "Interact", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_inventory = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 15, "Inventory", controls_panel, BLACK, FontType::FF48, nullptr, false);


	// KEYBOARD
	int keyboard_offset_x = actions_offset_x + 150;
	SDL_Rect button_rect = { 1570,1631,211,30 };

	keyboard = App->gui->AddLabel(keyboard_offset_x, first_control_y - 30, "KEYBOARD", controls_panel, BLACK, FontType::FF48, nullptr, false);

	button_up = App->gui->AddButton(keyboard_offset_x, first_control_y + 10, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.UP, button_up, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_up->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_up);

	button_right = App->gui->AddButton(keyboard_offset_x, button_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.RIGHT, button_right, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_right->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_right);

	button_left = App->gui->AddButton(keyboard_offset_x, button_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.LEFT, button_left, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_left->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_left);

	button_down = App->gui->AddButton(keyboard_offset_x, button_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DOWN, button_down, BLACK, FontType::FF32, nullptr, true);
	label_to_show_how_down->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_down);

	button_diagonals = App->gui->AddButton(keyboard_offset_x, button_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIAGONALS, button_diagonals, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_diagonals);

	button_direction_up = App->gui->AddButton(keyboard_offset_x, button_diagonals->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_UP, button_direction_up, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_direction_up);

	button_direction_right = App->gui->AddButton(keyboard_offset_x, button_direction_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, button_direction_right, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_direction_right);

	button_direction_left = App->gui->AddButton(keyboard_offset_x, button_direction_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, button_direction_left, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_direction_left);

	button_direction_down = App->gui->AddButton(keyboard_offset_x, button_direction_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, button_direction_down, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_direction_down);

	button_basic_attack = App->gui->AddButton(keyboard_offset_x, button_direction_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, button_basic_attack, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_basic_attack);

	button_abilities = App->gui->AddButton(keyboard_offset_x, button_basic_attack->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_abilities = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.SHOW_SKILLS, button_abilities, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_abilities->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_abilities);

	button_ability1 = App->gui->AddButton(keyboard_offset_x, button_abilities->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_ability1 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, button_ability1, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_ability1->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_ability1);

	button_ability2 = App->gui->AddButton(keyboard_offset_x, button_ability1->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_ability2 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, button_ability2, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_ability2->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_ability2);

	button_ability3 = App->gui->AddButton(keyboard_offset_x, button_ability2->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_ability3 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, button_ability3, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_ability3->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_ability3);

	button_interact = App->gui->AddButton(keyboard_offset_x, button_ability3->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_interact = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, button_interact, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_interact->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_interact);

	button_inventory = App->gui->AddButton(keyboard_offset_x, button_interact->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	label_to_show_how_inventory = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.INVENTORY, button_inventory, BLACK, FontType::FF32, nullptr, false);
	label_to_show_how_inventory->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(label_to_show_how_inventory);

	// CONTROLLER
	int controller_offset_x = actions_offset_x + 400;

	controller = App->gui->AddLabel(controller_offset_x, first_control_y - 30, "CONTROLLER", controls_panel, BLACK, FontType::FF48, nullptr, false);

	Cbutton_up = App->gui->AddButton(controller_offset_x, first_control_y + 10, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.UP, Cbutton_up, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_up->SetPosRespectParent(CENTERED);

	Cbutton_right = App->gui->AddButton(controller_offset_x, Cbutton_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.RIGHT, Cbutton_right, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_right->SetPosRespectParent(CENTERED);

	Cbutton_left = App->gui->AddButton(controller_offset_x, Cbutton_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.LEFT, Cbutton_left, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_left->SetPosRespectParent(CENTERED);

	Cbutton_down = App->gui->AddButton(controller_offset_x, Cbutton_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DOWN, Cbutton_down, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_down->SetPosRespectParent(CENTERED);

	Cbutton_diagonals = App->gui->AddButton(controller_offset_x, Cbutton_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIAGONALS, Cbutton_diagonals, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_diagonals);

	Cbutton_direction_up = App->gui->AddButton(controller_offset_x, Cbutton_diagonals->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_UP, Cbutton_direction_up, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_direction_up);

	Cbutton_direction_right = App->gui->AddButton(controller_offset_x, Cbutton_direction_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, Cbutton_direction_right, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_direction_right);

	Cbutton_direction_left = App->gui->AddButton(controller_offset_x, Cbutton_direction_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, Cbutton_direction_left, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_direction_left);

	Cbutton_direction_down = App->gui->AddButton(controller_offset_x, Cbutton_direction_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, Cbutton_direction_down, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_direction_down);

	Cbutton_basic_attack = App->gui->AddButton(controller_offset_x, Cbutton_direction_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.BASIC_ATTACK, Cbutton_basic_attack, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_basic_attack);

	Cbutton_abilities = App->gui->AddButton(controller_offset_x, Cbutton_basic_attack->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_abilities = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.SHOW_SKILLS, Cbutton_abilities, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_abilities->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_abilities);

	Cbutton_ability1 = App->gui->AddButton(controller_offset_x, Cbutton_abilities->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_ability1 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, Cbutton_ability1, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_ability1->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_ability1);

	Cbutton_ability2 = App->gui->AddButton(controller_offset_x, Cbutton_ability1->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_ability2 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, Cbutton_ability2, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_ability2->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_ability2);

	Cbutton_ability3 = App->gui->AddButton(controller_offset_x, Cbutton_ability2->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_ability3 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, Cbutton_ability3, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_ability3->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_ability3);

	Cbutton_interact = App->gui->AddButton(controller_offset_x, Cbutton_ability3->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_interact = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.BASIC_ATTACK, Cbutton_interact, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_interact->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_interact);

	Cbutton_inventory = App->gui->AddButton(controller_offset_x, Cbutton_interact->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls_panel, true, false, true, true);
	Clabel_to_show_how_inventory = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.INVENTORY, Cbutton_inventory, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_inventory->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(Clabel_to_show_how_inventory);

}

void m1MainMenu::DestroyControls()
{
	App->scene->control_to_change = nullptr;
	App->gui->DeleteUIElement(controls_panel);

	App->scene->labels_control.clear();
	App->scene->Clabels_control.clear();
}

void m1MainMenu::CreateNameMenu()
{
	input_text_image = App->gui->AddImage(0, 0, { 1024, 3256, 1024, 768 }, this, App->gui->screen, true, false, false, false);

	input_text = App->gui->AddInputText(0, 0, "ChooseYourCharacterName", input_text_image, BLACK, FontType::FF64, {100,100,500,50}, this);
	input_text->SetPosRespectParent(CENTERED);

	button_okay = App->gui->AddButton(0, 0, { 1570, 1631, 211, 30 }, { 1570, 1631, 211, 30 }, { 1570, 1631, 211, 30 }, this, input_text, true, false, true, true);
	button_okay->SetPosRespectParent(RIGHT_CENTERED, -300);
}

void m1MainMenu::DestroyNameMenu()
{
	App->gui->DeleteUIElement(input_text_image);
}

