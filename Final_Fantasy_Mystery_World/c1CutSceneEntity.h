#ifndef _C1CUTSCENEENTITY_H_
#define _C1CUTSCENEENTITY_H_

#include "c1CutsceneElement.h"
#include "e1Entity.h"


class c1CutsceneEntity :public c1CutsceneElement {
public:
	c1CutsceneEntity(int pos_x, int pos_y, std::string name);
	~c1CutsceneEntity();

	e1Entity* GetEntity();

protected:
	e1Entity * entity = nullptr;

};

#endif

