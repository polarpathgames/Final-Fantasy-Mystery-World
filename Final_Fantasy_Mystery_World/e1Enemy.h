#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2Timer.h"
#include "e1Particles.h"
#include <vector>


class e1Enemy : public e1DynamicEntity
{
public:

	struct EnemyStats {
		int live = 100;
		int basic_attack_damage = 25;
		int special_attack_damage = 50;
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
		FROZEN,

		NONE
	};

	e1Enemy(const int &x, const int &y);

	virtual ~e1Enemy();

	void InitStats();

	bool PreUpdate();

	bool Update(float dt);

	virtual bool PostUpdate() { return true; };

	virtual bool Load(pugi::xml_node&);

	virtual bool Save(pugi::xml_node&) const;

	virtual bool CleanUp();

	virtual bool CanAttack() { return false; } // Super Purple Frog has that function and I'm not going to spend time reworking it
	bool IsAnotherEnemyNextTile();
	bool IsPlayerNextTile();
	bool IsPlayerInRange(const int& rg);

	void MovementLogic();
	void PerformMovement(float dt);

	virtual void PrepareBasicAttack() {}
	virtual void FinishBasicAttack() {}

	virtual void PrepareDistanceAttack() {}
	virtual bool IsSpecialAttack1Finished() { return current_animation->Finished(); }
	virtual void AfetSpecialAttack1() {}

	void GetHitted(const int &damage_taken);

	void Drop();

public:
	std::vector<iPoint> next_enemy_pos;
	EnemyStats stats;
	float arrow_time = 0;
	p2Timer time_to_wait_before_attack;
	EnemyType enemy_type = EnemyType::NONE;
	iPoint original_position{ 0,0 };
	int range_to_walk = 15;
	int range_to_distance_attack = 1;

};



#endif // 



