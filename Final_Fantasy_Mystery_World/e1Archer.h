#ifndef _E1ARCHER_H_
#define _E1ARCHER_H_

#include "e1Player.h"

class e1Archer : public e1Player {

public:

	e1Archer(const int &x, const int &y);
	virtual ~e1Archer();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void InitStats();

};



#endif
