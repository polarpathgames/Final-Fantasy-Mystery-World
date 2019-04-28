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

	App->menu_manager->CreateMainMenu();
	App->audio->PlayMusic(mus_main_menu, 5);

	main_states = MainMenuStates::MAIN_MENU;
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
		main_states = MainMenuStates::SELECTION_MENU;
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.exit_game_button) {
		App->QuitGame();
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.credits_button) {
		App->menu_manager->CreateCredits();
		App->menu_manager->DestroyMainMenu();
		main_states = MainMenuStates::CREDITS_MENU;
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.options_button) {
		App->menu_manager->CreateOptions();
		App->menu_manager->DestroyMainMenu();
		main_states = MainMenuStates::OPTIONS_MENU;
		ret = false;
	}
	else if (interaction == App->menu_manager->main_menu.load_game_button) {
		App->LoadGame("save_game.xml");
		ret = false;
	}

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
	App->menu_manager->ManageInputText(interaction);
	
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