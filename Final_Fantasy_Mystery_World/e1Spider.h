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
	int d = 0;
	bool do_attack = false;
	bool is_awake = false;
	float time_awake = 0.0F;
};


#endif // !_E1SPIDER_H_


