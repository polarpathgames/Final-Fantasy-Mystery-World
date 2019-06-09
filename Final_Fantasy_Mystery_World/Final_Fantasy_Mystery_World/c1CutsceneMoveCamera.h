#ifndef _C1CUTSCENEMOVECAMERA_H
#define _C1CUTSCENEMOVECAMERA_H

#include "c1CutsceneAction.h"
#include "p2Point.h"

class c1CutsceneMoveCamera :public c1CutsceneAction
{
public:
	c1CutsceneMoveCamera(uint start, uint duration, int origin_x, int origin_y, int destination_x, int destination_y, float speed, bool stop_when_goal, bool from_player);
	~c1CutsceneMoveCamera() {};

	void Execute(float dt);

private:
	iPoint camera_origin;
	iPoint camera_destination;
	float speed = 0.f;

	float lerp_by = 0.f;
	bool stop_when_goal = false;
	bool from_player = false;
};

#endif
