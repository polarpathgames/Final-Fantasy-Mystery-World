#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"
#include "Entity.h"

class DynamicEntity  : public Entity
{
public:

	DynamicEntity();
	virtual ~DynamicEntity();
	
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	
	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

public:

	enum class Direction {
		UP, DOWN, RIGHT, LEFT, UP_LEFT, DOWN_LEFT, UP_RIGHT, DOWN_RIGHT
	};
	
	Direction direction;
	State state;

	Animation GoLeft;
	Animation GoRight;
	Animation GoDown;
	Animation GoUp;

	Animation IdleLeft;
	Animation IdleRight;
	Animation IdleUp;
	Animation IdleDown;

	Animation GoUpLeft;
	Animation GoDownLeft;
	Animation GoUpRight;
	Animation GoDownRight;

	Animation IdleUpLeft;
	Animation IdleDownLeft;
	Animation IdleUpRight;
	Animation IdleDownRight;

	iPoint velocity;

};

#endif
