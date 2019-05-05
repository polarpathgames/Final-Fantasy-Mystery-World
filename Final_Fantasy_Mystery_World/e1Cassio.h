#ifndef _E1CASSIO_H_
#define _E1CASSIO_H_

#include "e1Enemy.h"

class e1Cassio : public e1Enemy {

public:

	e1Cassio(const int &x, const int &y);

	virtual ~e1Cassio();

	bool PreUpdate();

	bool Update(float dt);

	void IdAnimToEnum();

	bool CanAttackDistance();

	void PrepareDistanceAttack();

};

#endif // !_E1CASSIO_H_
