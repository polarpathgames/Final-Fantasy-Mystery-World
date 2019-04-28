#ifndef __M1MENUMANAGER_H__
#define __M1MENUMANAGER_H__

#include "m1Module.h"

class u1InputText;
class u1Image;
class u1Button;
class u1Label;
class u1CheckBox;
class u1ChButton;

struct UI_input {
	u1InputText* input_text = nullptr;
	u1Image* input_text_image = nullptr;
	u1Button* button_okay = nullptr;
	u1Button* button_upper = nullptr;
	u1Button* button_lower = nullptr;
	u1Image* minus_letters = nullptr;
	u1Image* max_letters = nullptr;
	u1Button* button_A = nullptr;
	u1Button* button_B = nullptr;
	u1Button* button_C = nullptr;
	u1Button* button_D = nullptr;
	u1Button* button_E = nullptr;
	u1Button* button_F = nullptr;
	u1Button* button_G = nullptr;
	u1Button* button_H = nullptr;
	u1Button* button_I = nullptr;
	u1Button* button_J = nullptr;
	u1Button* button_K = nullptr;
	u1Button* button_L = nullptr;
	u1Button* button_M = nullptr;
	u1Button* button_N = nullptr;
	u1Button* button_O = nullptr;
	u1Button* button_P = nullptr;
	u1Button* button_Q = nullptr;
	u1Button* button_R = nullptr;
	u1Button* button_S = nullptr;
	u1Button* button_T = nullptr;
	u1Button* button_U = nullptr;
	u1Button* button_V = nullptr;
	u1Button* button_W = nullptr;
	u1Button* button_X = nullptr;
	u1Button* button_Y = nullptr;
	u1Button* button_Z = nullptr;
	u1Button* button_Delete = nullptr;
	u1Button* button_Space = nullptr;

	u1Button* return_btn_input_screen = nullptr;
	u1Label* return_label_input_screen = nullptr;
};

struct UI_main_menu {
	u1GUI* background = nullptr;

	u1Button* new_game_button = nullptr;
	u1Label* new_game_label = nullptr;

	u1Button* load_game_button = nullptr;
	u1Label* load_game_label = nullptr;

	u1Button* options_button = nullptr;
	u1Label* options_label = nullptr;

	u1Button* credits_button = nullptr;
	u1Label* credits_label = nullptr;

	u1Button* exit_game_button = nullptr;
	u1Label* exit_game_text = nullptr;

	void Reset() {
		background = nullptr;
		new_game_button = nullptr;
		new_game_label = nullptr;
		load_game_button = nullptr;
		load_game_label = nullptr;
		options_button = nullptr;
		options_label = nullptr;
		credits_button = nullptr;
		credits_label = nullptr;
		credits_panel = nullptr;
		exit_game_button = nullptr;
		exit_game_text = nullptr;
	}

};

struct UI_credits {
	u1Image* credits_panel = nullptr;

	u1Button* button_christian = nullptr;
	u1Label* label_christian = nullptr;
	u1Button* button_lluis = nullptr;
	u1Label* label_lluis = nullptr;
	u1Button* button_marc = nullptr;
	u1Label* label_marc = nullptr;
	u1Button* button_enric = nullptr;
	u1Label* label_enric = nullptr;
	u1Button* button_nadine = nullptr;
	u1Label* label_nadine = nullptr;
	u1Button* button_ivan = nullptr;
	u1Label* label_ivan = nullptr;
	u1Button* button_oriol = nullptr;
	u1Label* label_oriol = nullptr;

	u1Button* button_github = nullptr;
	u1Label* label_github = nullptr;

	u1Button* button_twitter = nullptr;
	u1Label* label_twitter = nullptr;

	u1Button* button_youtube = nullptr;
	u1Label* label_youtube = nullptr;

	u1Button* button_credits_return_menu = nullptr;
	u1Label* label_credits_return_menu = nullptr;

