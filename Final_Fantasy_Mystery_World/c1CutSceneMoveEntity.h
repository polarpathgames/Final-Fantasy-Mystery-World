#ifndef _C1CUTSCENEMOVEENTITY_H_
#define _C1CUTSCENEMOVEENTITY_H_

#include "c1CutsceneAction.h"
#include "c1CutSceneEntity.h"
#include "p2Point.h"
#include <string>

class c1CutsceneMoveEntity :public c1CutsceneAction {
public:
	c1CutsceneMoveEntity(uint start, uint duration, int origin_x, int origin_y, int destination_x, int destination_y, bool stop_on_goal, std::string entity);
	~c1CutsceneMoveEntity();

	void Execute(float dt);

private:
	iPoint		 origin;
	iPoint		 destination;
	c1CutsceneEntity* entity = nullptr;

	bool stop_on_goal = false;
	float speed = 0.005F;
	float lerp_by = 0.f;
};




#endif

