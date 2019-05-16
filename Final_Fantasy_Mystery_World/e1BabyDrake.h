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
	void SuperHit();
	void Death();
	void PrepareParticle();
	void DeleteParticle();

private:
	iPoint particle_position = { 0,0 };
	float lerp_translation = 0.f;
	float lerp_by = 0.02f;
	p1Follow* fire_particle = nullptr;

	bool first_hit = false;
	bool second_hit = false;
	bool third_hit = false;

};

#endif // !_E1BABYDRAKE_H_

