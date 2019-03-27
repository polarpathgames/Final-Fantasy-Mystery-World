#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "DynamicEntity.h"
#include "j1PerfTimer.h"
#include <vector>

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
};

struct InputAccepted {
	bool A = true;
	bool W = true;
	bool S = true;
	bool D = true;
};

struct PlayerStats {

	int live = 100;
	int attack_power = 50;
	int xp = 0;
	int mana = 100;

};

enum class Movement_Type {
	InLobby, InQuest
};



class Player : public DynamicEntity
{

public:

	Player(const int &x, const int &y);

	virtual ~Player();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	void OnCollision(Collider* c2);


	//PreUpdate
	void ReadPlayerInput(); // Global organizator function 

	void ReadPlayerMovementInQuest(); // Set input for movement in quest
	void ReadPlayerMovementInLobby(); // Set input for movement in lobby

	void ReadAttack();

	//Update
	void PerformActions(float dt); // Global organizator function 

	void BasicAttack(); // Basic attack xd 

	void PerformMovementInLobby(float dt); // Do the movement in lobby
	void PerformMovementInQuest(float dt); // Do the movement in quest

	void ChangeDirection(); // Just change the player direction

	const bool MultipleButtons(const Input* input); // Ensure that only one button is clicked 



public:


	Input player_input; //VARIABLES DEL INPUT DEL PLAYER
	Movement_Type movement_type; //EN LOBBY O EN UNA QUEST

	PlayerStats stats;

	InputAccepted can_input;
};



#endif // 


