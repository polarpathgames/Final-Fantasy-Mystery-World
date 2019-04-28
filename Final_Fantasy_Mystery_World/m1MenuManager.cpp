#include "m1MenuManager.h"
#include "App.h"
#include "m1GUI.h"
#include "u1Image.h"
#include "u1Button.h"
#include "u1InputText.h"

void m1MenuManager::CreateMainMenu()
{
	main_menu.background = App->gui->AddImage(0, 0, { 0, 0, 1024, 768 }, this, App->gui->screen, true, false, false, false);
	int offsetY = 75;

	main_menu.new_game_button = App->gui->AddButton(684, 337, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, main_menu.background, false, false, true, true);
	main_menu.new_game_label = App->gui->AddLabel(0, 0, "New Game", main_menu.new_game_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.new_game_label->SetPosRespectParent(CENTERED);

	main_menu.load_game_button = App->gui->AddButton(684, main_menu.new_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, main_menu.background, false, false, true, true);
	main_menu.load_game_label = App->gui->AddLabel(0, 0, "Load Game", main_menu.load_game_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.load_game_label->SetPosRespectParent(CENTERED);

	main_menu.options_button = App->gui->AddButton(684, main_menu.load_game_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, main_menu.background, false, false, true, true);
	main_menu.options_label = App->gui->AddLabel(0, 0, "Options", main_menu.options_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.options_label->SetPosRespectParent(CENTERED);

	main_menu.credits_button = App->gui->AddButton(684, main_menu.options_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, main_menu.background, false, false, true, true);
	main_menu.credits_label = App->gui->AddLabel(0, 0, "Credits", main_menu.credits_button, BLACK, FontType::FF64, nullptr, false);
	main_menu.credits_label->SetPosRespectParent(CENTERED);

	main_menu.exit_game_button = App->gui->AddButton(684, main_menu.credits_button->position.y + offsetY, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, main_menu.background, false, false, true, true);
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
	App->audio->PlayMusic(mus_credits, 0.5);
	credits_panel = App->gui->AddImage(0, 0, { 0, 2304, 1024, 768 }, this, App->gui->screen, true, false, false, false);
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
	label_nadine = App->gui->AddLabel(0, 0, "Nadine Gutierrez - Art", button_nadine, WHITE, FontType::FF100, nullptr, false);
	label_nadine->SetPosRespectParent(LEFT_CENTERED);

	button_ivan = App->gui->AddButton(555, 450, { 1850,1637,350,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_ivan = App->gui->AddLabel(0, 0, "Ivan Ropero - QA", button_ivan, WHITE, FontType::FF100, nullptr, false);
	label_ivan->SetPosRespectParent(LEFT_CENTERED);

	button_credits_return_menu = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, credits_panel, false, false, true, true);
	label_credits_return_menu = App->gui->AddLabel(0, 0, "Return", button_credits_return_menu, WHITE, FontType::FF64, nullptr, false);
	label_credits_return_menu->SetPosRespectParent(CENTERED);

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

void m1MenuManager::DestroyCredits()
{
	App->gui->DeleteUIElement(credits_panel);
}

void m1MenuManager::CreateSelectChamp()
{

	select_champ_panel = App->gui->AddImage(0, 0, { 1024, 3256, 1024, 768 }, this, App->gui->screen, true, false, false, false);

	warrior_image = App->gui->AddImage(500, 175, { 1052, 4079, 327, 358 }, App->main_menu, select_champ_panel, true, false, false, false);
	archer_image = App->gui->AddImage(580, 180, { 1681, 4050, 244, 400 }, App->main_menu, select_champ_panel, false, false, false, false);
	mage_image = App->gui->AddImage(580, 180, { 1414, 4079, 218, 363 }, App->main_menu, select_champ_panel, false, false, false, false);

	warrior_info = App->gui->AddImage(370, 600, { 99, 4120, 585, 97 }, App->main_menu, select_champ_panel, true, false, false, false);
	archer_info = App->gui->AddImage(370, 600, { 99, 4273, 537, 97 }, App->main_menu, select_champ_panel, false, false, false, false);
	mage_info = App->gui->AddImage(370, 600, { 98, 4414, 518, 97 }, App->main_menu, select_champ_panel, false, false, false, false);

	button_warrior = App->gui->AddChButton(100, 250, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::WARRIOR, true, false, true, true);
	label_warrior = App->gui->AddLabel(65, -13, "Warrior", button_warrior, BLACK, FontType::FF64, nullptr, false);
	button_archer = App->gui->AddChButton(100, 350, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::ARCHER, true, false, true, true);
	label_archer = App->gui->AddLabel(68, -13, "Archer", button_archer, BLACK, FontType::FF64, nullptr, false);
	button_mage = App->gui->AddChButton(100, 450, { 1850,1637,198,50 }, { 1569,1688,198,50 }, { 1569,1756,198,50 }, this, select_champ_panel, PlayerType::MAGE, true, false, true, true);
	label_mage = App->gui->AddLabel(75, -13, "Mage", button_mage, BLACK, FontType::FF64, nullptr, false);

	App->audio->PlayMusic(mus_selection, 0.5);

	return_select_champ_button = App->gui->AddButton(120, 640, { 1000, 1000, 80, 50 }, { 1000, 1000, 80, 50 }, { 1000, 1000, 80, 50 }, this, select_champ_panel, false, false, true, true, { -10, 3 });
	return_select_champ_label = App->gui->AddLabel(0, 0, "Return", return_select_champ_button, BLACK, FontType::FF64, this, false);

	App->gui->FocusButton((u1Button*)button_warrior);


}

void m1MenuManager::DestroySelectChamp()
{
	App->gui->DeleteUIElement(select_champ_panel);
}

void m1MenuManager::CreateOptions()
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

	checkbox_mute_music = App->gui->AddCheckBox(900, 263, { 1618, 1834, 33, 33 }, { 1618, 1834, 33, 33 }, { 1581, 1836, 26, 29 }, options_panel);
	checkbox_mute_music->is_option = true;
	checkbox_mute_music->box_clicked = App->audio->mute_volume;
	checkbox_mute_music->draggable = false;
	checkbox_mute_music->drawable = true;
	checkbox_mute_music->interactable = true;
	checkbox_mute_music->AddListener(this);

	button_fx_volume = App->gui->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_fx_volume = App->gui->AddLabel(0, 0, "FX Volume", button_fx_volume, BLACK, FontType::FF48, nullptr, false);
	label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	minus_fx_btn = App->gui->AddButton(715, 343, { 1699,1575,33,33 }, { 1699,1575,33,33 }, { 1699,1575,33,33 }, this, options_panel, true, false, true, true);
	plus_fx_btn = App->gui->AddButton(805, 343, { 1735,1575,33,33 }, { 1735,1575,33,33 }, { 1735,1575,33,33 }, this, options_panel, true, false, true, true);
	label_fx_value = App->gui->AddLabel(760, 330, "", options_panel, BLACK, FontType::FF48, nullptr, false);

	checkbox_mute_fx = App->gui->AddCheckBox(900, 343, { 1618, 1834, 33, 33 }, { 1618, 1834, 33, 33 }, { 1581, 1836, 26, 29 }, options_panel);
	checkbox_mute_fx->is_option = true;
	checkbox_mute_fx->box_clicked = App->audio->mute_fx;
	checkbox_mute_fx->draggable = false;
	checkbox_mute_fx->drawable = true;
	checkbox_mute_fx->interactable = true;
	checkbox_mute_fx->AddListener(this);

	/*label_fps = App->gui->AddLabel(491, 413, "FPS Caps", options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fps = App->gui->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->box_clicked = App->capactivated;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);*/

	label_fullscreen = App->gui->AddLabel(491, 413, "Fullscreen", options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fullscreen = App->gui->AddCheckBox(760, 420, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fullscreen->is_option = true;
	checkbox_fullscreen->box_clicked = App->win->fullscreen;
	checkbox_fullscreen->draggable = false;
	checkbox_fullscreen->drawable = true;
	checkbox_fullscreen->interactable = true;
	checkbox_fullscreen->AddListener(this);

	button_controls = App->gui->AddButton(491, 503, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_controls = App->gui->AddLabel(0, 0, "Controls", button_controls, BLACK, FontType::FF48, nullptr, false);
	label_controls->SetPosRespectParent(LEFT_CENTERED);

	button_retun_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_return_options = App->gui->AddLabel(0, 0, "Return", button_retun_options, BLACK, FontType::FF48, nullptr, false);
	label_return_options->SetPosRespectParent(CENTERED);

	label_fx_value->SetText(std::string(std::to_string(App->audio->volume_fx)).data());
	label_music_value->SetText(std::string(std::to_string(App->audio->volume)).data());
	label_general_value->SetText(std::string(std::to_string(App->audio->volume_general)).data());

}

void m1MenuManager::DestroyOptions()
{
	App->gui->DeleteUIElement(options_panel);

}

void m1MenuManager::CreateControls()
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

void m1MenuManager::DestroyControls()
{
	App->scene->control_to_change = nullptr;
	App->gui->DeleteUIElement(controls_panel);

	App->scene->labels_control.clear();
	App->scene->Clabels_control.clear();
}

void m1MenuManager::CreateNameMenu()
{
	input_text_image = App->gui->AddImage(0, 0, { 1025, 4792, 1024, 768 }, this, App->gui->screen, true, false, false, false);



	minus_letters = App->gui->AddImage(137, 350, { 1024,5658,743,334 }, nullptr, input_text_image, true, false, false, false);
	max_letters = App->gui->AddImage(137, 350, { 119,5658,743,334 }, nullptr, input_text_image, false, false, false, false);

	// 
	button_A = App->gui->AddButton(0, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_B = App->gui->AddButton(94, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_C = App->gui->AddButton(188, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_D = App->gui->AddButton(282, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_E = App->gui->AddButton(378, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_F = App->gui->AddButton(471, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_G = App->gui->AddButton(565, 0, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_upper = App->gui->AddButton(662, 0, { 0,0,80,47 }, { 0,0,80,47 }, { 0,0,80,47 }, this, max_letters, false, false, true, true, { -2,-5 });
	input_text = App->gui->AddInputText(52, -91, "", max_letters, BLACK, FontType::FF64, { 1214,5050,600,63 }, this);
	//
	button_H = App->gui->AddButton(0, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_I = App->gui->AddButton(94, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_J = App->gui->AddButton(188, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_K = App->gui->AddButton(282, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_L = App->gui->AddButton(378, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_M = App->gui->AddButton(471, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_N = App->gui->AddButton(565, 74, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_lower = App->gui->AddButton(662, 74, { 0,0,80,47 }, { 0,0,80,47 }, { 0,0,80,47 }, this, max_letters, false, false, true, true, { -2,-5 });
	//
	button_O = App->gui->AddButton(0, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_P = App->gui->AddButton(94, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_Q = App->gui->AddButton(188, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_R = App->gui->AddButton(282, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_S = App->gui->AddButton(378, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_T = App->gui->AddButton(471, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_U = App->gui->AddButton(565, 148, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_okay = App->gui->AddButton(662, 148, { 0, 0, 60, 47 }, { 0, 0, 60, 47 }, { 0, 0, 60, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	//
	button_V = App->gui->AddButton(0, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_W = App->gui->AddButton(94, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_X = App->gui->AddButton(188, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_Y = App->gui->AddButton(282, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_Z = App->gui->AddButton(378, 223, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, { 0, 0, 47, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	button_Delete = App->gui->AddButton(471, 223, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, this, max_letters, false, false, true, true, { -2,-5 });
	//
	button_Space = App->gui->AddButton(188, 295, { 0, 0, 235, 40 }, { 0, 0, 93, 47 }, { 0, 0, 93, 47 }, this, max_letters, false, false, true, true, { -2,-5 });

	App->gui->FocusButton((u1Button*)input_text);

}

void m1MenuManager::DestroyNameMenu()
{
	App->gui->DeleteUIElement(input_text_image);
}

bool m1MenuManager::Interact(u1GUI * interaction)
{
	bool ret = true;
	if (interaction == controls.button_retun_to_options) {
		//App->audio->PlayFx(fx_push_button_return);
		CreateOptions();
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