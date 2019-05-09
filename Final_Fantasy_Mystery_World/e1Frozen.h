#ifndef __E1FROZEN_H__
#define __E1FROZEN_H__

#include "e1Enemy.h"

class e1Frozen :public e1Enemy {
public:
	e1Frozen(const int& x, const int& y);
	~e1Frozen();
public:
	bool PreUpdate();

	bool Update(float dt);

	void IdAnimToEnum();

	bool CanAttackDistance();

	void PrepareDistanceAttack();
};

#endif // !__E1FROZEN_H__
