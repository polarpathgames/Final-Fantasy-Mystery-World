#ifndef _E1BABYDRAKE_H_
#define _E1BABYDRAKE_H_

#include "e1Enemy.h"

class p1Follow;

class e1BabyDrake : public e1Enemy {

public:

	e1BabyDrake(const int &x, const int &y);

	virtual ~e1BabyDrake();

	void IdAnimToEnum();

	void PrepareDistanceAttack();
	void AfetSpecialAttack1();
	void PrepareBasicAttack();
	void FinishBasicAttack();
	void UpdateEnemy();

	void PrepareParticle();
	void DeleteParticle();

private:
	iPoint particle_position = { 0,0 };
	float lerp_translation = 0.f;
	float lerp_by = 0.02f;
	p1Follow* fire_particle = nullptr;

};

#endif // !_E1BABYDRAKE_H_

