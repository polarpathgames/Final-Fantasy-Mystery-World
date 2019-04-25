#ifndef __E1DROP_H__
#define __E1DROP_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "e1StaticEntity.h"



enum class DropsType {

	GOLD_DROP,
	ABILITY1,
	NONE
};

class e1Drop : public e1StaticEntity
{
public:

	e1Drop(const int &x, const int &y, const char* name);
	virtual ~e1Drop();

	bool Update(float fg);
	
	void SetGold(const int &gold);

public:

	DropsType drop_type = DropsType::NONE;
	int gold = 0;
	fPoint			  moving_pos = { NULL, NULL };
	bool			  moving = true;
	iPoint original_position{ 0,0 };
};

#endif

