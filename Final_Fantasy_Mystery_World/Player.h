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
	bool pressing_shift;
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





	void ReadPlayerInput(); 
	void ReadPlayerMovementInQuest();
	void ReadPlayerMovementInLobby();

	void PerformActions(float dt);
	void PerformMovementInLobby(float dt);
	void PerformMovementInQuest(float dt);


	const bool MultipleButtons(const Input* input);

public:


	Input player_input; //VARIABLES DEL INPUT DEL PLAYER
	Movement_Type movement_type; //EN LOBBY O EN UNA QUEST

};



#endif // 