	void Reset() {
		credits_panel = nullptr;
		button_christian = nullptr;
		label_christian = nullptr;
		button_lluis = nullptr;
		label_lluis = nullptr;
		button_marc = nullptr;
		label_marc = nullptr;
		button_enric = nullptr;
		label_enric = nullptr;
		button_nadine = nullptr;
		label_nadine = nullptr;
		button_ivan = nullptr;
		label_ivan = nullptr;
		button_oriol = nullptr;
		label_oriol = nullptr;
		button_github = nullptr;
		label_github = nullptr;
		button_twitter = nullptr;
		label_twitter = nullptr;
		button_youtube = nullptr;
		label_youtube = nullptr;
		button_credits_return_menu = nullptr;
		label_credits_return_menu = nullptr;
	}
};

struct UI_options {
	u1Image* options_panel = nullptr;

	u1Label* label_general_volume = nullptr;
	u1Button* button_general_volume = nullptr;
	u1Button* minus_general_btn = nullptr;
	u1Button* plus_general_btn = nullptr;
	u1Label* label_general_value = nullptr;

	u1Label* label_music_volume = nullptr;
	u1Button* button_music_volume = nullptr;
	u1Button* minus_music_btn = nullptr;
	u1Button* plus_music_btn = nullptr;
	u1Label* label_music_value = nullptr;

	u1Label* label_fx_volume = nullptr;
	u1Button* button_fx_volume = nullptr;
	u1Button* minus_fx_btn = nullptr;
	u1Button* plus_fx_btn = nullptr;
	u1Label* label_fx_value = nullptr;

	/*u1Label* label_fps = nullptr;
	u1CheckBox* checkbox_fps = nullptr;*/
	u1Label* label_fullscreen = nullptr;
	u1CheckBox* checkbox_fullscreen = nullptr;
	u1Button* button_controls = nullptr;
	u1Label* label_controls = nullptr;

	u1Button* button_retun_options = nullptr;
	u1Label* label_return_options = nullptr;

	u1CheckBox* checkbox_mute_music = nullptr;
	u1CheckBox* checkbox_mute_fx = nullptr;
};

struct UI_controls_keyboard{
	u1Label* keyboard = nullptr;

	u1Button* button_basic_attack = nullptr;
	u1Label* label_basic_attack = nullptr;
	u1Label* label_to_show_how_basic_attack = nullptr;

	u1Button* button_up = nullptr;
	u1Label* label_up = nullptr;
	u1Label* label_to_show_how_up = nullptr;

	u1Button* button_right = nullptr;
	u1Label* label_right = nullptr;
	u1Label* label_to_show_how_right = nullptr;

	u1Button* button_left = nullptr;
	u1Label* label_left = nullptr;
	u1Label* label_to_show_how_left = nullptr;

	u1Button* button_down = nullptr;
	u1Label* label_down = nullptr;
	u1Label* label_to_show_how_down = nullptr;

	u1Button* button_diagonals = nullptr;
	u1Label* label_diagonals = nullptr;
	u1Label* label_to_show_how_diagonals = nullptr;

	u1Button* button_direction_up = nullptr;
	u1Label* label_direction_up = nullptr;
	u1Label* label_to_show_how_direction_up = nullptr;

	u1Button* button_direction_right = nullptr;
	u1Label* label_direction_right = nullptr;
	u1Label* label_to_show_how_direction_right = nullptr;

	u1Button* button_direction_left = nullptr;
	u1Label* label_direction_left = nullptr;
	u1Label* label_to_show_how_direction_left = nullptr;

	u1Button* button_direction_down = nullptr;
	u1Label* label_direction_down = nullptr;
	u1Label* label_to_show_how_direction_down = nullptr;

	u1Button* button_inventory = nullptr;
	u1Label* label_inventory = nullptr;
	u1Label* label_to_show_how_inventory = nullptr;

	u1Button* button_interact = nullptr;
	u1Label* label_interact = nullptr;
	u1Label* label_to_show_how_interact = nullptr;

	u1Button* button_abilities = nullptr;
	u1Label* label_abilities = nullptr;
	u1Label* label_to_show_how_abilities = nullptr;

	u1Button* button_ability1 = nullptr;
	u1Label* label_ability1 = nullptr;
	u1Label* label_to_show_how_ability1 = nullptr;

	u1Button* button_ability2 = nullptr;
	u1Label* label_ability2 = nullptr;
	u1Label* label_to_show_how_ability2 = nullptr;

	u1Button* button_ability3 = nullptr;
	u1Label* label_ability3 = nullptr;
	u1Label* label_to_show_how_ability3 = nullptr;

};

