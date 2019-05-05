#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2PerfTimer.h"
#include "e1Particles.h"
#include <vector>


class e1Enemy : public e1DynamicEntity
{
public:

	struct EnemyStats {
		int live = 100;
		int attack_power = 25;
		int experience = 20;
	};


public:

	enum class EnemyType {
		CARNIVOROUS_PLANT,
		BLUE_DOG,
		STRANGE_FROG,
		BLUE_SLIME,
		SUPER_PURPLE_FROG,
		CASSIO,

		NONE
	};

	e1Enemy(const int &x, const int &y);

	virtual ~e1Enemy();

	void InitStats();

	virtual bool PreUpdate() { return true; };

	virtual bool Update(float dt) { return true; };

	virtual bool PostUpdate() { return true; };

	virtual bool Load(pugi::xml_node&);

	virtual bool Save(pugi::xml_node&) const;

	virtual bool CleanUp();

	bool IsAnotherEnemyNextTile();
	bool IsPlayerNextTile();

	void MovementLogic();
	void PerformMovement(float dt);

	void GetHitted(const int &damage_taken);

	void Drop();

public:
	std::vector<iPoint> next_enemy_pos;
	EnemyStats stats;
	float arrow_time = 0;
	float time_to_wait_before_attack = 0.0f;
	EnemyType enemy_type = EnemyType::NONE;
	iPoint original_position{ 0,0 };

};



#endif // 



