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
#include <windows.h>
#include "m1Audio.h"
#include "m1Window.h"
#include "m1MenuManager.h"

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
	m1MenuManager::CreateMainMenu();
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
		if (interaction == exit_game_button) {
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
				App->globals.Reset();
				App->globals.player_name = input_text->GetText();
				DestroyNameMenu();
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
		if (interaction == button_upper) {
			minus_letters->drawable = false;
			max_letters->drawable = true;
		}
		if (interaction == button_lower) {
			minus_letters->drawable = true;
			max_letters->drawable = false;
		}
		if (interaction == button_A) {
			if (minus_letters->drawable) {
				input_text->AddText("a");
			}
			else if (max_letters->drawable) {
				input_text->AddText("A");
			}
		}
		if (interaction == button_B) {
			if (minus_letters->drawable) {
				input_text->AddText("b");
			}
			else if (max_letters->drawable) {
				input_text->AddText("B");
			}
		}
		if (interaction == button_C) {
			if (minus_letters->drawable) {
				input_text->AddText("c");
			}
			else if (max_letters->drawable) {
				input_text->AddText("C");
			}
		}
		if (interaction == button_D) {
			if (minus_letters->drawable) {
				input_text->AddText("d");
			}
			else if (max_letters->drawable) {
				input_text->AddText("D");
			}
		}
		if (interaction == button_E) {
			if (minus_letters->drawable) {
				input_text->AddText("e");
			}
			else if (max_letters->drawable) {
				input_text->AddText("E");
			}
		}
		if (interaction == button_F) {
			if (minus_letters->drawable) {
				input_text->AddText("f");
			}
			else if (max_letters->drawable) {
				input_text->AddText("F");
			}
		}
		if (interaction == button_H) {
			if (minus_letters->drawable) {
				input_text->AddText("h");
			}
			else if (max_letters->drawable) {
				input_text->AddText("H");
			}
		}
		if (interaction == button_G) {
			if (minus_letters->drawable) {
				input_text->AddText("g");
			}
			else if (max_letters->drawable) {
				input_text->AddText("G");
			}
		}
		if (interaction == button_I) {
			if (minus_letters->drawable) {
				input_text->AddText("i");
			}
			else if (max_letters->drawable) {
				input_text->AddText("I");
			}
		}
		if (interaction == button_J) {
			if (minus_letters->drawable) {
				input_text->AddText("j");
			}
			else if (max_letters->drawable) {
				input_text->AddText("J");
			}
		}
		if (interaction == button_K) {
			if (minus_letters->drawable) {
				input_text->AddText("k");
			}
			else if (max_letters->drawable) {
				input_text->AddText("K");
			}
		}
		if (interaction == button_L) {
			if (minus_letters->drawable) {
				input_text->AddText("l");
			}
			else if (max_letters->drawable) {
				input_text->AddText("L");
			}
		}
		if (interaction == button_M) {
			if (minus_letters->drawable) {
				input_text->AddText("m");
			}
			else if (max_letters->drawable) {
				input_text->AddText("M");
			}
		}
		if (interaction == button_N) {
			if (minus_letters->drawable) {
				input_text->AddText("n");
			}
			else if (max_letters->drawable) {
				input_text->AddText("N");
			}
		}
		if (interaction == button_O) {
			if (minus_letters->drawable) {
				input_text->AddText("o");
			}
			else if (max_letters->drawable) {
				input_text->AddText("O");
			}
		}
		if (interaction == button_P) {
			if (minus_letters->drawable) {
				input_text->AddText("p");
			}
			else if (max_letters->drawable) {
				input_text->AddText("P");
			}
		}
		if (interaction == button_Q) {
			if (minus_letters->drawable) {
				input_text->AddText("q");
			}
			else if (max_letters->drawable) {
				input_text->AddText("Q");
			}
		}
		if (interaction == button_R) {
			if (minus_letters->drawable) {
				input_text->AddText("r");
			}
			else if (max_letters->drawable) {
				input_text->AddText("R");
			}
		}
		if (interaction == button_S) {
			if (minus_letters->drawable) {
				input_text->AddText("s");
			}
			else if (max_letters->drawable) {
				input_text->AddText("S");
			}
		}
		if (interaction == button_T) {
			if (minus_letters->drawable) {
				input_text->AddText("t");
			}
			else if (max_letters->drawable) {
				input_text->AddText("T");
			}
		}
		if (interaction == button_U) {
			if (minus_letters->drawable) {
				input_text->AddText("u");
			}
			else if (max_letters->drawable) {
				input_text->AddText("U");
			}
		}
		if (interaction == button_V) {
			if (minus_letters->drawable) {
				input_text->AddText("v");
			}
			else if (max_letters->drawable) {
				input_text->AddText("V");
			}
		}
		if (interaction == button_W) {
			if (minus_letters->drawable) {
				input_text->AddText("w");
			}
			else if (max_letters->drawable) {
				input_text->AddText("W");
			}
		}
		if (interaction == button_X) {
			if (minus_letters->drawable) {
				input_text->AddText("x");
			}
			else if (max_letters->drawable) {
				input_text->AddText("X");
			}
		}
		if (interaction == button_Y) {
			if (minus_letters->drawable) {
				input_text->AddText("y");
			}
			else if (max_letters->drawable) {
				input_text->AddText("Y");
			}
		}
		if (interaction == button_Z) {
			if (minus_letters->drawable) {
				input_text->AddText("z");
			}
			else if (max_letters->drawable) {
				input_text->AddText("Z");
			}
		}
		if (interaction == button_Delete) {
			input_text->DeleteText();
		}
		if (interaction == button_Space) {
			input_text->AddText(" ");
		}
		break;
	case MainMenuStates::SELECTION_MENU:
		if (interaction == button_warrior) {
			App->scene->player_type = PlayerType::WARRIOR;
			CreateNameMenu();
			DestroySelectChamp();
			App->scene->player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::WARRIOR, -100, -100,"warrior");
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}
		if (interaction == button_archer) {
			App->scene->player_type = PlayerType::ARCHER;
			CreateNameMenu();
			DestroySelectChamp();
			App->scene->player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::ARCHER, -100, -100, "archer");
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}
		if (interaction == button_mage) {
			App->scene->player_type = PlayerType::MAGE;
			CreateNameMenu();
			DestroySelectChamp();
			App->scene->player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::MAGE, -100, -100, "mage");
			main_states = MainMenuStates::CHOOSE_NAME_MENU;
			ret = false;
		}

		if (interaction == return_select_champ_button) {
			CreateMainMenu();
			DestroySelectChamp();
			main_states = MainMenuStates::MAIN_MENU;
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
		if (interaction == checkbox_mute_music)
		{
			checkbox_mute_music->Clicked();
			App->audio->StopMusic(-2);
		}

		if (interaction == checkbox_mute_fx)
		{
			checkbox_mute_fx->Clicked();
			App->audio->StopMusic(-3);
		}
		//if (interaction == checkbox_fps)
		//{
		//	checkbox_fps->Clicked();
		//	if (App->capactivated) {
		//		App->capactivated = false;
		//	}
		//	else {
		//		App->capactivated = true;
		//	}
		//	//App->GetFrameRate();
		//}
		
		if (interaction == checkbox_fullscreen)
		{
			checkbox_fullscreen->Clicked();

			if (App->win->fullscreen) {
				App->win->fullscreen = false;
				SDL_SetWindowFullscreen(App->win->window, 0);
			}
			else {
				App->win->fullscreen = true;
				SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
		if (interaction == button_credits_return_menu) {
			App->audio->PlayFx(fx_push_button_return);
			CreateMainMenu();
			DestroyCredits();
			main_states = MainMenuStates::MAIN_MENU;
			ret = false;
		}
		
		break;
	}
	if (interaction != nullptr && interaction != button_credits_return_menu && interaction != new_game_button && interaction != button_retun_to_options && interaction != button_retun_options && interaction != button_warrior && interaction != button_mage && interaction != button_archer)
		App->audio->PlayFx(fx_push_button);
	return ret;
}