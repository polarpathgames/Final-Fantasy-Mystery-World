#ifndef __M1MENUMANAGER_H__
#define __M1MENUMANAGER_H__

#include "m1Module.h"

class u1InputText;
class u1Image;
class u1Button;
class u1Label;
class u1CheckBox;
class u1ChButton;
class u1VerticalSlider;
class u1Bar;

struct EaseSplineInfo;

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

	void Reset() {
		input_text = nullptr;
		input_text_image = nullptr;
		button_okay = nullptr;
		button_upper = nullptr;
		button_lower = nullptr;
		minus_letters = nullptr;
		max_letters = nullptr;
		button_A = nullptr;
		button_B = nullptr;
		button_C = nullptr;
		button_D = nullptr;
		button_E = nullptr;
		button_F = nullptr;
		button_G = nullptr;
		button_H = nullptr;
		button_I = nullptr;
		button_J = nullptr;
		button_K = nullptr;
		button_L = nullptr;
		button_M = nullptr;
		button_N = nullptr;
		button_O = nullptr;
		button_P = nullptr;
		button_Q = nullptr;
		button_R = nullptr;
		button_S = nullptr;
		button_T = nullptr;
		button_U = nullptr;
		button_V = nullptr;
		button_W = nullptr;
		button_X = nullptr;
		button_Y = nullptr;
		button_Z = nullptr;
		button_Delete = nullptr;
		button_Space = nullptr;
		return_btn_input_screen = nullptr;
		return_label_input_screen = nullptr;
	}
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

	void Reset() {
		options_panel = nullptr;
		label_general_volume = nullptr;
		button_general_volume = nullptr;
		minus_general_btn = nullptr;
		plus_general_btn = nullptr;
		label_general_value = nullptr;
		label_music_volume = nullptr;
		button_music_volume = nullptr;
		minus_music_btn = nullptr;
		plus_music_btn = nullptr;
		label_music_value = nullptr;
		label_fx_volume = nullptr;
		button_fx_volume = nullptr;
		minus_fx_btn = nullptr;
		plus_fx_btn = nullptr;
		label_fx_value = nullptr;
		/*label_fps = nullptr;
		checkbox_fps = nullptr;*/
		label_fullscreen = nullptr;
		checkbox_fullscreen = nullptr;
		button_controls = nullptr;
		label_controls = nullptr;
		button_retun_options = nullptr;
		label_return_options = nullptr;
		checkbox_mute_music = nullptr;
		checkbox_mute_fx = nullptr;
	}
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

	UI_controls_keyboard keyboard;
	UI_controls_controller controller;

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

struct UI_inventory {
	u1Image* inventory_panel = nullptr;
	u1Image* inventory_panel2 = nullptr;
	u1Image* inventory_background = nullptr;
	u1Image* hp_potion_image = nullptr;
	u1Button* hp_potion_button = nullptr;
	u1Image* mana_potion_image = nullptr;
	u1Button* mana_potion_button = nullptr;
	u1Image* coin_image = nullptr;
	u1Label* player_name = nullptr;
	u1Label* hp_potion_label = nullptr;
	u1Label* mana_potion_label = nullptr;
	u1Label* money_label = nullptr;
	u1Label* level_name_label = nullptr;
	u1Label* level_number_label = nullptr;
	u1Label* exp_name_label = nullptr;
	u1Label* exp_number_label = nullptr;

	u1Image* first_ability = nullptr;
	u1Image* flash = nullptr;
	u1Image* shop_ability = nullptr;
	u1Image* item_helmet = nullptr;
	u1Image* item_ring = nullptr;
	u1Button* button_first_ability = nullptr;
	u1Button* button_flash = nullptr;
	u1Button* button_shop_ability = nullptr;
	u1Button* button_item_helmet = nullptr;
	u1Button* button_item_ring = nullptr;
	EaseSplineInfo* spline_move_inventory = nullptr;

	void ChangeInventory(bool item);
	void ResetSplineInventory();
	void SetClipInInventory();
};

struct UI_pause_menu {
	u1Image* pause_panel = nullptr;
	u1Button* button_resume = nullptr;
	u1Label* label_resume = nullptr;
	u1Button* button_main_menu = nullptr;
	u1Label* label_main_menu = nullptr;
	u1Button* button_abort_quest = nullptr;
	u1Label* label_abort_quest = nullptr;
	u1Button* button_options = nullptr;
	u1Label* label_options = nullptr;

	void Reset() {
		pause_panel = nullptr;
		button_resume = nullptr;
		label_resume = nullptr;
		button_main_menu = nullptr;
		label_main_menu = nullptr;
		button_abort_quest = nullptr;
		label_abort_quest = nullptr;
		button_options = nullptr;
		label_options = nullptr;
	}
};

struct UI_potion {
	u1Image* potion_panel = nullptr;
	u1Button* use_hp_button = nullptr;
	u1Button* use_mana_button = nullptr;
	u1Button* cancel_button = nullptr;
	u1Label* use_label = nullptr;
	u1Label* cancel_label = nullptr;
};

struct UI_quest {
	u1Image* go_to_quest_panel = nullptr;
	u1Button* go_to_quest_button = nullptr;
	u1Label* go_to_quest_label = nullptr;
	u1Button* cancel_quest_button = nullptr;
	u1Label* cancel_quest_label = nullptr;
};

