#ifndef _E1WARRIOR_H_
#define _E1WARRIOR_H_

#include "e1Player.h"

class e1Warrior : public e1Player {

public:

	e1Warrior(const int &x, const int &y);
	virtual ~e1Warrior();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

};



#endif