#ifndef _E1STRANGEFROG_H_
#define _E1STRANGEFROG_H_

#include "e1Enemy.h"

class e1StrangeFrog : public e1Enemy {

public:

	e1StrangeFrog(const int &x, const int &y);

	virtual ~e1StrangeFrog();

	bool PreUpdate();

	bool Update(float dt);

	void InitStats();


	void IdAnimToEnum();

};


#endif // !_E1STRANGEFROG_H_



