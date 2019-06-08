#ifndef _C1CUTSCENEMOVEENTITY_H_
#define _C1CUTSCENEMOVEENTITY_H_

#include "c1CutsceneAction.h"
#include "p2Point.h"
#include <string>
#include "e1DynamicEntity.h"

class c1CutsceneMoveEntity :public c1CutsceneAction {
public:
	c1CutsceneMoveEntity(uint start, uint duration, float speed_x, float speed_y, std::string entity, Direction init, Direction end);
	~c1CutsceneMoveEntity();

	void Execute(float dt);

protected:
	iPoint		 player_speed = { 0,0 };
	e1DynamicEntity* ent = nullptr;
	Direction end_direction = Direction::NONE;
};




#endif

