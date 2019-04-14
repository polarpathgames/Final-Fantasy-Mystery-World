#ifndef _C1CUTSCENEMOVECAMERA_H
#define _C1CUTSCENEMOVECAMERA_H

#include "c1CutsceneAction.h"
#include "p2Point.h"

class c1CutsceneMoveCamera :public c1CutsceneAction
{
public:
	c1CutsceneMoveCamera(uint start, uint duration, int speed_x, int speed_y);
	~c1CutsceneMoveCamera() {};

	void Execute(float dt);

private:
	iPoint camera_speed;

};

#endif
