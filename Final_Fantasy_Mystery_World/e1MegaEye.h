#ifndef _E1MEGAEYE_H_
#define _E1MEGAEYE_H_

#include "e1Enemy.h"

class p1Follow;

class e1MegaEye : public e1Enemy {

public:

	e1MegaEye(const int &x, const int &y);

	virtual ~e1MegaEye();

	void IdAnimToEnum();

	void PrepareDistanceAttack();
	void PrepareBasicAttack();
	bool IsSpecialAttack1Finished();
	void AfterSpecialAttack1();

	void Attacking();

	void UpdateEnemy();

	void FinishBasicAttack();

private:


};

#endif // !_E1MEGAEYE_H_

