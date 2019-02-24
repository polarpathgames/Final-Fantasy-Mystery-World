#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "DynamicEntity.h"
#include "j1PerfTimer.h"
#include <vector>



class Player : public DynamicEntity
{

public:

	Player();

	virtual ~Player();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

public:
	enum Direction {
		up, down, right, left, idle
	};
	iPoint target_position;
	iPoint initial_position;
	iPoint movement_count;
	Direction direction;
};



#endif // 


