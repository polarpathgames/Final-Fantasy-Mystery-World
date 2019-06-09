#ifndef __m1SCENE_H__
#define __m1SCENE_H__

#include "m1Module.h"
#include <list>
#include "SDL_mixer/include/SDL_mixer.h"

#define GOLD_RUPEE_GREEN 10, 20
#define GOLD_RUPEE_BLUE 30, 40
#define GOLD_RUPEE_RED 50, 70
#define GOLD_RUPEE_YELLOW 80, 100



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

	void UpdateCutscenesDone();

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

    Mix_Chunk* fx_writting = nullptr;
	Mix_Chunk* fx_attack = nullptr;
	Mix_Chunk* fx_frog_attack = nullptr;
	Mix_Chunk* fx_plant_attack = nullptr;
    Mix_Chunk* fx_dog_attack = nullptr;
	Mix_Chunk* fx_ability_warrior = nullptr;
    Mix_Chunk* fx_ability_mage = nullptr;
	Mix_Chunk* fx_ability_mage_prepare = nullptr;
	Mix_Chunk* fx_ability_archer = nullptr;
	Mix_Chunk* fx_ability_no_mana = nullptr;
	Mix_Chunk* fx_ability_screen = nullptr;
	Mix_Chunk* fx_drop_pick_up = nullptr;
	Mix_Chunk* fx_door_enter = nullptr;
	Mix_Chunk* fx_potion = nullptr;
	Mix_Chunk* fx_denegated_potion = nullptr;
	Mix_Chunk* fx_potion_menu = nullptr;
    Mix_Chunk* fx_flash = nullptr;
	Mix_Chunk* fx_die = nullptr;
	Mix_Chunk* fx_rock = nullptr;
	Mix_Chunk* fx_kill_enemy = nullptr;
	Mix_Chunk* fx_no_money = nullptr;
	Mix_Chunk* fx_controller_conection = nullptr;
	Mix_Chunk* fx_surprise = nullptr;
	Mix_Chunk* fx_buy = nullptr;
	Mix_Chunk* fx_buy_special = nullptr;
	Mix_Chunk* fx_ability3 = nullptr;
	Mix_Chunk* fx_ability3_hit = nullptr;
	Mix_Chunk* fx_burn = nullptr;
	Mix_Chunk* fx_poison = nullptr;
	Mix_Chunk* fx_pick_up_poti = nullptr;

	Mix_Music* mus_game_over = nullptr;

	bool close_shop = false;

	int snowman_count = 0;
};

#endif // __j1SCENE_H__