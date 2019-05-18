#ifndef _E1BOMBERMAN_H_
#define _E1BOMBERMAN_H_

#include "e1Enemy.h"

class e1Bomberman : public e1Enemy {

public:

	e1Bomberman(const int &x, const int &y);

	virtual ~e1Bomberman();

	void PrepareBasicAttack();

	void FinishBasicAttack();

	void IdAnimToEnum();

};


#endif // !_E1STRANGEFROG_H_