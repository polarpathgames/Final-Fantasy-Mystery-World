#ifndef _C1CUTSCENEMOVEENTITY_H_
#define _C1CUTSCENEMOVEENTITY_H_

#include "c1CutsceneAction.h"
#include "p2Point.h"
#include <string>

class c1CutsceneMoveEntity :public c1CutsceneAction {
public:
	c1CutsceneMoveEntity(uint start, uint duration, float speed_x, float speed_y, std::string entity);
	~c1CutsceneMoveEntity();

	void Execute(float dt);

protected:
	iPoint		 player_speed;
	std::string	 entity_name;
};




#endif