struct UI_controls_controller {
	u1Label* controller = nullptr;

	u1Button* Cbutton_direction_up = nullptr;
	u1Label* Clabel_to_show_how_direction_up = nullptr;

	u1Button* Cbutton_direction_right = nullptr;
	u1Label* Clabel_to_show_how_direction_right = nullptr;

	u1Button* Cbutton_direction_left = nullptr;
	u1Label* Clabel_to_show_how_direction_left = nullptr;

	u1Button* Cbutton_direction_down = nullptr;
	u1Label* Clabel_to_show_how_direction_down = nullptr;

	u1Button* Cbutton_diagonals = nullptr;
	u1Label* Clabel_to_show_how_diagonals = nullptr;

	u1Button* Cbutton_basic_attack = nullptr;
	u1Label* Clabel_to_show_how_basic_attack = nullptr;

	u1Button* Cbutton_up = nullptr;
	u1Label* Clabel_to_show_how_up = nullptr;

	u1Button* Cbutton_right = nullptr;
	u1Label* Clabel_to_show_how_right = nullptr;

	u1Button* Cbutton_left = nullptr;
	u1Label* Clabel_to_show_how_left = nullptr;

	u1Button* Cbutton_down = nullptr;
	u1Label* Clabel_to_show_how_down = nullptr;

	u1Button* Cbutton_inventory = nullptr;
	u1Label* Clabel_to_show_how_inventory = nullptr;

	u1Button* Cbutton_interact = nullptr;
	u1Label* Clabel_to_show_how_interact = nullptr;

	u1Button* Cbutton_abilities = nullptr;
	u1Label* Clabel_to_show_how_abilities = nullptr;

	u1Button* Cbutton_ability1 = nullptr;
	u1Label* Clabel_to_show_how_ability1 = nullptr;

	u1Button* Cbutton_ability2 = nullptr;
	u1Label* Clabel_to_show_how_ability2 = nullptr;

	u1Button* Cbutton_ability3 = nullptr;
	u1Label* Clabel_to_show_how_ability3 = nullptr;
};

struct UI_controls {
	u1Image* controls_panel = nullptr;

	ui_controls_keyboard keyboard;
	ui_controls_controller controller;

	u1Button* button_retun_to_options = nullptr;
	u1Label* label_return_to_options = nullptr;
};

struct UI_select_champ {
	u1Image* select_champ_panel = nullptr;
	u1ChButton* button_warrior = nullptr;
	u1Label* label_warrior = nullptr;
	u1ChButton* button_archer = nullptr;
	u1Label* label_archer = nullptr;
	u1ChButton* button_mage = nullptr;
	u1Label* label_mage = nullptr;

	u1Image* warrior_image = nullptr;
	u1Image* archer_image = nullptr;
	u1Image* mage_image = nullptr;

	u1Image* warrior_info = nullptr;
	u1Image* archer_info = nullptr;
	u1Image* mage_info = nullptr;

	u1Button* return_select_champ_button = nullptr;
	u1Label* return_select_champ_label = nullptr;

	void Reset() {
		select_champ_panel = nullptr;
		button_warrior = nullptr;
		label_warrior = nullptr;
		button_archer = nullptr;
		label_archer = nullptr;
		button_mage = nullptr;
		label_mage = nullptr;
		warrior_image = nullptr;
		archer_image = nullptr;
		mage_image = nullptr;
		warrior_info = nullptr;
		archer_info = nullptr;
		mage_info = nullptr;
		return_select_champ_button = nullptr;
		return_select_champ_label = nullptr;
	}
};

class m1MenuManager :public m1Module {

public:
	void CreateMainMenu();
	void DestroyMainMenu();

	void CreateCredits();
	void DestroyCredits();

	void CreateSelectChamp();
	void DestroySelectChamp();

	void CreateOptions();
	void DestroyOptions();

	void CreateControls();
	void DestroyControls();

	void CreateNameMenu();
	void DestroyNameMenu();

	bool Interact(u1GUI* button);

	void ManageInputText(u1GUI * &interaction);

public:
	UI_main_menu	main_menu;
	UI_options		options;
	UI_credits		credits;
	UI_input		input;
	UI_controls		controls;
	UI_select_champ	select_champ;
};
#endif // !__M1MENUMANAGER_H__

