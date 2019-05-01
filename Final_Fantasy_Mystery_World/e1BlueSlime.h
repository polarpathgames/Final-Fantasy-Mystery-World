#ifndef _E1BLUESLIME_H_
#define _E1BLUESLIME_H_

#include "e1Enemy.h"

class e1BlueSlime : public e1Enemy {

public:

	e1BlueSlime(const int &x, const int &y);

	virtual ~e1BlueSlime();

	bool PreUpdate();

	bool Update(float dt);

	void IdAnimToEnum();

};

#endif // !_E1BLUESLIME_H_