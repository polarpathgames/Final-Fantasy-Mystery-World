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
		ROCK1,
		ROCK2,
		STREETLIGHT,
		HOUSE1,
		HOUSE2,
		SHOP,
		HOME,
		FLOOR,
		CORNER_FLOOR,
		CORNER,
		RED_PLANT,
		HALF_TREE,
		QUEST_TREE1,
		QUEST_TREE2,
		QUEST_TREE3,
		QUEST_TREE4,
		FEATHER,
		CANDLE,
		PIECE_SHOP,
		SELLER,

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
	Type static_type = Type::UNKNOWN;

	bool has_animation = false;
	Animation* idle = nullptr;

};

#endif