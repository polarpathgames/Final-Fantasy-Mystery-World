#ifndef __E1ROCK_H__
#define __E1ROCK_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "e1StaticEntity.h"

class e1Rock : public e1StaticEntity
{
public:
	e1Rock(const int &x, const int &y, const char* name);
	~e1Rock();
	void GetHitted();

public:
	Animation* idle;
};


#endif

