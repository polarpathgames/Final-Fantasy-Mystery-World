#ifndef __E1DROP_H__
#define __E1DROP_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "e1StaticEntity.h"



enum class DropsType {

	GOLD_DROP,
	GREEN_RUPEE,
	BLUE_RUPEE,
	RED_RUPEE,
	GOLD_RUPEE,
	ABILITY1,
	MANA_POTION,
	HEALTH_POTION,
	NONE
};

class e1Drop : public e1StaticEntity
{
public:

	e1Drop(const int &x, const int &y, const char* name);
	virtual ~e1Drop();

	bool Update(float fg);
	
	void SetGold(const int &gold);

	void FinishSpline();
	void SetSplineToFall();

public:

	DropsType drop_type = DropsType::NONE;
	int gold = 0;
	iPoint			  moving_pos = { NULL, NULL };
	bool			  moving = false;
	iPoint original_position{ 0,0 };

	float lerp_translation = 0.f;
	float lerp_by = 0.03f;

	bool is_insta_ruppe = false;
	iPoint insta_gem_pos = { 0,0 };
};

#endif

