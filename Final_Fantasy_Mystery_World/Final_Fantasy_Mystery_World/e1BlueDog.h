#ifndef _E1BLUEDOG_H_
#define _E1BLUEDOG_H_

#include "e1Enemy.h"

class e1BlueDog : public e1Enemy {

public:

	e1BlueDog(const int &x, const int &y);

	virtual ~e1BlueDog();

	void IdAnimToEnum();

};

#endif // !_E1BLUEDOG_H_
