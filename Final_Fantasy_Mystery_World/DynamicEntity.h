#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"
#include "Entity.h"


enum class Direction {
	UP, DOWN, RIGHT, LEFT, UP_LEFT, DOWN_LEFT, UP_RIGHT, DOWN_RIGHT, NONE
};

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

	void ChangeTurn(EntityType type);

	void PushBack();

public:


	
	Direction direction = Direction::NONE;
	State state = State::NONE;

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

	iPoint target_position;
	iPoint initial_position; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DIGUALAR A LA POSICIO INICIAL!!
	iPoint movement_count; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DE POSAR A 0!! 


};

#endif
