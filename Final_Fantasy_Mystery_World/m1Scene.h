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
	MAP,

	NONE
};

enum class PlayerType {
	WARRIOR,
	ARCHER,
	MAGE,

	NONE,
};

enum class LobbyState {
	NORMAL_LOBBY,
	ICE_LOBBY,
	NIGHT_LOBBY
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

	bool Interact(u1GUI* interaction);
	StatesMenu GetMenuState();
	void SetMenuState(const StatesMenu &menu);

public:

	std::list<u1Label*> labels_control;
	std::list<u1Label*> Clabels_control;

	e1Player* player = nullptr;
	PlayerType player_type = PlayerType::NONE;

	int price_hp_potion = 100;
	int price_mana_potion = 100;
	int price_ability3 = 175;
	int price_helmet = 375;
	int price_ring = 375;
	int helmet_hp = 150;
	int ring_mana = 100;


	StatesMenu menu_state = StatesMenu::NO_MENU;


public:

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
	Mix_Chunk* fx_buy_special;
	Mix_Chunk* fx_ability3;
	Mix_Chunk* fx_ability3_hit;
	Mix_Chunk* fx_burn;
	Mix_Chunk* fx_pick_up_poti;

	Mix_Music* mus_game_over;

	bool close_shop = false;
};

#endif // __j1SCENE_H__