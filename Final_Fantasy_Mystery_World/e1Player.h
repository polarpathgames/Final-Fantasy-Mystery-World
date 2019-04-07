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
	bool pressing_A; // MOVE
	bool pressing_W; // MOVE
	bool pressing_S; // MOVE
	bool pressing_D; // MOVE
	bool pressing_I; // CHANGE DIRECTION
	bool pressing_J; // CHANGE DIRECTION
	bool pressing_K; // CHANGE DIRECTION
	bool pressing_L; // CHANGE DIRECTION
	bool pressing_G; // BASIC ATTACK
	bool pressing_shift; // DIAGONALS
	bool pressing_V; // SHOW SKILLS
};

struct PlayerStats {

	int live = 1000;
	int attack_power = 500;
	int xp = 0;
	int mana = 100;

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
	void BasicAttack(); // Basic attack xd 

	void PerformMovementInLobby(float dt); // Do the movement in lobby
	void PerformMovementInQuest(float dt); // Do the movement in quest

	void ChangeDirection(); // Just change the player direction

	const bool MultipleButtons(const Input* input); // Ensure that only one button is clicked 

	void GetHitted(const int & damage_taken); // Player Get Damaged

	void CreateSkills(); // Skills Appear In Screen
	void DestroySkills(); //Skills Desappear

public:

	bool has_skills = false;

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


