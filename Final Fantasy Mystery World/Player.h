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

public:

	iPoint target_position; 
	iPoint initial_position; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DIGUALAR A LA POSICIO INICIAL!!
	iPoint movement_count; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DE POSAR A 0!!
	Direction direction;
	State state;
	Input player_input;
};



#endif // 


