#include "m1MenuManager.h"
#include "App.h"
#include "m1MainMenu.h"
#include "m1Scene.h"
#include "m1Audio.h"
#include "m1Window.h"
#include "m1GUI.h"
#include "u1Image.h"
#include "u1Button.h"
#include "u1InputText.h"
#include "u1CheckBox.h"
#include "u1ChButton.h"
#include "m1Input.h"
#include "m1Scene.h"
#include "m1Textures.h"
#include "m1Cutscene.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "e1Player.h"

void m1MenuManager::CreateMainMenu()
{
	main_menu.background = App->gui->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->gui->screen, true, false, false, false);
	int offsetY = 75;

	main_menu.new_game_button = App->gui->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false, true, true);
	main_menu.new_game_label = App->gui->AddLabel(0, 0, "New Game", main_menu.new_game_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.new_game_label->SetPosRespectParent(CENTERED);

	if (App->LookForFileExistence("save_game.xml"))
		main_menu.load_game_button = App->gui->AddButton(684, main_menu.new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false, true, true);
	else
		main_menu.load_game_button = App->gui->AddButton(684, main_menu.new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false,false, false);

	main_menu.load_game_label = App->gui->AddLabel(0, 0, "Load Game", main_menu.load_game_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.load_game_label->SetPosRespectParent(CENTERED);

	main_menu.options_button = App->gui->AddButton(684, main_menu.load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false, true, true);
	main_menu.options_label = App->gui->AddLabel(0, 0, "Options", main_menu.options_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.options_label->SetPosRespectParent(CENTERED);

	main_menu.credits_button = App->gui->AddButton(684, main_menu.options_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false, true, true);
	main_menu.credits_label = App->gui->AddLabel(0, 0, "Credits", main_menu.credits_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.credits_label->SetPosRespectParent(CENTERED);

	main_menu.exit_game_button = App->gui->AddButton(684, main_menu.credits_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, main_menu.background, false, false, true, true);
	main_menu.exit_game_text = App->gui->AddLabel(0, 0, "Exit", main_menu.exit_game_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.exit_game_text->SetPosRespectParent(CENTERED);

}

void m1MenuManager::DestroyMainMenu()
{
	App->gui->DeleteUIElement(main_menu.background);
	main_menu.Reset();
}

void m1MenuManager::CreateCredits()
{
	App->audio->PlayMusic(App->main_menu->mus_credits, 0.5);
	credits.credits_panel = App->gui->AddImage(0, 0, { 0, 2304, 1024, 768 }, App->main_menu, App->gui->screen, true, false, false, false);
	credits.credits_panel->SetPosRespectParent(CENTERED);

	credits.button_christian = App->gui->AddButton(325, 290, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_christian = App->gui->AddLabel(0, 0, "Christian Martinez - Lead", credits.button_christian, WHITE, FontType::FF100, nullptr, false);
	credits.label_christian->SetPosRespectParent(LEFT_CENTERED);

	credits.button_lluis = App->gui->AddButton(85, 350, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_lluis = App->gui->AddLabel(0, 0, "Lluis Moreu - Manager", credits.button_lluis, WHITE, FontType::FF100, nullptr, false);
	credits.label_lluis->SetPosRespectParent(LEFT_CENTERED);

	credits.button_marc = App->gui->AddButton(85, 400, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_marc = App->gui->AddLabel(0, 0, "Marc Galvez - Design", credits.button_marc, WHITE, FontType::FF100, nullptr, false);
	credits.label_marc->SetPosRespectParent(LEFT_CENTERED);

	credits.button_enric = App->gui->AddButton(85, 450, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_enric = App->gui->AddLabel(0, 0, "Enric Perez - UI", credits.button_enric, WHITE, FontType::FF100, nullptr, false);
	credits.label_enric->SetPosRespectParent(LEFT_CENTERED);

	credits.button_oriol = App->gui->AddButton(555, 350, { 1850,1637,350,50 }, { 1850,1637,1980,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_oriol = App->gui->AddLabel(0, 0, "Oriol Capdevila - Code", credits.button_oriol, WHITE, FontType::FF100, nullptr, false);
	credits.label_oriol->SetPosRespectParent(LEFT_CENTERED);

	credits.button_nadine = App->gui->AddButton(555, 400, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_nadine = App->gui->AddLabel(0, 0, "Nadine Gutierrez - Art", credits.button_nadine, WHITE, FontType::FF100, nullptr, false);
	credits.label_nadine->SetPosRespectParent(LEFT_CENTERED);

	credits.button_ivan = App->gui->AddButton(555, 450, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_ivan = App->gui->AddLabel(0, 0, "Ivan Ropero - QA", credits.button_ivan, WHITE, FontType::FF100, nullptr, false);
	credits.label_ivan->SetPosRespectParent(LEFT_CENTERED);

	credits.button_credits_return_menu = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_credits_return_menu = App->gui->AddLabel(0, 0, "Return", credits.button_credits_return_menu, WHITE, FontType::FF64, nullptr, false);
	credits.label_credits_return_menu->SetPosRespectParent(CENTERED);

	credits.button_github = App->gui->AddButton(710, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_github = App->gui->AddLabel(0, 0, ".", credits.button_github, WHITE, FontType::FF32, nullptr, false);
	credits.label_github->SetPosRespectParent(CENTERED);

	credits.button_twitter = App->gui->AddButton(410, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_twitter = App->gui->AddLabel(0, 0, ".", credits.button_twitter, WHITE, FontType::FF32, nullptr, false);
	credits.label_twitter->SetPosRespectParent(CENTERED);

	credits.button_youtube = App->gui->AddButton(110, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->main_menu, credits.credits_panel, false, false, true, true);
	credits.label_youtube = App->gui->AddLabel(0, 0, ".", credits.button_youtube, WHITE, FontType::FF32, nullptr, false);
	credits.label_youtube->SetPosRespectParent(CENTERED);
}

void m1MenuManager::DestroyCredits()
{
	App->gui->DeleteUIElement(credits.credits_panel);
	credits.Reset();
}

void m1MenuManager::CreateSelectChamp()
{

	select_champ.select_champ_panel = App->gui->AddImage(0, 0, { 1024, 3256, 1024, 768 }, App->main_menu, App->gui->screen, true, false, false, false);
	
	select_champ.warrior_image = App->gui->AddImage(500, 175, { 1052, 4079, 327, 358 }, App->main_menu, select_champ.select_champ_panel, true, false, false, false);
	select_champ.archer_image = App->gui->AddImage(580, 180, { 1681, 4050, 244, 400 }, App->main_menu, select_champ.select_champ_panel, false, false, false, false);
	select_champ.mage_image = App->gui->AddImage(580, 180, { 1414, 4079, 218, 363 }, App->main_menu, select_champ.select_champ_panel, false, false, false, false);

	select_champ.warrior_info = App->gui->AddImage(370, 600, { 99, 4120, 585, 97 }, App->main_menu, select_champ.select_champ_panel, true, false, false, false);
	select_champ.archer_info = App->gui->AddImage(370, 600, { 99, 4273, 537, 97 }, App->main_menu, select_champ.select_champ_panel, false, false, false, false);
	select_champ.mage_info = App->gui->AddImage(370, 600, { 98, 4414, 518, 97 }, App->main_menu, select_champ.select_champ_panel, false, false, false, false);

	select_champ.button_warrior = App->gui->AddChButton(100, 250, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, App->main_menu, select_champ.select_champ_panel, PlayerType::WARRIOR, true, false, true, true);
	select_champ.label_warrior = App->gui->AddLabel(65, -13, "Warrior", select_champ.button_warrior, BLACK, FontType::FF64, nullptr, false);
	select_champ.button_archer = App->gui->AddChButton(100, 350, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, App->main_menu, select_champ.select_champ_panel, PlayerType::ARCHER, true, false, true, true);
	select_champ.label_archer = App->gui->AddLabel(68, -13, "Archer", select_champ.button_archer, BLACK, FontType::FF64, nullptr, false);
	select_champ.button_mage = App->gui->AddChButton(100, 450, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, App->main_menu, select_champ.select_champ_panel, PlayerType::MAGE, true, false, true, true);
	select_champ.label_mage = App->gui->AddLabel(75, -13, "Mage", select_champ.button_mage, BLACK, FontType::FF64, nullptr, false);

	select_champ.button_warrior->AddElementsToShow(select_champ.warrior_image);
	select_champ.button_warrior->AddElementsToShow(select_champ.warrior_info);

	select_champ.button_archer->AddElementsToShow(select_champ.archer_image);
	select_champ.button_archer->AddElementsToShow(select_champ.archer_info);

	select_champ.button_mage->AddElementsToShow(select_champ.mage_image);
	select_champ.button_mage->AddElementsToShow(select_champ.mage_info);

	App->audio->PlayMusic(App->main_menu->mus_selection, 0.5);

	select_champ.return_select_champ_button = App->gui->AddButton(120, 640, { 1000, 1000, 80, 50 }, { 1000, 1000, 80, 50 }, { 1000, 1000, 80, 50 }, App->main_menu, select_champ.select_champ_panel, false, false, true, true, { -10, 3 });
	select_champ.return_select_champ_label = App->gui->AddLabel(0, 0, "Return", select_champ.return_select_champ_button, BLACK, FontType::FF64, this, false);

	App->gui->FocusButton((u1Button*)select_champ.button_warrior);


}

void m1MenuManager::DestroySelectChamp()
{
	App->gui->DeleteUIElement(select_champ.select_champ_panel);
	select_champ.Reset();
}

void m1MenuManager::CreateOptions()
{
	options.options_panel = App->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, App->gui->screen, true, false, false, false);
	options.options_panel->SetPosRespectParent(CENTERED);

	options.button_general_volume = App->gui->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options.options_panel, false, false, true, true);
	options.label_general_volume = App->gui->AddLabel(0, 0, "General Volume", options.button_general_volume, BLACK, FontType::FF48, nullptr, false);
	options.label_general_volume->SetPosRespectParent(LEFT_CENTERED);
	options.minus_general_btn = App->gui->AddButton(715, 185, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.plus_general_btn = App->gui->AddButton(805, 185, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.label_general_value = App->gui->AddLabel(760, 172, "", options.options_panel, BLACK, FontType::FF48, nullptr, false);

	options.button_music_volume = App->gui->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options.options_panel, false, false, true, true);
	options.label_music_volume = App->gui->AddLabel(0, 0, "Music Volume", options.button_music_volume, BLACK, FontType::FF48, nullptr, false);
	options.label_music_volume->SetPosRespectParent(LEFT_CENTERED);
	options.minus_music_btn = App->gui->AddButton(715, 263, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.plus_music_btn = App->gui->AddButton(805, 263, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.label_music_value = App->gui->AddLabel(760, 250, "", options.options_panel, BLACK, FontType::FF48, nullptr, false);

	options.checkbox_mute_music = App->gui->AddCheckBox(900, 263, { 1618, 1834, 33, 33 }, { 1618, 1834, 33, 33 }, { 1581, 1836, 26, 29 }, options.options_panel);
	options.checkbox_mute_music->is_option = true;
	options.checkbox_mute_music->box_clicked = App->audio->mute_volume;
	options.checkbox_mute_music->draggable = false;
	options.checkbox_mute_music->drawable = true;
	options.checkbox_mute_music->interactable = true;
	options.checkbox_mute_music->AddListener(this);

	options.button_fx_volume = App->gui->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options.options_panel, false, false, true, true);
	options.label_fx_volume = App->gui->AddLabel(0, 0, "FX Volume", options.button_fx_volume, BLACK, FontType::FF48, nullptr, false);
	options.label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	options.minus_fx_btn = App->gui->AddButton(715, 343, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.plus_fx_btn = App->gui->AddButton(805, 343, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options.options_panel, true, false, true, true);
	options.label_fx_value = App->gui->AddLabel(760, 330, "", options.options_panel, BLACK, FontType::FF48, nullptr, false);

	options.checkbox_mute_fx = App->gui->AddCheckBox(900, 343, { 1618, 1834, 33, 33 }, { 1618, 1834, 33, 33 }, { 1581, 1836, 26, 29 }, options.options_panel);
	options.checkbox_mute_fx->is_option = true;
	options.checkbox_mute_fx->box_clicked = App->audio->mute_fx;
	options.checkbox_mute_fx->draggable = false;
	options.checkbox_mute_fx->drawable = true;
	options.checkbox_mute_fx->interactable = true;
	options.checkbox_mute_fx->AddListener(this);

	/*label_fps = App->gui->AddLabel(491, 413, "FPS Caps", options.options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fps = App->gui->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options.options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->box_clicked = App->capactivated;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);*/

	options.label_fullscreen = App->gui->AddLabel(491, 413, "Fullscreen", options.options_panel, BLACK, FontType::FF48, nullptr, false);
	options.checkbox_fullscreen = App->gui->AddCheckBox(760, 420, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options.options_panel);
	options.checkbox_fullscreen->is_option = true;
	options.checkbox_fullscreen->box_clicked = App->win->fullscreen;
	options.checkbox_fullscreen->draggable = false;
	options.checkbox_fullscreen->drawable = true;
	options.checkbox_fullscreen->interactable = true;
	options.checkbox_fullscreen->AddListener(this);

	options.button_controls = App->gui->AddButton(491, 503, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options.options_panel, false, false, true, true);
	options.label_controls = App->gui->AddLabel(0, 0, "Controls", options.button_controls, BLACK, FontType::FF48, nullptr, false);
	options.label_controls->SetPosRespectParent(LEFT_CENTERED);

	options.button_retun_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options.options_panel, false, false, true, true);
	options.label_return_options = App->gui->AddLabel(0, 0, "Return", options.button_retun_options, BLACK, FontType::FF48, nullptr, false);
	options.label_return_options->SetPosRespectParent(CENTERED);

	options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
	options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
	options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());

}

void m1MenuManager::DestroyOptions()
{
	App->gui->DeleteUIElement(options.options_panel);
	options.Reset();
}

void m1MenuManager::CreateControls()
{
	App->scene->SetMenuState(StatesMenu::CONTROLS_MENU);

	controls.controls_panel = App->gui->AddImage(0, 0, { 0,3256,1024,768 }, this, App->gui->screen, true, false, false, false);
	controls.controls_panel->SetPosRespectParent(CENTERED);


	controls.button_retun_to_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls.controls_panel, false, false, true, true);
	controls.label_return_to_options = App->gui->AddLabel(0, 0, "Return", controls.button_retun_to_options, BLACK, FontType::FF48, nullptr, false);
	controls.label_return_to_options->SetPosRespectParent(CENTERED);

	// Actions
	// KEYS/BUTTONS
	int offset_between_y = 35;
	int actions_offset_x = 200;
	int first_control_y = 130;

	controls.keyboard.label_up = App->gui->AddLabel(actions_offset_x, first_control_y, "Move Up", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_right = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y, "Move Right", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_left = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 2, "Move Left", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_down = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 3, "Move Down", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_diagonals = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 4, "Use Diagonals", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_direction_up = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 5, "Look Up", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_direction_right = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 6, "Look Right", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_direction_left = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 7, "Look Left", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_direction_down = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 8, "Look Down", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_basic_attack = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 9, "Basic Attack", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_abilities = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 10, "Show Abilities", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_ability1 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 11, "Ability 1", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_ability2 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 12, "Ability 2", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_ability3 = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 13, "Ability 3", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_interact = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 14, "Interact", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);
	controls.keyboard.label_inventory = App->gui->AddLabel(actions_offset_x, first_control_y + offset_between_y * 15, "Inventory", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);

	// KEYBOARD
	int keyboard_offset_x = actions_offset_x + 150;
	SDL_Rect button_rect = { 1570,1631,211,30 };

	controls.keyboard.keyboard = App->gui->AddLabel(keyboard_offset_x, first_control_y - 30, "KEYBOARD", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);

	controls.keyboard.button_up = App->gui->AddButton(keyboard_offset_x, first_control_y + 10, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.UP, controls.keyboard.button_up, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_up->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_up);

	controls.keyboard.button_right = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.RIGHT, controls.keyboard.button_right, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_right->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_right);

	controls.keyboard.button_left = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.LEFT, controls.keyboard.button_left, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_left->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_left);

	controls.keyboard.button_down = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DOWN, controls.keyboard.button_down, BLACK, FontType::FF32, nullptr, true);
	controls.keyboard.label_to_show_how_down->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_down);

	controls.keyboard.button_diagonals = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIAGONALS, controls.keyboard.button_diagonals, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_diagonals);

	controls.keyboard.button_direction_up = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_diagonals->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_UP, controls.keyboard.button_direction_up, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_direction_up);

	controls.keyboard.button_direction_right = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_direction_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, controls.keyboard.button_direction_right, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_direction_right);

	controls.keyboard.button_direction_left = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_direction_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, controls.keyboard.button_direction_left, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_direction_left);

	controls.keyboard.button_direction_down = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_direction_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, controls.keyboard.button_direction_down, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_direction_down);

	controls.keyboard.button_basic_attack = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_direction_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, controls.keyboard.button_basic_attack, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_basic_attack);

	controls.keyboard.button_abilities = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_basic_attack->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_abilities = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.SHOW_SKILLS, controls.keyboard.button_abilities, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_abilities->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_abilities);

	controls.keyboard.button_ability1 = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_abilities->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_ability1 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, controls.keyboard.button_ability1, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_ability1->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_ability1);

	controls.keyboard.button_ability2 = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_ability1->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_ability2 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, controls.keyboard.button_ability2, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_ability2->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_ability2);

	controls.keyboard.button_ability3 = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_ability2->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_ability3 = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.ABILITY1, controls.keyboard.button_ability3, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_ability3->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_ability3);

	controls.keyboard.button_interact = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_ability3->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_interact = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, controls.keyboard.button_interact, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_interact->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_interact);

	controls.keyboard.button_inventory = App->gui->AddButton(keyboard_offset_x, controls.keyboard.button_interact->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.keyboard.label_to_show_how_inventory = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.INVENTORY, controls.keyboard.button_inventory, BLACK, FontType::FF32, nullptr, false);
	controls.keyboard.label_to_show_how_inventory->SetPosRespectParent(CENTERED);
	App->scene->labels_control.push_back(controls.keyboard.label_to_show_how_inventory);

	// CONTROLLER
	int controller_offset_x = actions_offset_x + 400;
	
	controls.controller.controller = App->gui->AddLabel(controller_offset_x, first_control_y - 30, "CONTROLLER", controls.controls_panel, BLACK, FontType::FF48, nullptr, false);

	controls.controller.Cbutton_up = App->gui->AddButton(controller_offset_x, first_control_y + 10, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.UP, controls.controller.Cbutton_up, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_up->SetPosRespectParent(CENTERED);

	controls.controller.Cbutton_right = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.RIGHT, controls.controller.Cbutton_right, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_right->SetPosRespectParent(CENTERED);

	controls.controller.Cbutton_left = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.LEFT, controls.controller.Cbutton_left, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_left->SetPosRespectParent(CENTERED);

	controls.controller.Cbutton_down = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DOWN, controls.controller.Cbutton_down, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_down->SetPosRespectParent(CENTERED);

	controls.controller.Cbutton_diagonals = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIAGONALS, controls.controller.Cbutton_diagonals, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_diagonals);

	controls.controller.Cbutton_direction_up = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_diagonals->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_UP, controls.controller.Cbutton_direction_up, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_direction_up);

	controls.controller.Cbutton_direction_right = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_direction_up->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, controls.controller.Cbutton_direction_right, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_direction_right);

	controls.controller.Cbutton_direction_left = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_direction_right->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, controls.controller.Cbutton_direction_left, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_direction_left);

	controls.controller.Cbutton_direction_down = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_direction_left->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, controls.controller.Cbutton_direction_down, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_direction_down);

	controls.controller.Cbutton_basic_attack = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_direction_down->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.BASIC_ATTACK, controls.controller.Cbutton_basic_attack, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_basic_attack);

	controls.controller.Cbutton_abilities = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_basic_attack->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_abilities = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.SHOW_SKILLS, controls.controller.Cbutton_abilities, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_abilities->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_abilities);

	controls.controller.Cbutton_ability1 = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_abilities->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_ability1 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, controls.controller.Cbutton_ability1, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_ability1->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_ability1);

	controls.controller.Cbutton_ability2 = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_ability1->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_ability2 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, controls.controller.Cbutton_ability2, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_ability2->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_ability2);

	controls.controller.Cbutton_ability3 = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_ability2->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_ability3 = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.ABILITY1, controls.controller.Cbutton_ability3, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_ability3->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_ability3);

	controls.controller.Cbutton_interact = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_ability3->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_interact = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.BASIC_ATTACK, controls.controller.Cbutton_interact, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_interact->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_interact);

	controls.controller.Cbutton_inventory = App->gui->AddButton(controller_offset_x, controls.controller.Cbutton_interact->position.y + offset_between_y, button_rect, button_rect, button_rect, this, controls.controls_panel, true, false, true, true);
	controls.controller.Clabel_to_show_how_inventory = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.INVENTORY, controls.controller.Cbutton_inventory, BLACK, FontType::FF32, nullptr, false);
	controls.controller.Clabel_to_show_how_inventory->SetPosRespectParent(CENTERED);
	App->scene->Clabels_control.push_back(controls.controller.Clabel_to_show_how_inventory);

}

