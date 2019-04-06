#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "ChangeControls.h"

enum class StatesMenu {
	NO_MENU,
	PAUSE_MENU,
	OPTIONS_MENU,
	CONTROLS_MENU,

	NONE
};


struct SDL_Texture;
struct SDL_Rect;

class GUI;
class GUI_Image;
class GUI_Label;
class GUI_Button;

class GUI_CheckBox;
class GUI_Slider;

class Player;



class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void CreateEntities();

	void CreatePauseMenu();
	void DestroyPauseMenu();
	bool Interact(GUI* interaction);

	void CreateOptionsMenu();
	void DestroyOptionsMenu();

	void CreateControlsMenu();
	void DestroyControlsMenu();

public:

	//GUI* mock_image_ui = nullptr;
	//SDL_Rect mock_image_rect = { 0, 0, 61, 76 };
	GUI* background = nullptr;
	std::list<GUI_Label*> labels_control;
	std::list<GUI_Label*> Clabels_control;

  GUI_Slider* slider_general_volume = nullptr;
	GUI_Slider* slider_music_volume = nullptr;
	GUI_Slider* slider_fx_volume = nullptr;

	Player* player = nullptr;


private:

	ChangeControls * control_to_change = nullptr;
	StatesMenu menu_state = StatesMenu::NO_MENU;

	//pause
	GUI_Image* pause_panel = nullptr;
	GUI_Button* button_resume = nullptr;
	GUI_Label* label_resume = nullptr;
	GUI_Button* button_main_menu = nullptr;
	GUI_Label* label_main_menu = nullptr;
	GUI_Button* button_abort_quest = nullptr;
	GUI_Label* label_abort_quest = nullptr;
	GUI_Button* button_options = nullptr;
	GUI_Label* label_options = nullptr;
	
	//options
	GUI_Image* options_panel = nullptr;

	GUI_Label* label_general_volume = nullptr;
	GUI_Button* button_general_volume = nullptr;
	
	GUI_Label* label_music_volume = nullptr;
	GUI_Button* button_music_volume = nullptr;
	//GUI_Button* music_slider_btn = nullptr;

	GUI_Label* label_fx_volume = nullptr;
	GUI_Button* button_fx_volume = nullptr;
	//GUI_Button* fx_slider_btn = nullptr;

	GUI_Label* label_fps = nullptr;
	GUI_CheckBox* checkbox_fps = nullptr;
	GUI_Label* label_fullscreen = nullptr;
	GUI_CheckBox* checkbox_fullscreen = nullptr;
	GUI_Button* button_controls = nullptr;
	GUI_Label* label_controls = nullptr;

	GUI_Button* button_retun = nullptr;
	GUI_Label* label_return = nullptr;


	// Menu Controls

	

	GUI_Image* controls_panel = nullptr;
	

	GUI_Button* button_retun_to_options = nullptr;
	GUI_Label* label_return_to_options = nullptr;

	// KEYBOARD
	GUI_Label* keyboard = nullptr;

	GUI_Button* button_basic_attack = nullptr;
	GUI_Label* label_basic_attack = nullptr;
	GUI_Label* label_to_show_how_basic_attack = nullptr;

	GUI_Button* button_up = nullptr;
	GUI_Label* label_up = nullptr;
	GUI_Label* label_to_show_how_up = nullptr;

	GUI_Button* button_right = nullptr;
	GUI_Label* label_right= nullptr;
	GUI_Label* label_to_show_how_right = nullptr;

	GUI_Button* button_left = nullptr;
	GUI_Label* label_left = nullptr;
	GUI_Label* label_to_show_how_left = nullptr;

	GUI_Button* button_down = nullptr;
	GUI_Label* label_down = nullptr;
	GUI_Label* label_to_show_how_down = nullptr;

	GUI_Button* button_diagonals = nullptr;
	GUI_Label* label_diagonals = nullptr;
	GUI_Label* label_to_show_how_diagonals = nullptr;

	GUI_Button* button_direction_up = nullptr;
	GUI_Label* label_direction_up = nullptr;
	GUI_Label* label_to_show_how_direction_up = nullptr;

	GUI_Button* button_direction_right = nullptr;
	GUI_Label* label_direction_right = nullptr;
	GUI_Label* label_to_show_how_direction_right = nullptr;

	GUI_Button* button_direction_left = nullptr;
	GUI_Label* label_direction_left = nullptr;
	GUI_Label* label_to_show_how_direction_left = nullptr;

	GUI_Button* button_direction_down = nullptr;
	GUI_Label* label_direction_down = nullptr;
	GUI_Label* label_to_show_how_direction_down = nullptr;

	// CONTROLLER

	GUI_Label* controller = nullptr;

	GUI_Button* Cbutton_direction_up = nullptr;
	GUI_Label* Clabel_to_show_how_direction_up = nullptr;

	GUI_Button* Cbutton_direction_right = nullptr;
	GUI_Label* Clabel_to_show_how_direction_right = nullptr;

	GUI_Button* Cbutton_direction_left = nullptr;
	GUI_Label* Clabel_to_show_how_direction_left = nullptr;

	GUI_Button* Cbutton_direction_down = nullptr;
	GUI_Label* Clabel_to_show_how_direction_down = nullptr;

	GUI_Button* Cbutton_diagonals = nullptr;
	GUI_Label* Clabel_to_show_how_diagonals = nullptr;

	GUI_Button* Cbutton_basic_attack = nullptr;
	GUI_Label* Clabel_to_show_how_basic_attack = nullptr;

	GUI_Button* Cbutton_up = nullptr;
	GUI_Label* Clabel_to_show_how_up = nullptr;

	GUI_Button* Cbutton_right = nullptr;
	GUI_Label* Clabel_to_show_how_right = nullptr;

	GUI_Button* Cbutton_left = nullptr;
	GUI_Label* Clabel_to_show_how_left = nullptr;

	GUI_Button* Cbutton_down = nullptr;
	GUI_Label* Clabel_to_show_how_down = nullptr;

};

#endif // __j1SCENE_H__