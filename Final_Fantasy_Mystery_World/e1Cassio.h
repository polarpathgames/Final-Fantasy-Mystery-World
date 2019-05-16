#ifndef _E1CASSIO_H_
#define _E1CASSIO_H_

#include "e1Enemy.h"

class p1Follow;

class e1Cassio : public e1Enemy {

public:

	e1Cassio(const int &x, const int &y);

	virtual ~e1Cassio();

	void IdAnimToEnum();

	void PrepareDistanceAttack();
	bool IsSpecialAttack1Finished();
	void AfterSpecialAttack1();

	void UpdateEnemy();

private:
	iPoint particle_position = { 0,0 };
	float lerp_translation = 0.f;
	float lerp_by = 0.02f;
	p1Follow* poison_particle = nullptr;

};

#endif // !_E1CASSIO_H_
