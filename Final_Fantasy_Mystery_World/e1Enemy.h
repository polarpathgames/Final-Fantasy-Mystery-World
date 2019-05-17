#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2Timer.h"
#include "e1Particles.h"
#include <vector>
#include "e1Drop.h"


class e1Enemy : public e1DynamicEntity
{

public:

	struct EnemyStats {
		int max_live = 100;
		int live = 100;
		int basic_attack_damage = 25;
		int special_attack_damage = 20;
		int experience = 20;
	};


public:

	enum class EnemyType {
		CARNIVOROUS_PLANT,
		BLUE_DOG,
		STRANGE_FROG,
		BLUE_SLIME,
		MEGA_EYE,
		SUPER_PURPLE_FROG,
		CASSIO,
		FROZEN,
		BABY_DRAKE,
		SPIDER,
		BOMBERMAN,

		NONE
	};

	e1Enemy(const int &x, const int &y);

	virtual ~e1Enemy();

	virtual void InitStats();

	bool PreUpdate();

	bool Update(float dt);
	virtual void UpdateEnemy() {}

	virtual bool PostUpdate() { return true; };

	virtual bool Load(pugi::xml_node&);

	virtual bool Save(pugi::xml_node&) const;

	virtual bool CleanUp();

	virtual bool CanAttack() { return false; } // Super Purple Frog has that function and I'm not going to spend time reworking it
	bool IsAnotherEnemyNextTile();
	bool IsPlayerNextTile();
	bool IsPlayerInRange(const int& rg);
	void LookToPlayer();

	void MovementLogic();
	void PerformMovement(float dt);

	virtual void PrepareBasicAttack() {}
	virtual void FinishBasicAttack() {}

	virtual void Attacking() {}

	virtual void PrepareDistanceAttack() {}
	virtual bool IsSpecialAttack1Finished() { return current_animation->Finished(); }
	virtual void AfterSpecialAttack1() {}

	virtual void AfterAttack() {}

	virtual void Escape() {}
	virtual void Death();
	void GetHitted(const int &damage_taken);

	void Drop();

	int CalculateDrop();

public:
	std::vector<iPoint> next_enemy_pos;
	EnemyStats stats;
	float arrow_time = 0;
	p2Timer time_to_wait_before_attack;
	EnemyType enemy_type = EnemyType::NONE;
	iPoint original_position{ 0,0 };
	int range_to_walk = 7;
	int range_to_distance_attack = 1;
	bool want_to_attack = true;

	uint times_hitted = 0u;

	// % of drop

	int ratio_poti_hp = 0;
	int ratio_poti_mana = 0;
	int ratio_rupee = 0;
	int ratio_green_rupee = 0;
	int ratio_red_rupee = 0;
	int ratio_blue_rupee = 0;
	int ratio_gold_rupee = 0;

	//SFX

	Mix_Chunk* fx_laser;
	bool laser_play_fx = true;
	Mix_Chunk* fx_enemy_hit;
	Mix_Chunk* fx_dragon_attack;
	Mix_Chunk* fx_dragon_knockback;
	Mix_Chunk* fx_ice_queen_hit;
	Mix_Chunk* fx_ice_queen_tp;
	Mix_Chunk* fx_ice_queen_summon;
	Mix_Chunk* fx_frog_jump;

};



#endif // 



