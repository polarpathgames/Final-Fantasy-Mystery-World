#ifndef __Enemy_H__
#define __Enemy_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2Timer.h"
#include "e1Particles.h"
#include <vector>
#include "e1Drop.h"

class u1Bar;
class u1Label;

class e1Enemy : public e1DynamicEntity
{

public:

	struct EnemyStats {
		int max_live = 500;
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
		AMAZING_DRAGON,
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

	Mix_Chunk* fx_laser = nullptr;
	bool laser_play_fx = true;
	Mix_Chunk* fx_enemy_hit = nullptr;
	Mix_Chunk* fx_dragon_attack = nullptr;
	Mix_Chunk* fx_dragon_knockback = nullptr;
	Mix_Chunk* fx_ice_queen_hit = nullptr;
	Mix_Chunk* fx_ice_queen_tp = nullptr;
	Mix_Chunk* fx_ice_queen_summon = nullptr;
	Mix_Chunk* fx_frog_jump = nullptr;
	Mix_Chunk* fx_poison_cassio = nullptr;
	Mix_Chunk* fx_plant_hit = nullptr;
	Mix_Chunk* fx_wake_up = nullptr;
	Mix_Chunk* fx_claw_cassio = nullptr;
	Mix_Chunk* fx_drake_throw = nullptr;
	Mix_Chunk* fx_fireball_ancient_dragon = nullptr;
	Mix_Chunk* fx_ancient_drake_weak = nullptr;
	Mix_Chunk* fx_ancient_drake_dead = nullptr;
	Mix_Chunk* fx_ancient_drake_hit = nullptr;
	Mix_Chunk* fx_bomberman_attack = nullptr;
	Mix_Chunk* fx_laser_mega_eye = nullptr;

	u1Bar* icequeen_hp_bar = nullptr;
	u1Label* icequeen_label = nullptr;

	u1Bar* drake_hp_bar = nullptr;
	u1Label* drake_name_label = nullptr;

	u1Bar* megadrake_hp_bar = nullptr;
	u1Label* megadrake_label = nullptr;

};



#endif // 



