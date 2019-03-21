#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "DynamicEntity.h"
#include "j1PerfTimer.h"
#include <vector>

struct Input {
	bool pressing_A;
	bool pressing_W;
	bool pressing_S;
	bool pressing_D;
	bool pressing_G;
	bool pressing_shift;
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

enum class Attacks {
	BASIC, NONE
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




	//PreUpdate
	void ReadPlayerInput(); 

	void ReadPlayerMovementInQuest();
	void ReadPlayerMovementInLobby();

	void ReadAttack();

	//Update
	void PerformActions(float dt);

	void BasicAttack();

	void PerformMovementInLobby(float dt);
	void PerformMovementInQuest(float dt);


	const bool MultipleButtons(const Input* input);



public:


	Input player_input; //VARIABLES DEL INPUT DEL PLAYER
	Movement_Type movement_type; //EN LOBBY O EN UNA QUEST
	Attacks type_attack = Attacks::NONE;
	PlayerStats stats;
};



#endif // 


