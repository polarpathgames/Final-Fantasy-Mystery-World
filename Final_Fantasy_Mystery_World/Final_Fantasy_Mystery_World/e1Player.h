#ifndef __Player_H__
#define __Player_H__

#include "e1DynamicEntity.h"
#include "p2Timer.h"

class u1GUI;
class u1Button;
class u1Label;
class p1Follow;


struct Input {
	bool pressing_A = false; // MOVE
	bool pressing_W = false; // MOVE
	bool pressing_S = false; // MOVE
	bool pressing_D = false; // MOVE
	bool pressing_I = false; // CHANGE DIRECTION
	bool pressing_J = false; // CHANGE DIRECTION
	bool pressing_K = false; // CHANGE DIRECTION
	bool pressing_L = false; // CHANGE DIRECTION
	bool pressing_UP_LEFT = false; // CHANGE DIRECTION
	bool pressing_UP_RIGHT = false; // CHANGE DIRECTION
	bool pressing_DOWN_LEFT = false; // CHANGE DIRECTION
	bool pressing_DOWN_RIGHT = false; // CHANGE DIRECTION

	bool pressing_SPACE = false; // BASIC ATTACK
	bool pressing_shift = false; // DIAGONALS
	bool pressing_V = false; // SHOW SKILLS
	bool pressing_1 = false; // ability 1
	bool pressing_2 = false; // falsh
	bool pressing_3 = false; // ability 2

	void Reset() {
		pressing_A = false;
		pressing_W = false;
		pressing_S = false;
		pressing_D = false;
		pressing_I = false;
		pressing_J = false;
		pressing_K = false;
		pressing_L = false;
		pressing_SPACE = false;
		pressing_shift = false;
		pressing_V = false;
		pressing_J = false;
		pressing_2 = false;
		pressing_3 = false;
	}
};

struct PlayerStats {

	int live = 0;
	int max_lives = 0;
	int attack_power = 0;
	int xp = 0;
	int max_xp = 100;
	int mana = 0;
	int max_mana = 0;
	int gold = 0;
	int num_hp_potions = 0;
	int num_mana_potions = 0;
	int cost_mana_special_attack1 = 0;
	int cost_mana_special_attack2 = 0;
	int cost_mana_special_attack3 = 0;
	int level = 0;
	int attack_power_ability_1 = 0;
	int attack_power_ability_3 = 0;

};



enum class Movement_Type {
	InLobby, InQuest
};



class e1Player : public e1DynamicEntity
{

public:

	e1Player(const int &x, const int &y);

	void Init();

	virtual ~e1Player();

	bool PreUpdate();

	bool Update(float dt);

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	void Draw(float dt);

	virtual bool CleanUp();

	void OnCollision(Collider* c2);
	void OnCollisionEnter(Collider* c2);
	void OnCollisionExit(Collider* c2);

	void CheckLobbyCollision(const float &pdtos, const Direction &dir);

	void CenterPlayerInTile();

	//PreUpdate
	void ReadPlayerInput(); // Global organizator function 

	void ReadPlayerMovementInQuest(); // Set input for movement in quest
	void ReadPlayerMovementInLobby(); // Set input for movement in lobby

	void ReadAttack();

	void InitStats();

	virtual void PrepareSpecialAttack1() {};

	virtual void SpecialAttack1() {};


	//Update
	void PerformActions(float dt); // Global organizator function 

	void PrepareBasicAttack(); // Prepare Basic Attack

	void BasicAttack(); // Basic attack xd 
	
	void PrepareSpecialAttack2();

	void SpecialAttack2();

	void CheckBasicSpecialAttack2Effects();

	void PerformMovementInLobby(float dt); // Do the movement in lobby
	void PerformMovementInQuest(float dt); // Do the movement in quest

	void ChangeDirection(); // Just change the player direction

	const bool MultipleButtons(const Input* input); // Ensure that only one button is clicked 

	void GetHitted(const int & damage_taken); // Player Get Damaged
	void Death();
	void CreateSkills(); // Skills Appear In Screen
	virtual void IdAnimToEnum() {};
	void DestroySkills(); //Skills Desappear

	bool BlockControls(bool to_block);

	void LobbyControls();
	void QuestControls();

	void LookFlash();
	void Flashing();
	void RestTimeAfterFlash();

	void ReduceMana(const int &cost_mana);

	void AugmentMana(const int &plus_mana, bool level_up = false);

	void ReduceLives(const int &cost_lives);

	void AugmentLives(const int &plus_lives, bool level_up = false);

	bool IsEnemyInThatPosition(const iPoint & pos);

	void ReduceGold(const int &cost_gold);

	virtual void SetAbility1TilesPos() {}

	void AugmentGold(const int &plus_gold);
		
	void SetPlayerIdle();

	void UpdateExperience(int experience);

	void ChangeArrow(Animation & anim);

	virtual void UpdateLevel(){}

public:
	float death_time = 0.0f;
	bool has_skills = false;
	bool block_controls = false;
	bool god_mode = false;

	p2Timer timer_ability1;
	float time_to_wait_ability1 = 1.f;
	SDL_Texture* ability1_tile_tx = nullptr;
	std::vector<iPoint> ability1_tiles;
	Animation tile_anim;

	float flash_time = 0.0F;
	iPoint flash_position{ 0,0 };

	Input player_input; //VARIABLES DEL INPUT DEL PLAYER
	Movement_Type movement_type; //EN LOBBY O EN UNA QUEST

	PlayerStats stats;
	u1Button* upper_button = nullptr;
	u1Label* upper_skill_button = nullptr;
	u1Label* upper_skill_label = nullptr;

	u1Button* right_button = nullptr;
	u1Label* right_skill_button = nullptr;
	u1Label* right_skill_label = nullptr;

	u1Button* left_button = nullptr;
	u1Label* left_skill_button = nullptr;
	u1Label* left_skill_label = nullptr;

	Animation * current_anim_arrow_move = nullptr;
	Animation normal_arrow;
	Animation diagonal_arrow;
	p2Timer arrow_timer;
};
#endif