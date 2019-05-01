#ifndef __M1STATE_MANAGER_H__
#define __M1STATE_MANAGER_H__

#include "m1Module.h"
#include <list>
#include "p2States.h"

class m1StateManager :public m1Module {
public:
	m1StateManager();
	~m1StateManager();

	bool PostUpdate();


private:
	std::list<State*> states;
};

#endif // !__M1STATE_MANAGER_H__