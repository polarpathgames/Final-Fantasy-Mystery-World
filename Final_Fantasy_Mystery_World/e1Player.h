#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2PerfTimer.h"
#include <vector>

class u1GUI;
class u1Button;
class u1Label;


struct Input {
	bool pressing_A = false; // MOVE
	bool pressing_W = false; // MOVE
	bool pressing_S = false; // MOVE
	bool pressing_D = false; // MOVE
	bool pressing_I = false; // CHANGE DIRECTION
	bool pressing_J = false; // CHANGE DIRECTION
	bool pressing_K = false; // CHANGE DIRECTION
	bool pressing_L = false; // CHANGE DIRECTION
	bool pressing_G = false; // BASIC ATTACK
	bool pressing_shift = false; // DIAGONALS
	bool pressing_V = false; // SHOW SKILLS
	bool pressing_F = false;

	void Reset() {
		pressing_A = false;
		pressing_W = false;
		pressing_S = false;
		pressing_D = false;
		pressing_I = false;
		pressing_J = false;
		pressing_K = false;
		pressing_L = false;
		pressing_G = false;
		pressing_shift = false;
		pressing_V = false;
		pressing_J = false;
	}
};

struct PlayerStats {

	int live = 2;
	int max_lives = 250;
	int attack_power = 500;
	int xp = 0;
	int mana = 100;
	int max_mana = 100;
	int gold = 100;
	int num_hp_potions = 0;
	int num_mana_potions = 0;
	int cost_mana_special_attack1 = 50;
	int level = 1;

};



enum class Movement_Type {
	InLobby, InQuest
};



class e1Player : public e1DynamicEntity
{

public:

	e1Player(const int &x, const int &y);

	virtual ~e1Player();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

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

	

	//Update
	void PerformActions(float dt); // Global organizator function 

	void PrepareBasicAttack(); // Prepare Basic Attack
	void PrepareSpecialAttack1();
	void BasicAttack(); // Basic attack xd 
	void SpecialAttack1();
	void CheckSpecialAttack1Efects(const int &damage);
	void PerformMovementInLobby(float dt); // Do the movement in lobby
	void PerformMovementInQuest(float dt); // Do the movement in quest

	void ChangeDirection(); // Just change the player direction

	const bool MultipleButtons(const Input* input); // Ensure that only one button is clicked 

	void GetHitted(const int & damage_taken); // Player Get Damaged
	void Death();
	void CreateSkills(); // Skills Appear In Screen
	void IdAnimToEnum();
	void DestroySkills(); //Skills Desappear

	bool BlockControls(bool to_block);


	inline void ReduceMana(const int &cost_mana) {
		stats.mana -= cost_mana;
		if (stats.mana < 0)
			stats.mana = 0;
	}

	inline void AugmentMana(const int &plus_mana) {
		stats.mana += plus_mana;
		if (stats.mana > stats.max_mana)
			stats.mana = stats.max_mana;
	}

	inline void ReduceLives(const int &cost_lives) {
		stats.live -= cost_lives;
		if (stats.live < 0)
			stats.live = 0;
	}

	inline void AugmentLives(const int &plus_lives) {
		stats.live += plus_lives;
		if (stats.live > stats.max_lives)
			stats.live = stats.max_lives;
	}

	inline void ReduceGold(const int &cost_gold) {
		stats.gold -= cost_gold;
		if (stats.gold < 0)
			stats.gold = 0;
	}

	inline void AugmentGold(const int &plus_gold) {
		stats.gold += plus_gold;
	}

public:
	float death_time = 0.0f;
	bool has_skills = false;
	bool block_controls = false;

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

};



#endif // 


