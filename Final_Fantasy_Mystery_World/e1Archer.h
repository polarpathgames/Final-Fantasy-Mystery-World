#ifndef _E1ARCHER_H_
#define _E1ARCHER_H_

#include "e1Player.h"
#include "e1Particles.h"

class e1Archer : public e1Player {

public:

	e1Archer(const int &x, const int &y);
	virtual ~e1Archer();

	bool CleanUp();

	void PrepareSpecialAttack1();

	void SpecialAttack1();

	void IdAnimToEnum();

	void UpdateLevel();

	void SetAbility1TilesPos();

public:

	e1Particles * arrow = nullptr;

};



#endif
