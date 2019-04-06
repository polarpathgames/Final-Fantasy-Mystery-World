#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2PerfTimer.h"
#include <vector>


class e1Enemy : public e1DynamicEntity
{
public:

	struct EnemyStats {
		int live = 100;
		int attack_power = 25;
	};


public:

	e1Enemy(const int &x, const int &y);

	virtual ~e1Enemy();

	bool Update(float dt);

	bool PreUpdate();

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	bool IsPlayerNextTile();

	void MovementLogic();

	void GetHitted(const int &damage_taken);

public:

	EnemyStats stats;
	float time_to_wait_before_attack = 0.0f;
};



#endif // 



