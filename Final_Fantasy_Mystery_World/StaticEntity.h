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

	enum class Type {
		TREE1,
		TREE2,
		TREE3,
		FLOWER,
		FOUNTAIN,
		BARREL,

		UNKNOWN
	};
	virtual bool Update(float dt) { return true; };

	virtual bool CleanUp() { return true; };

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

public:

	StaticEntity(int x, int y, const char* name);
	~StaticEntity();

private:

	void Draw(SDL_Texture* tex, float dt);
	void SetRect(int x, int y, int w, int h);

private:
	SDL_Rect frame;
	Type static_type;
};

#endif

