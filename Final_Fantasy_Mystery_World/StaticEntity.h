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
		TREE,
		FLOWER,
		FOUNTAIN,

		UNKNOWN
	};

public:

	StaticEntity(int x, int y, const char* name);
	~StaticEntity();

private:

	void Draw(SDL_Texture* tex, float dt);
	void SetRect(int x, int y, int w, int h);

private:
	SDL_Rect frame;
	Type type;
};

#endif

