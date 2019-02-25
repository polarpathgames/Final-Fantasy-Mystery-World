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
		up, down, right, left
	};

	Animation GoLeft;
	Animation GoRight;
	Animation GoDown;
	Animation GoUp;
	Animation IdleLeft;
	Animation IdleRight;
	Animation IdleUp;
	Animation IdleDown;

	iPoint velocity;

};

#endif