struct UI_shop {
	u1Image* shop_panel = nullptr;
	u1Label* shop_label = nullptr;

	u1Button* button_close_shop = nullptr;
	u1Label* label_close_shop = nullptr;

	u1Image* shop_background_item1 = nullptr;
	u1Button* shop_button_hp_potion = nullptr;
	u1Image* shop_hp_potion_image = nullptr;
	u1Label* shop_hp_potion_label = nullptr;
	u1Image* shop_coin1 = nullptr;

	u1Image* shop_background_item2 = nullptr;
	u1Button* shop_button_mana_potion = nullptr;
	u1Image* shop_mana_potion_image = nullptr;
	u1Label* shop_mana_potion_label = nullptr;
	u1Image* shop_coin2 = nullptr;

	u1Image* shop_background_item3 = nullptr;
	u1Button* shop_button_sword = nullptr;
	u1Image* shop_sword_image = nullptr;
	u1Label* shop_sword_label = nullptr;
	u1Image* shop_coin3 = nullptr;

	u1Image* shop_background_item4 = nullptr;
	u1Button* shop_button_helmet = nullptr;
	u1Image* shop_helmet_image = nullptr;
	u1Label* shop_helmet_label = nullptr;
	u1Image* shop_coin4 = nullptr;

	u1Image* shop_background_item5 = nullptr;
	u1Button* shop_button_ring = nullptr;
	u1Image* shop_ring_image = nullptr;
	u1Label* shop_ring_label = nullptr;
	u1Image* shop_coin5 = nullptr;

	u1VerticalSlider* shop_vertical_slider = nullptr;
	u1Image* shop_zone = nullptr;
	u1Image* shop_item_zone = nullptr;
};

struct UI_debugscreen {
	u1Image* debug_screen = nullptr;

	u1Label* project_name_label = nullptr;
	u1Label* version_label = nullptr;
	u1Label* fps_label = nullptr;
	u1Label* textures_label = nullptr;
	u1Label* map_label = nullptr;
	u1Label* player_label = nullptr;
	u1Label* mouse_label = nullptr;
	u1Label* entities_label = nullptr;
};

struct UI_abilities {
	u1Image* first_ability_panel = nullptr;
	u1Button* button_ability1_screen = nullptr;
	u1Label* label_ability1_screen = nullptr;
};

struct UI_game_over {
	u1Image* game_over_panel = nullptr;

	u1Button* button_continue_lobby = nullptr;
	u1Label* label_continue_lobby = nullptr;

	u1Button* button_return_main = nullptr;
	u1Label* label_continue_main = nullptr;
};

struct UI_HUD {
	u1Image* bg_hud = nullptr;
	u1Image* player_hud_image = nullptr;
	u1Bar* player_hp_bar = nullptr;
	u1Bar* player_mana_bar = nullptr;
	u1Image* diagonal_compass = nullptr; 	//Compass
	u1Image* vertical_compass = nullptr;	//Compass
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
	void UpdateOptionsMenu();
	void DestroyOptions();

	void CreateControls();
	void DestroyControls();

	void CreateNameMenu();
	void DestroyNameMenu();

	void CreateInventory();
	void DestroyInventory();
	void CreatePotionMenu(u1GUI* potion_button); //Creates the menu to choose to use or not a potion
	void DeletePotionMenu();

	void CreatePauseMenu();
	void DestroyPauseMenu();

	void CreateGoToQuestMenu();
	void DestroyGoToQuestMenu();

	void CreateShopMenu();
	void DestroyShopMenu();

	void CreateDebugScreen();
	void DestroyDebugScreen();
	void UpdateDebugScreen();

	void CreateGameOver();
	void DestroyGameOver();

	void CreateFirstAbilityPanel();
	void DestroyFirstAbilityPanel();

	void CreateHelpDiagonalMenu();
	void DestroyHelpDiagonalMenu();

	void CreateHelpAttackMenu();
	void DestroyHelpAttackMenu();

	void CreateHelpAbilityMenu();
	void DestroyHelpAbilityMenu();

	void CreateHUD();
	void DestroyHUD();
	void ShowHUD(bool show_or_hide);
	void ChangeCompass(bool shift_pressed);

	void SkipMenu(bool is_cutscene);

	void GodModeIndicator(bool is_god_mode);

	bool Interact(u1GUI* button);

	void ManageInputText(u1GUI * &interaction);

	void CreateBigInventory();
	void DestroyBigInventory();



public:
	UI_main_menu	main_menu;
	UI_options		options;
	UI_credits		credits;
	UI_input		input;
	UI_controls		controls;
	UI_select_champ	select_champ;
	UI_pause_menu	pause;
	UI_inventory	inventory;
	UI_potion		potion;
	UI_quest		quest;
	UI_shop			shop;
	UI_debugscreen	debug_screen;
	UI_abilities	abilities;
	UI_game_over	game_over;
	UI_HUD			hud;
	//god mode
	u1Label* god_text = nullptr;
	// help diagonal
	u1Image* help_diagonal = nullptr;
	// help ATTACK
	u1Image* help_attack = nullptr;
	// help ABILITY
	u1Image* help_ability = nullptr;
	//cutscenes skipper
	u1Image* im_skipper = nullptr;
	u1Label* lb_skipper = nullptr;
	u1Bar* br_skipper = nullptr;
};
#endif // !__M1MENUMANAGER_H__