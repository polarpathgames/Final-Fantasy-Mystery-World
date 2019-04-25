#ifndef _E1CARNIVOROUSPLANT_H_
#define _E1CARNIVOROUSPLANT_H_

#include "e1Enemy.h"

class e1CarnivorousPlant : public e1Enemy {

public:

	e1CarnivorousPlant(const int &x, const int &y);

	virtual ~e1CarnivorousPlant();

	bool PreUpdate();

	bool Update(float dt);

	void IdAnimToEnum();

public:

	Animation Sleep;

};


#endif // !_E1CARNIVOROUSPLANT_H_

