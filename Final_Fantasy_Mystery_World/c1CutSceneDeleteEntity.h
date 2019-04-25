#ifndef __C1CUTSCENEDELETEENTITY_H__
#define __C1CUTSCENEDELETEENTITY_H__

#include "c1CutSceneAction.h"
#include "c1CutSceneEntity.h"
#include "p2Log.h"
class c1CutSceneDeleteEntity :public c1CutsceneAction
{
public:
	c1CutSceneDeleteEntity(uint start, uint duration, std::string name);
	~c1CutSceneDeleteEntity();

	void Execute(float dt);
protected:
	std::string names;
};





#endif

