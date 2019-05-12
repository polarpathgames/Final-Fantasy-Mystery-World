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
	void AfetSpecialAttack1();

	void UpdateEnemy();

	void FinishBasicAttack();

private:
	iPoint particle_position = { 0,0 };
	float lerp_translation = 0.f;
	float lerp_by = 0.02f;
	p1Follow* poison_particle = nullptr;

};

#endif // !_E1MEGAEYE_H_

