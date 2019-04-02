#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "DynamicEntity.h"
#include "j1PerfTimer.h"
#include <vector>


class Enemy : public DynamicEntity
{
public:

	struct EnemyStats {
		int live = 100;
		int attack_power = 25;
	};


public:

	Enemy(const int &x, const int &y);

	virtual ~Enemy();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	bool IsPlayerNextTile();

	void MovementLogic();

public:

	EnemyStats stats;
	float time_to_wait_before_attack = 0.0f;
};



#endif // 



