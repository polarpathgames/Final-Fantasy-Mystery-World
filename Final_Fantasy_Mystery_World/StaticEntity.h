#ifndef __STATICENTITY_H__
#define __STATICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"
#include "Entity.h"


class StaticEntity : public Entity
{
public:

	StaticEntity(const int &x, const int &y);
	virtual ~StaticEntity();

	virtual bool Update(float dt) { return true; };

	virtual bool CleanUp() { return true; };

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

public:

	Animation Idle;

	SDL_Texture * ground = nullptr;

};

#endif

