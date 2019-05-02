#ifndef _E1SUPERPURPLEFROG_H_
#define _E1SUPERPURPLEFROG_H_

#include "e1Enemy.h"

class e1SuperPurpleFrog : public e1Enemy {

public:

	e1SuperPurpleFrog(const int &x, const int &y);

	virtual ~e1SuperPurpleFrog();

	bool PreUpdate();

	bool Update(float dt);

	void IdAnimToEnum();

	bool CanAttack();

public:

	int distance_to_travel = 0;
	iPoint last_tile{ 0,0 };

};


#endif // !_E1SUPERPURPLEFROG_H_




