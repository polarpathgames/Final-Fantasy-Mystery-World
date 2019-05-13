#ifndef _E1SPIDER_H_
#define _E1SPIDER_H_

#include "e1Enemy.h"

class e1Spider : public e1Enemy {

public:

	e1Spider(const int &x, const int &y);

	virtual ~e1Spider();

	bool PreUpdate();

	void IdAnimToEnum();

public:

	Animation Sleep;

};


#endif // !_E1SPIDER_H_


