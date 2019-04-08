#ifndef __STATICENTITY_H__
#define __STATICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2PerfTimer.h"
#include "e1Entity.h"


class e1StaticEntity : public e1Entity
{
public:

	enum class Type {
		TREE1,
		TREE2,
		TREE3,
		FLOWER,
		FOUNTAIN,
		BARREL,
		PLANT1,
		PLANT2,

		UNKNOWN
	};
	virtual bool Update(float dt) { return true; };

	virtual bool CleanUp() { return true; };

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

public:

	e1StaticEntity(int x, int y, const char* name);
	~e1StaticEntity();

private:

	void Draw(SDL_Texture* tex, float dt);
	void SetRect(int x, int y, int w, int h);

private:
	SDL_Rect frame;
	Type static_type;
};

#endif