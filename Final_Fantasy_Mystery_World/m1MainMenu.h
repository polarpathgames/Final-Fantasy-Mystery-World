#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include <list>
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Rect;
class u1GUI;
class u1Button;
class u1Label;
class u1CheckBox;
class u1Image;
class u1ChButton;
class u1InputText;
class e1Player;

enum class MainMenuStates {
	MAIN_MENU,
	OPTIONS_MENU,
	CREDITS_MENU,
	SELECTION_MENU,
	CONTROLS_MENU,
	CHOOSE_NAME_MENU,

	NONE
};

class m1MainMenu : public m1Module
{
public:
	m1MainMenu();
	~m1MainMenu();

	bool Awake();
	bool Start();
	void CreateMainMenu();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Interact(u1GUI* interaction);

	void CreateCredits();
	void DestroyCredits();

	void CreateSelectChamp();
	void DestroySelectChamp();

	void SetMainMenuState(const MainMenuStates &state);

	void DestroyMainMenu();

	void CreateOptions();
	void DestroyOptions();

	void CreateControls();
	void DestroyControls();

	void CreateNameMenu();
	void DestroyNameMenu();

private:

	MainMenuStates main_states = MainMenuStates::NONE;

	// input text screen

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

	// main menu

	u1GUI* background = nullptr;

	u1Button* new_game_button = nullptr;
	u1Label* new_game_label = nullptr;

	u1Button* load_game_button = nullptr;
	u1Label* load_game_label = nullptr;

	u1Button* options_button = nullptr;
	u1Label* options_label = nullptr;

	u1Button* credits_button = nullptr;
	u1Label* credits_label = nullptr;
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

	u1Button* exit_button = nullptr;
	u1Label* exit_text = nullptr;

	u1Button* button_retun = nullptr;
	u1Label* label_return = nullptr;

	u1Button* button_github = nullptr;
	u1Label* label_github = nullptr;

	u1Button* button_twitter = nullptr;
	u1Label* label_twitter = nullptr;
	
	u1Button* button_youtube = nullptr;
	u1Label* label_youtube = nullptr;


	//options
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

	u1Label* label_fps = nullptr;
	u1CheckBox* checkbox_fps = nullptr;
	u1Label* label_fullscreen = nullptr;
	u1CheckBox* checkbox_fullscreen = nullptr;
	u1Button* button_controls = nullptr;
	u1Label* label_controls = nullptr;

	u1Button* button_retun_options = nullptr;
	u1Label* label_return_options = nullptr;

	// Menu Controls

	u1Image* controls_panel = nullptr;

	u1Button* button_retun_to_options = nullptr;
	u1Label* label_return_to_options = nullptr;

	// KEYBOARD
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

	// CONTROLLER

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

public:

	//select character

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

	Mix_Chunk* fx_push_button;
	Mix_Chunk* fx_push_button_return;

	Mix_Music* mus_main_menu;
	Mix_Music* mus_credits;
	Mix_Music* mus_selection;

};

#endif