void m1MenuManager::DestroyControls()
{
	App->scene->control_to_change = nullptr;
	App->gui->DeleteUIElement(controls.controls_panel);

	App->scene->labels_control.clear();
	App->scene->Clabels_control.clear();
}

void m1MenuManager::CreateNameMenu()
{
	input.input_text_image = App->gui->AddImage(0, 0, { 1025, 4792, 1024, 768 }, App->main_menu, App->gui->screen, true, false, false, false);



	input.minus_letters = App->gui->AddImage(137, 350, { 1024,5658,743,334 }, nullptr, input.input_text_image, true, false, false, false);
	input.max_letters = App->gui->AddImage(137, 350, { 119,5658,743,334 }, nullptr, input.input_text_image, false, false, false, false);

	// 
	input.button_A = App->gui->AddButton(0, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_B = App->gui->AddButton(94, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_C = App->gui->AddButton(188, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_D = App->gui->AddButton(282, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_E = App->gui->AddButton(378, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_F = App->gui->AddButton(471, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_G = App->gui->AddButton(565, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_upper = App->gui->AddButton(662, 0, { 0,0,80,47 }, { 0,0,80,47 }, { 0,0,80,47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.input_text = App->gui->AddInputText(52, -91, "", input.max_letters, BLACK, FontType::FF64, { 1214,5050,600,63 }, this);
	//
	input.button_H = App->gui->AddButton(0, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_I = App->gui->AddButton(94, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_J = App->gui->AddButton(188, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_K = App->gui->AddButton(282, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_L = App->gui->AddButton(378, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_M = App->gui->AddButton(471, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_N = App->gui->AddButton(565, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_lower = App->gui->AddButton(662, 74, { 0,0,80,47 }, { 0,0,80,47 }, { 0,0,80,47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	//
	input.button_O = App->gui->AddButton(0, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_P = App->gui->AddButton(94, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_Q = App->gui->AddButton(188, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_R = App->gui->AddButton(282, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_S = App->gui->AddButton(378, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_T = App->gui->AddButton(471, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_U = App->gui->AddButton(565, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_okay = App->gui->AddButton(662, 148, { 0, 0, 60, 47 }, { 0, 0, 60, 47 }, { 0, 0, 60, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	//
	input.button_V = App->gui->AddButton(0, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_W = App->gui->AddButton(94, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_X = App->gui->AddButton(188, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_Y = App->gui->AddButton(282, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_Z = App->gui->AddButton(378, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	input.button_Delete = App->gui->AddButton(471, 223, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });
	//
	input.button_Space = App->gui->AddButton(188, 295, { 0, 0, 235, 40 }, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, App->main_menu, input.max_letters, false, false, true, true, { -2,-5 });

	App->gui->FocusButton((u1Button*)input.input_text);

}

void m1MenuManager::DestroyNameMenu()
{
	App->gui->DeleteUIElement(input.input_text_image);
	input.Reset();
}

void m1MenuManager::CreateGoToQuestMenu()
{
	App->audio->PlayFx(App->gui->fx_inventory);
	quest.go_to_quest_panel = App->gui->AddImage(100, 70, { 1878, 1536, 170, 101 }, nullptr, App->gui->screen, true, false, false, false);

	quest.go_to_quest_button = App->gui->AddButton(30, 0, { 10, 10, 70, 50 }, { 10, 10, 70, 50 }, { 10, 10, 70, 50 }, App->scene, quest.go_to_quest_panel, false, false, true, true);
	quest.go_to_quest_label = App->gui->AddLabel(50, -5, "Tutorial", quest.go_to_quest_panel, BLACK, FontType::FF64, nullptr, false);

	quest.cancel_quest_button = App->gui->AddButton(30, 43, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, App->scene, quest.go_to_quest_panel, false, false, true, true);
	quest.cancel_quest_label = App->gui->AddLabel(50, 38, "Cancel", quest.go_to_quest_panel, BLACK, FontType::FF64, nullptr, false);

	App->scene->player->BlockControls(true);
}

void m1MenuManager::DestroyGoToQuestMenu()
{

	App->gui->DeleteUIElement(quest.go_to_quest_panel);

	App->scene->player->BlockControls(false);
}

void m1MenuManager::CreateInventory()
{
	inventory.inventory_panel = App->gui->AddImage(0, 0, { 1024, 1536, 228, 384 }, App->scene, App->gui->screen, true, false, false, false);
	inventory.inventory_panel->SetPosRespectParent(RIGHT_CENTERED, 8);

	inventory.player_name = App->gui->AddLabel(80, 7, App->globals.player_name.c_str(), inventory.inventory_panel, BLACK, FontType::FF64, nullptr, false);

	inventory.hp_potion_button = App->gui->AddButton(73, 72, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, App->scene, inventory.inventory_panel, true, false, true, true);
	inventory.hp_potion_image = App->gui->AddImage(85, 80, { 1058, 1952, 33, 47 }, nullptr, inventory.inventory_panel, true, false, false, false);
	inventory.hp_potion_label = App->gui->AddLabel(50, -10, std::string("x " + std::to_string(App->scene->player->stats.num_hp_potions)).data(), inventory.hp_potion_image, BLACK, FontType::FF64, nullptr, false);

	inventory.mana_potion_button = App->gui->AddButton(73, 135, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, App->scene, inventory.inventory_panel, true, false, true, true);
	inventory.mana_potion_image = App->gui->AddImage(85, 140, { 1091, 1952, 33, 51 }, nullptr, inventory.inventory_panel, true, false, false, false);
	inventory.mana_potion_label = App->gui->AddLabel(50, -10, std::string("x " + std::to_string(App->scene->player->stats.num_mana_potions)).data(), inventory.mana_potion_image, BLACK, FontType::FF64, nullptr, false);

	inventory.coin_image = App->gui->AddImage(45, 225, { 1024, 1952, 34, 34 }, App->scene, inventory.inventory_panel, true, false, false, false);
	inventory.money_label = App->gui->AddLabel(50, -20, std::string("x " + std::to_string(App->scene->player->stats.gold)).data(), inventory.coin_image, BLACK, FontType::FF64, nullptr, false);

	inventory.level_name_label = App->gui->AddLabel(76, 267, "Level:", inventory.inventory_panel, BLACK, FontType::FF64, nullptr, false);
	inventory.level_number_label = App->gui->AddLabel(65, 0, std::string("x " + std::to_string(App->scene->player->stats.level)).data(), inventory.level_name_label, BLACK, FontType::FF64, nullptr, false);

	inventory.exp_name_label = App->gui->AddLabel(55, 307, "Exp:", inventory.inventory_panel, BLACK, FontType::FF64, nullptr, false);
	inventory.exp_number_label = App->gui->AddLabel(50, 0, std::string(std::to_string(App->scene->player->stats.xp) + "/" + std::to_string(App->scene->player->stats.max_xp)).data(), inventory.exp_name_label, BLACK, FontType::FF64, nullptr, false);
}

void m1MenuManager::DestroyInventory()
{
	App->gui->DeleteUIElement(inventory.inventory_panel);
	App->gui->ShowCursor(false);
	//menu_state = StatesMenu::NO_MENU;
}

void m1MenuManager::CreatePotionMenu(u1GUI* potion_button)
{
	if (potion_button == inventory.hp_potion_button)
	{
		potion.potion_panel = App->gui->AddImage(-170, 50, { 1878, 1536, 170, 101 }, nullptr, inventory.inventory_panel, true, false, false, false);

		potion.use_hp_button = App->gui->AddButton(30, 0, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, App->scene, potion.potion_panel, false, false, true, true);
		potion.use_label = App->gui->AddLabel(50, -5, "Use", potion.potion_panel, BLACK, FontType::FF64, nullptr, false);

		potion.cancel_button = App->gui->AddButton(30, 43, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, App->scene, potion.potion_panel, false, false, true, true);
		potion.cancel_label = App->gui->AddLabel(50, 38, "Cancel", potion.potion_panel, BLACK, FontType::FF64, nullptr, false);

		App->gui->FocusButton(potion.use_hp_button);
	}

	else if (potion_button == inventory.mana_potion_button)
	{
		potion.potion_panel = App->gui->AddImage(-170, 100, { 1878, 1536, 170, 101 }, nullptr, inventory.inventory_panel, true, false, false, false);

		potion.use_mana_button = App->gui->AddButton(30, 0, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, App->scene, potion.potion_panel, false, false, true, true);
		potion.use_mana_button->AddListener(this);
		potion.use_label = App->gui->AddLabel(50, -5, "Use", potion.potion_panel, BLACK, FontType::FF64, nullptr, false);

		potion.cancel_button = App->gui->AddButton(30, 43, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, App->scene, potion.potion_panel, false, false, true, true);
		potion.cancel_button->AddListener(this);
		potion.cancel_label = App->gui->AddLabel(50, 38, "Cancel", potion.potion_panel, BLACK, FontType::FF64, nullptr, false);

		App->gui->FocusButton(potion.use_mana_button);
	}

	//menu_state = StatesMenu::POTION_MENU;
}

void m1MenuManager::DeletePotionMenu()
{
	App->gui->DeleteUIElement(potion.potion_panel);
	//menu_state = StatesMenu::INVENTORY_MENU;
}

void m1MenuManager::CreatePauseMenu()
{
	pause.pause_panel = App->gui->AddImage(0, 0, { 1252,1536,313,428 }, nullptr, App->gui->screen, true, false, false, false);
	pause.pause_panel->SetPosRespectParent(CENTERED);

	pause.button_resume = App->gui->AddButton(50, 50, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause.pause_panel, true, false, true, true);
	pause.label_resume = App->gui->AddLabel(0, 0, "Continue", pause.button_resume, BLACK, FontType::FF48, nullptr, false);
	pause.label_resume->SetPosRespectParent(CENTERED);

	pause.button_main_menu = App->gui->AddButton(50, 350, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause.pause_panel, true, false, true, true);
	pause.label_main_menu = App->gui->AddLabel(0, 0, "Return to main menu", pause.button_main_menu, BLACK, FontType::FF48, nullptr, false);
	pause.label_main_menu->SetPosRespectParent(CENTERED);

	//if (App->map->actual_map == Maps::LOBBY || App->map->actual_map == Maps::SHOP || App->map->actual_map == Maps::HOME)
	pause.button_abort_quest = App->gui->AddButton(50, 250, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause.pause_panel, true, false, false, false);
	//else
	//	pause.button_abort_quest = App->gui->AddButton(50, 250, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);


	pause.label_abort_quest = App->gui->AddLabel(0, 0, "Abort quest", pause.button_abort_quest, BLACK, FontType::FF48, nullptr, false);
	pause.label_abort_quest->SetPosRespectParent(CENTERED);


	pause.button_options = App->gui->AddButton(50, 150, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause.pause_panel, true, false, true, true);
	pause.label_options = App->gui->AddLabel(0, 0, "Options", pause.button_options, BLACK, FontType::FF48, nullptr, false);
	pause.label_options->SetPosRespectParent(CENTERED);
}

void m1MenuManager::DestroyPauseMenu()
{
	App->gui->DeleteUIElement(pause.pause_panel);
	pause.Reset();
	App->gui->ShowCursor(false);
}

void m1MenuManager::UpdateOptionsMenu()
{
	if (options.options_panel != nullptr) {
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
		App->scene->SetMenuState(StatesMenu::OPTIONS_MENU);
	}
}

void m1MenuManager::CreateShopMenu()
{
	App->scene->player->BlockControls(true);

	shop.shop_panel = App->gui->AddImage(100, 150, { 1820,1691,227,383 }, (m1Module*)App->scene, App->gui->screen, true, false, false, false);
	shop.shop_panel->SetPosRespectParent(LEFT_CENTERED, 200);
	shop.shop_label = App->gui->AddLabel(0, 0, "SHOP", shop.shop_panel, BLACK, FontType::FF64, nullptr, false);
	shop.shop_label->SetPosRespectParent(CENTERED_UP, 20);

	shop.button_close_shop = App->gui->AddButton(130, 330, { 1850,1637,75,35 }, { 1850,1637,55,35 }, { 1850,1637,55,35 }, App->scene, shop.shop_panel, false, false, true, true);
	shop.label_close_shop = App->gui->AddLabel(140, 321, "Return", shop.shop_panel, BLACK, FontType::FF48, nullptr, false);


	shop.shop_hp_potion_image = App->gui->AddImage(58, 101, { 1058, 1952, 33, 47 }, nullptr, shop.shop_panel, true, false, false, false);
	shop.shop_hp_potion_label = App->gui->AddLabel(102, 93, std::string("x " + std::to_string(App->scene->price_hp_potion)).data(), shop.shop_panel, BLACK, FontType::FF64, nullptr, false);
	shop.shop_coin1 = App->gui->AddImage(160, 112, { 1024, 1952, 34, 34 }, nullptr, shop.shop_panel, true, false, false, false);
	shop.shop_button_hp_potion = App->gui->AddButton(32, 100, { 0,0,180,50 }, { 0,0,180,50 }, { 0,0,180,50 }, App->scene, shop.shop_panel, false, false, true, true);

	shop.shop_mana_potion_image = App->gui->AddImage(58, 186, { 1091, 1952, 33, 51 }, nullptr, shop.shop_panel, true, false, false, false);
	shop.shop_mana_potion_label = App->gui->AddLabel(102, 178, std::string("x " + std::to_string(App->scene->price_mana_potion)).data(), shop.shop_panel, BLACK, FontType::FF64, nullptr, false);
	shop.shop_coin2 = App->gui->AddImage(160, 197, { 1024, 1952, 34, 34 }, nullptr, shop.shop_panel, true, false, false, false);
	shop.shop_button_mana_potion = App->gui->AddButton(32, 185, { 0,0,180,50 }, { 0,0,180,50 }, { 0,0,180,50 }, App->scene, shop.shop_panel, false, false, true, true);


	App->gui->FocusButton(shop.shop_button_hp_potion);

	CreateInventory();
	inventory.inventory_panel->SetPosRespectParent(RIGHT_CENTERED, 200);
	inventory.hp_potion_button->interactable = false;
	inventory.mana_potion_button->interactable = false;
}

void m1MenuManager::DestroyShopMenu()
{
	App->scene->player->BlockControls(false);
	App->gui->DeleteUIElement(shop.shop_panel);
	DestroyInventory();
	//menu_state = StatesMenu::NO_MENU;
}

void m1MenuManager::CreateDebugScreen()
{
	debug_screen.debug_screen = App->gui->AddImage(0, 0, App->gui->screen->section, nullptr, App->gui->screen, false, false, false, false);

	SDL_Color debug_background = { 0,0,0,150 };
	int debug_wrap_section = App->gui->screen->section.w * 0.3;

	debug_screen.project_name_label = App->gui->AddLabel(0, 0, App->GetTitle(), debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);
	debug_screen.version_label = App->gui->AddLabel(0, debug_screen.project_name_label->section.h, std::string(std::string("Version: ") + App->GetVersion()).data(), debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);
	debug_screen.fps_label = App->gui->AddLabel(0, debug_screen.version_label->position.y + debug_screen.version_label->section.h, "fps: 000 | dt: 000", debug_screen.project_name_label, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);

	debug_screen.textures_label = App->gui->AddLabel(0, debug_screen.fps_label->position.y + debug_screen.fps_label->section.h * 2, "textures:\nnumber of textures: %i",
		debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, debug_wrap_section, true, debug_background);

	debug_screen.map_label = App->gui->AddLabel(0, debug_screen.textures_label->position.y + debug_screen.textures_label->section.h + debug_screen.fps_label->section.h, "map:\nnumber of layers: %i\nnumber of tilesets: %i\nmap id: %i\nwidth: %i | height: %i\ntile width: %i | tile height: %i\ntiles drawn: %i\n menu state: %i",
		debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, debug_wrap_section, true, debug_background);

	debug_screen.entities_label = App->gui->AddLabel(0, debug_screen.map_label->position.y + debug_screen.map_label->section.h + debug_screen.fps_label->section.h * 2, "entities:\nnumber of entities: %i\nentities drawn: %i",
		debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, debug_wrap_section, true, debug_background);

	debug_screen.player_label = App->gui->AddLabel(0, debug_screen.entities_label->position.y + debug_screen.entities_label->section.h + debug_screen.fps_label->section.h, "player:\nposition: %i\ntile: %i\n movement type: %i\ndirection: %i\n state: %i",
		debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, debug_wrap_section, true, debug_background);

	debug_screen.mouse_label = App->gui->AddLabel(0, 0, "mouse:\nposition: (%i, %i)\nmotion: (%i, %i)\ntile: (%i, %i)\nUI Element selected:\nposition: (%i, %i)\nsection: (%i, %i)\nnumber of childs: %i\ntype: %i",
		debug_screen.debug_screen, WHITE, FontType::PMIX16, nullptr, false, debug_wrap_section, true, debug_background);
	debug_screen.mouse_label->SetPosRespectParent(Position_Type::RIGHT_UP);

}

void m1MenuManager::DestroyDebugScreen()
{
	App->gui->DeleteUIElement(debug_screen.debug_screen);

	debug_screen.debug_screen = nullptr;

	debug_screen.project_name_label = nullptr;
	debug_screen.version_label = nullptr;
	debug_screen.fps_label = nullptr;
	debug_screen.textures_label = nullptr;
	debug_screen.map_label = nullptr;
	debug_screen.player_label = nullptr;
	debug_screen.mouse_label = nullptr;
	debug_screen.entities_label = nullptr;
}

void m1MenuManager::UpdateDebugScreen()
{
	//BROFILER_CATEGORY("UpdateDebugScreen", Profiler::Color::Orange);

	debug_screen.fps_label->SetText(std::string("fps: " + std::to_string(App->GetFps()) + " | dt: " + std::to_string(App->GetDeltaTime())).data());

	debug_screen.textures_label->SetTextWrapped(std::string("textures:\nnumber of textures: " + std::to_string(App->tex->textures.size())).data());

	debug_screen.map_label->SetTextWrapped(std::string("map:\nnumber of layers: " + std::to_string(App->map->data.layers.size()) + "\nnumber of tilesets: " + std::to_string(App->map->data.tilesets.size()) +
		"\nmap id: " + std::to_string((int)App->map->actual_map) + "\nwidth: " + std::to_string(App->map->data.width) + " | height: " + std::to_string(App->map->data.height) + "\ntile width: "
		+ std::to_string(App->map->data.tile_width) + "\ntile height: " + std::to_string(App->map->data.tile_height) + "\ntiles drawn: " + std::to_string(App->map->last_tiles_drawn) +
		"\nmenu state : " + std::to_string((int)App->scene->menu_state)).data());

	debug_screen.entities_label->SetTextWrapped(std::string("entities:\nnumber of entities: " + std::to_string(App->entity_manager->GetEntities().size()) + "\nentities drawn: " + std::to_string(App->entity_manager->entities_drawn)).data());

	if (App->scene->player != nullptr) {
		debug_screen.player_label->SetTextWrapped(std::string("player:\nposition: (" + std::to_string(App->scene->player->position.x) + ", " + std::to_string(App->scene->player->position.y) +
			")\ntile: (" + std::to_string(App->scene->player->actual_tile.x) + ", " + std::to_string(App->scene->player->actual_tile.y) + ")\nmovement type: " + std::to_string((int)App->scene->player->movement_type) +
			"\ndirection: " + std::to_string((int)App->scene->player->direction) + "\nstate: " + std::to_string((int)App->scene->player->state)).data());
	}

	int x = 0, y = 0, m_x = 0, m_y = 0;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(m_x, m_y);
	iPoint tile = App->map->WorldToMap(x, y);

	const u1GUI* focus = App->gui->GetFocus();

	if (focus == nullptr) {
		debug_screen.mouse_label->SetTextWrapped(std::string("mouse:\nposition: (" + std::to_string(x*App->win->GetScale()) + ", " + std::to_string(y*App->win->GetScale()) +
			")\nmotion: (" + std::to_string(m_x) + ", " + std::to_string(m_y) +
			")\ntile: (" + std::to_string(tile.x) + ", " + std::to_string(tile.y) +
			")\nUI Element selected:\nposition: (00, 00)\nsection: (00, 00)\nnumber of childs: 00\ntype: unknown").data());
	}
	else {
		debug_screen.mouse_label->SetTextWrapped(std::string("mouse:\nposition: (" + std::to_string(x*App->win->GetScale()) + ", " + std::to_string(y*App->win->GetScale()) +
			")\nmotion: (" + std::to_string(m_x) + ", " + std::to_string(m_y) +
			")\ntile: (" + std::to_string(tile.x) + ", " + std::to_string(tile.y) +
			")\nUI Element selected:\nposition: (" + std::to_string(focus->position.x) + ", " + std::to_string(focus->position.y) +
			")\nsection: (" + std::to_string(focus->section.w) + ", " + std::to_string(focus->section.w) +
			")\nnumber of childs: " + std::to_string(focus->childs.size()) + "\ntype: " + std::to_string((int)focus->GetType())).data());
	}

}

void m1MenuManager::CreateGameOver()
{
	App->audio->PlayMusic(App->scene->mus_game_over, 0.5);
	game_over.game_over_panel = App->gui->AddImage(0, 0, { 1024, 0, 1024, 768 }, nullptr, App->gui->screen, true, false, false, false);
	game_over.game_over_panel->SetPosRespectParent(CENTERED);

	game_over.button_continue_lobby = App->gui->AddButton(150, 500, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->scene, game_over.game_over_panel, false, false, true, true);
	game_over.label_continue_lobby = App->gui->AddLabel(0, 0, "Continue", game_over.button_continue_lobby, WHITE, FontType::FF100, nullptr, false);
	game_over.label_continue_lobby->SetPosRespectParent(LEFT_CENTERED);


	game_over.button_return_main = App->gui->AddButton(610, 500, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, App->scene, game_over.game_over_panel, false, false, true, true);
	game_over.label_continue_main = App->gui->AddLabel(0, 0, "Return Main Menu", game_over.button_return_main, WHITE, FontType::FF100, nullptr, false);
	game_over.label_continue_main->SetPosRespectParent(LEFT_CENTERED);
}

void m1MenuManager::DestroyGameOver()
{
	App->gui->DeleteUIElement(game_over.game_over_panel);
}

void m1MenuManager::CreateHelpDiagonalMenu()
{
	App->audio->PlayFx(App->scene->fx_ability_screen);
	help_diagonal = App->gui->AddImage(0, 0, { 0,6329,1024,768 }, nullptr, App->gui->screen, true, false, false, false);

}

void m1MenuManager::DestroyHelpDiagonalMenu()
{
	App->gui->DeleteUIElement(help_diagonal);
}

void m1MenuManager::CreateHelpAttackMenu()
{
	App->audio->PlayFx(App->scene->fx_ability_screen);
	help_attack = App->gui->AddImage(0, 0, { 1024,6329,1024,768 }, nullptr, App->gui->screen, true, false, false, false);
}

void m1MenuManager::DestroyHelpAttackMenu()
{
	App->gui->DeleteUIElement(help_attack);
}

void m1MenuManager::CreateHelpAbilityMenu()
{
	App->audio->PlayFx(App->scene->fx_ability_screen);
	//switch (player_type) {
	//case PlayerType::WARRIOR:
		help_ability = App->gui->AddImage(0, 0, { 0,4792,1024,768 }, nullptr, App->gui->screen, true, false, false, false);
	/*	break;
	case PlayerType::MAGE:
		help_ability = App->gui->AddImage(0, 0, { 1024,7096,1024,768 }, nullptr, App->gui->screen, true, false, false, false);
		break;
	case PlayerType::ARCHER:
		help_ability = App->gui->AddImage(0, 0, { 0,7096,1024,768 }, nullptr, App->gui->screen, true, false, false, false);
		break;
	default:
		help_ability = App->gui->AddImage(0, 0, { 0,4792,1024,768 }, nullptr, App->gui->screen, true, false, false, false);
		break;
	}*/
}

void m1MenuManager::DestroyHelpAbilityMenu()
{

	App->gui->DeleteUIElement(help_ability);
}

void m1MenuManager::CreateFirstAbilityPanel()
{
	App->audio->PlayFx(App->scene->fx_ability_screen);

	App->gui->ShowCursor(false);

	//switch (player_type) {
	//case PlayerType::WARRIOR:
	abilities.first_ability_panel = App->gui->AddImage(0, 0, { 0, 4792, 1025, 768 }, nullptr, App->gui->screen, true, false, false, false);
	abilities.first_ability_panel->SetPosRespectParent(RIGHT_CENTERED);
	//	break;
	//case PlayerType::ARCHER:
	//	first_ability_panel = App->gui->AddImage(0, 0, { 0, 4792, 1025, 768 }, this, App->gui->screen, true, false, false, false);
	//	first_ability_panel->SetPosRespectParent(RIGHT_CENTERED);
	//	break;
	//case PlayerType::MAGE:
	//	first_ability_panel = App->gui->AddImage(0, 0, { 0, 4792, 1025, 768 }, this, App->gui->screen, true, false, false, false);
	//	first_ability_panel->SetPosRespectParent(RIGHT_CENTERED);
	//	break;
	//}

	abilities.button_ability1_screen = App->gui->AddButton(800, 600, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, App->scene, abilities.first_ability_panel, false, false, true, true);
	abilities.label_ability1_screen = App->gui->AddLabel(0, 0, "Continue", abilities.button_ability1_screen, WHITE, FontType::FF100, nullptr, true);

}

void m1MenuManager::DestroyFirstAbilityPanel()
{
	App->gui->DeleteUIElement(abilities.first_ability_panel);
}

void m1MenuManager::GodModeIndicator(bool is_god_mode)
{
	if (is_god_mode)
	{
		god_text = App->gui->AddLabel(50, 0, "GOD MODE", App->gui->screen, RED, FontType::FF64, nullptr, false);
	}
	else
	{
		App->gui->DeleteUIElement(god_text);
		god_text = nullptr;
	}
}

void m1MenuManager::SkipMenu(bool is_cutscene)
{
	if (is_cutscene)
	{
		im_skipper = App->gui->AddImage(880, 700, { 1522,2051,33,31 }, nullptr, App->gui->screen, true, false, false, false);
		lb_skipper = App->gui->AddLabel(924, 698,"Skip", App->gui->screen, WHITE, FontType::PMIX32, nullptr,true);
	}
	else
	{
		App->gui->DeleteUIElement(lb_skipper);
		lb_skipper = nullptr;
		App->gui->DeleteUIElement(im_skipper);
		im_skipper = nullptr;
	}
}

bool m1MenuManager::Interact(u1GUI * interaction)
{
	bool ret = true;

	// PAUSE ========================================================================================================

	if (interaction == pause.button_resume)
	{
		App->audio->PlayFx(App->main_menu->fx_push_button_return);
		DestroyPauseMenu();
		App->scene->SetMenuState(StatesMenu::NO_MENU);
		if (App->GetPause())
			App->ChangePause();
		App->scene->ShowHUD(true);
		ret = false;
		App->scene->player->BlockControls(false);
	}
	if (interaction == pause.button_main_menu)
	{
		DestroyDebugScreen();
		App->gui->DeleteAllUIElements();
		App->entity_manager->Disable();
		App->map->Disable();
		App->ChangePause();
		active = false;
		App->main_menu->Enable();
		ret = false;
	}
	if (interaction == pause.button_options)
	{
		CreateOptions();
		DestroyPauseMenu();
		App->scene->SetMenuState(StatesMenu::OPTIONS_MENU);
		App->scene->ShowHUD(false);
		ret = false;
	}

	// CONTROLS =====================================================================================================
	if (interaction == controls.button_retun_to_options) {
		//App->audio->PlayFx(fx_push_button_return);
		CreateOptions();
		App->scene->SetMenuState(StatesMenu::OPTIONS_MENU);
		DestroyControls();
		ret = false;
	}
	/*else if (interaction == button_up) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_up, &App->input->keyboard_buttons.buttons_code.UP, &App->input->keyboard_buttons.buttons_char.UP, false);
	}
	else if (interaction == button_right) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_right, &App->input->keyboard_buttons.buttons_code.RIGHT, &App->input->keyboard_buttons.buttons_char.RIGHT, false);
	}
	else if (interaction == button_left) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_left, &App->input->keyboard_buttons.buttons_code.LEFT, &App->input->keyboard_buttons.buttons_char.LEFT, false);
	}
	else if (interaction == button_down) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_down, &App->input->keyboard_buttons.buttons_code.DOWN, &App->input->keyboard_buttons.buttons_char.DOWN, false);
	}
	else if (interaction == button_diagonals) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_diagonals, &App->input->keyboard_buttons.buttons_code.DIAGONALS, &App->input->keyboard_buttons.buttons_char.DIAGONALS, false);
	}
	else if (interaction == button_direction_up) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_up, &App->input->keyboard_buttons.buttons_code.DIRECTION_UP, &App->input->keyboard_buttons.buttons_char.DIRECTION_UP, false);
	}
	else if (interaction == button_direction_right) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_right, &App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT, &App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, false);
	}
	else if (interaction == button_direction_left) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_left, &App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT, &App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, false);
	}
	else if (interaction == button_direction_down) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_direction_down, &App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN, &App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, false);
	}
	else if (interaction == button_basic_attack) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(label_to_show_how_basic_attack, &App->input->keyboard_buttons.buttons_code.BASIC_ATTACK, &App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, false);
	}
	else if (interaction == Cbutton_direction_up) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_up, &App->input->controller_Buttons.buttons_code.DIRECTION_UP, &App->input->controller_Buttons.buttons_char.DIRECTION_UP, true);
	}
	else if (interaction == Cbutton_direction_right) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_right, &App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT, &App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, true);
	}
	else if (interaction == Cbutton_direction_left) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_left, &App->input->controller_Buttons.buttons_code.DIRECTION_LEFT, &App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, true);
	}
	else if (interaction == Cbutton_direction_down) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_direction_down, &App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN, &App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, true);
	}
	else if (interaction == Cbutton_diagonals) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_diagonals, &App->input->controller_Buttons.buttons_code.DIAGONALS, &App->input->controller_Buttons.buttons_char.DIAGONALS, true);
	}
	else if (interaction == Cbutton_basic_attack) {
		if (App->scene->control_to_change != nullptr)
			delete App->scene->control_to_change;
		App->scene->control_to_change = DBG_NEW ChangeControls(Clabel_to_show_how_basic_attack, &App->input->controller_Buttons.buttons_code.BASIC_ATTACK, &App->input->controller_Buttons.buttons_char.BASIC_ATTACK, true);
	}*/

	//OPTIONS ======================================================================================================================================

	else if (interaction == options.button_retun_options) {
		App->audio->PlayFx(App->main_menu->fx_push_button_return);
		DestroyOptions();

		//_STL_ASSERT(App->main_menu->active != App->scene->active, "main menu and scene are both active or deactive");
		if(App->main_menu->active){
			CreateMainMenu();
		}
		else if (App->scene->active) {
			CreatePauseMenu();
			App->scene->ShowHUD(true);
			App->scene->SetMenuState(StatesMenu::PAUSE_MENU);
		}

		ret = false;
	}
	else if (interaction == options.button_controls) {
		CreateControls();
		DestroyOptions();
		if (App->scene->active)
			App->scene->SetMenuState(StatesMenu::CONTROLS_MENU);
		ret = false;
	}
	else if (interaction == options.checkbox_mute_music)
	{
		options.checkbox_mute_music->Clicked();
		App->audio->StopMusic(-2);
	}

	else if (interaction == options.checkbox_mute_fx)
	{
		options.checkbox_mute_fx->Clicked();
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

	else if (interaction == options.checkbox_fullscreen)
	{
		options.checkbox_fullscreen->Clicked();
		App->win->ChangeFullScreen();
	}
	else if (interaction == options.button_music_volume) {
		App->audio->StopMusic(-2);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.button_fx_volume) {
		App->audio->StopMusic(-3);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.minus_music_btn) {
		App->audio->VolumeDown(-2);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.plus_music_btn) {
		App->audio->VolumeUp(-2);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.minus_fx_btn) {
		App->audio->VolumeDown(-3);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.plus_fx_btn) {
		App->audio->VolumeUp(-3);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.minus_general_btn) {
		App->audio->VolumeDown(-1);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	else if (interaction == options.plus_general_btn) {
		App->audio->VolumeUp(-1);
		options.label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
		options.label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
		options.label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());
	}
	return ret;
}

void m1MenuManager::ManageInputText(u1GUI *& interaction)
{
	if (interaction == input.button_upper) {
		input.minus_letters->drawable = false;
		input.max_letters->drawable = true;
	}
	else if (interaction == input.button_lower) {
		input.minus_letters->drawable = true;
		input.max_letters->drawable = false;
	}
	else if (interaction == input.button_A) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("a");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("A");
		}
	}
	else if (interaction == input.button_B) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("b");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("B");
		}
	}
	else if (interaction == input.button_C) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("c");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("C");
		}
	}
	else if (interaction == input.button_D) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("d");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("D");
		}
	}
	else if (interaction == input.button_E) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("e");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("E");
		}
	}
	else if (interaction == input.button_F) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("f");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("F");
		}
	}
	else if (interaction == input.button_H) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("h");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("H");
		}
	}
	else if (interaction == input.button_G) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("g");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("G");
		}
	}
	else if (interaction == input.button_I) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("i");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("I");
		}
	}
	else if (interaction == input.button_J) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("j");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("J");
		}
	}
	else if (interaction == input.button_K) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("k");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("K");
		}
	}
	else if (interaction == input.button_L) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("l");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("L");
		}
	}
	else if (interaction == input.button_M) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("m");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("M");
		}
	}
	else if (interaction == input.button_N) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("n");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("N");
		}
	}
	else if (interaction == input.button_O) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("o");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("O");
		}
	}
	else if (interaction == input.button_P) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("p");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("P");
		}
	}
	else if (interaction == input.button_Q) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("q");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("Q");
		}
	}
	else if (interaction == input.button_R) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("r");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("R");
		}
	}
	else if (interaction == input.button_S) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("s");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("S");
		}
	}
	else if (interaction == input.button_T) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("t");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("T");
		}
	}
	else if (interaction == input.button_U) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("u");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("U");
		}
	}
	else if (interaction == input.button_V) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("v");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("V");
		}
	}
	else if (interaction == input.button_W) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("w");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("W");
		}
	}
	else if (interaction == input.button_X) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("x");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("X");
		}
	}
	else if (interaction == input.button_Y) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("y");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("Y");
		}
	}
	else if (interaction == input.button_Z) {
		if (input.minus_letters->drawable) {
			input.input_text->AddText("z");
		}
		else if (input.max_letters->drawable) {
			input.input_text->AddText("Z");
		}
	}
	else if (interaction == input.button_Delete) {
		input.input_text->DeleteText();
	}
	else if (interaction == input.button_Space) {
		input.input_text->AddText(" ");
	}
}