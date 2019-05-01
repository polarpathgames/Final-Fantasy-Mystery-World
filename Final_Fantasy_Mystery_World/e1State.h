#ifndef __E1STATE_H__
#define __E1STATE_H__

#include "e1DynamicEntity.h"

enum class States {
	SNOWSTORM,

	NONE
};

class e1State :public e1Entity {
public:
	e1State();
	~e1State();

private:
	States state;
	e1Entity* target = nullptr;

};

#endif // !__E1STATE_H__
