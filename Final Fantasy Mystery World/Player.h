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
};

enum class Movement_Type {
	InLobby, InQuest
};

enum class LobbyDirection {
	up, left, right, down, right_up, right_down, left_up, left_down
};
class Player : public DynamicEntity
{

public:

	Player();

	virtual ~Player();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	void PushBack();
	void ReadPlayerInput();
	void PerformActions(float dt);

public:

	iPoint target_position; 
	iPoint initial_position; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DIGUALAR A LA POSICIO INICIAL!!
	iPoint movement_count; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DE POSAR A 0!!
	Direction direction; //DIRECCIO EN UNA QUEST
	LobbyDirection lobby_direction; //DIRRECCIO EN LA LOBBY
	State state; //ESTATS DEL PLAYER
	Input player_input; //VARIABLES DEL INPUT DEL PLAYER
	Movement_Type movement_type; //EN LOBBY O EN UNA QUEST
};



#endif // 


