#ifndef _E1AMAZINGDRAGON_H_
#define _E1AMAZINGDRAGON_H_

#include "e1Enemy.h"

class e1AmazingDragon : public e1Enemy {

public:

	e1AmazingDragon(const int &x, const int &y);

	virtual ~e1AmazingDragon();

	bool PreUpdate();
	bool Update(float dt);

	void IdAnimToEnum();

};

#endif // !_E1AMAZINGDRAGON_H_
