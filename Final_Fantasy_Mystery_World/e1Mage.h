#ifndef _E1MAGE_H_
#define _E1MAGE_H_

#include "e1Player.h"

class e1Mage : public e1Player {

public:

	e1Mage(const int &x, const int &y);
	virtual ~e1Mage();

	bool CleanUp();

	void InitStats();

	void PrepareSpecialAttack1();

	void SpecialAttack1();

	void IdAnimToEnum();

};



#endif