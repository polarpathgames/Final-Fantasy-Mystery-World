#ifndef __m1SCENE_H__
#define __m1SCENE_H__

#include "m1Module.h"
#include "p2ChangeControls.h"
#include <list>
#include "SDL_mixer/include/SDL_mixer.h"
#include "p2Animation.h"

enum class StatesMenu {
	NO_MENU,
	PAUSE_MENU,
	OPTIONS_MENU,
	CONTROLS_MENU,
	INVENTORY_MENU,
	POTION_MENU,
	GO_TO_QUEST_MENU,
	SHOP_MENU,
	DIE_MENU,
	FIRSTABILITY_MENU,
	HELP_DIAGONAL_MENU,
	HELP_ATTACK_MENU,
	HELP_ABILITY_MENU,

	NONE
};

enum class PlayerType {
	WARRIOR,
	ARCHER,
	MAGE,

	NONE,
};

struct SDL_Texture;
struct SDL_Rect;

class u1GUI;
class u1Image;
class u1Label;
class u1Button;
class u1Bar;

class u1CheckBox;
class u1Slider;

class e1Player;

class m1Scene : public m1Module
{
public:

	m1Scene();

	// Destructor
	virtual ~m1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void ShitFunctionJAJA();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void CreateEntities();
	void CreateEntitiesFromXML(pugi::xml_node& node);
	void CreateHUD();
	void ShowHUD(bool show_or_hide);

	bool Interact(u1GUI* interaction);
	StatesMenu GetMenuState();
	void SetMenuState(const StatesMenu &menu);

	void ChangeCompass(bool shift_pressed);

public:

	std::list<u1Label*> labels_control;
	std::list<u1Label*> Clabels_control;

	e1Player* player = nullptr;
	PlayerType player_type = PlayerType::NONE;

	ChangeControls * control_to_change = nullptr;

	// HUD
	u1Image* bg_hud = nullptr;
	u1Image* player_hud_image = nullptr;
	u1Bar* player_hp_bar = nullptr;
	u1Bar* player_mana_bar = nullptr;

		//Compass
	u1Image* diagonal_compass = nullptr;
	u1Image* vertical_compass = nullptr;


	int price_hp_potion = 75;
	int price_mana_potion = 75;

	StatesMenu menu_state = StatesMenu::NO_MENU;
	
public:

	// SFX
	/*int fx_writting;
	int fx_attack;
	int fx_frog_attack;
	int fx_plant_attack;
	int fx_dog_attack;
	int fx_ability_warrior;
	int fx_ability_mage;
	int fx_ability_mage_prepare;
	int fx_ability_archer;
	int fx_ability_no_mana;
	int fx_ability_screen;
	int fx_drop_pick_up;
	int fx_door_enter;
	int fx_potion;
	int fx_denegated_potion;
	int fx_potion_menu;
	int fx_flash;
	int fx_die;
	int fx_rock;
	int fx_kill_enemy;
	int fx_no_money;
	int fx_controller_conection;
	int fx_surprise;
	int fx_buy;*/

    Mix_Chunk* fx_writting;
	Mix_Chunk* fx_attack;
	Mix_Chunk* fx_frog_attack;
	Mix_Chunk* fx_plant_attack;
    Mix_Chunk* fx_dog_attack;
	Mix_Chunk* fx_ability_warrior;
    Mix_Chunk* fx_ability_mage;
	Mix_Chunk* fx_ability_mage_prepare;
	Mix_Chunk* fx_ability_archer;
	Mix_Chunk* fx_ability_no_mana;
	Mix_Chunk* fx_ability_screen;
	Mix_Chunk* fx_drop_pick_up;
	Mix_Chunk* fx_door_enter;
	Mix_Chunk* fx_potion;
	Mix_Chunk* fx_denegated_potion;
	Mix_Chunk* fx_potion_menu;
    Mix_Chunk* fx_flash;
	Mix_Chunk* fx_die;
	Mix_Chunk* fx_rock;
	Mix_Chunk* fx_kill_enemy;
	Mix_Chunk* fx_no_money;
	Mix_Chunk* fx_controller_conection;
	Mix_Chunk* fx_surprise;
	Mix_Chunk* fx_buy;

	Mix_Music* mus_game_over;

	bool close_shop = false;
};

#endif // __j1SCENE_H__