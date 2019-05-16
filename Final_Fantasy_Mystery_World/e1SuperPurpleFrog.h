#ifndef _E1SUPERPURPLEFROG_H_
#define _E1SUPERPURPLEFROG_H_

#include "e1Enemy.h"

class e1SuperPurpleFrog : public e1Enemy {

public:

	e1SuperPurpleFrog(const int &x, const int &y);

	virtual ~e1SuperPurpleFrog();

	void PrepareBasicAttack();

	void FinishBasicAttack();

	void IdAnimToEnum();

	bool CanAttack();

	void AfterAttack();

public:

	int distance_to_travel = 0;

};

#endif // !_E1SUPERPURPLEFROG_H_
