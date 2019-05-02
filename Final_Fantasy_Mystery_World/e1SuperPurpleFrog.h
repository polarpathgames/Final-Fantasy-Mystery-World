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

};


#endif // !_E1SUPERPURPLEFROG_H_




