#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2PerfTimer.h"
#include "e1Entity.h"
#include "m1EasingSplines.h"

enum class Attacks {
	BASIC, SPECIAL_1, SPECIAL_2, NONE
};

enum class Direction {
	UP, DOWN, RIGHT, LEFT, UP_LEFT, DOWN_LEFT, UP_RIGHT, DOWN_RIGHT, NONE
};

struct animation {
	Animation GoDownLeft;
	Animation IdleDownLeft;
	Animation BasicAttackDownLeft;
	Animation DeathDownLeft;
	Animation AbilityDownLeft1;
	Animation AbilityDownLeft2;

	Animation GoDownRight;
	Animation IdleDownRight;
	Animation BasicAttackDownRight;
	Animation DeathDownRight;
	Animation AbilityDownRight1;
	Animation AbilityDownRight2;

	Animation GoUpRight;
	Animation IdleUpRight;
	Animation BasicAttackUpRight;
	Animation DeathUpRight;
	Animation AbilityUpRight1;
	Animation AbilityUpRight2;

	Animation GoUpLeft;
	Animation IdleUpLeft;
	Animation BasicAttackUpLeft;
	Animation DeathUpLeft;
	Animation AbilityUpLeft1;
	Animation AbilityUpLeft2;

	Animation GoLeft;
	Animation IdleLeft;
	Animation BasicAttackLeft;
	Animation DeathLeft;
	Animation AbilityLeft1;
	Animation AbilityLeft2;

	Animation GoRight;
	Animation IdleRight;
	Animation BasicAttackRight;
	Animation DeathRight;
	Animation AbilityRight1;
	Animation AbilityRight2;

	Animation GoUp;
	Animation IdleUp;
	Animation BasicAttackUp;
	Animation DeathUp;
	Animation AbilityUp1;
	Animation AbilityUp2;

	Animation GoDown;
	Animation IdleDown;
	Animation BasicAttackDown;
	Animation DeathDown;
	Animation AbilityDown1;
	Animation AbilityDown2;
};

class e1DynamicEntity  : public e1Entity
{
public:

	e1DynamicEntity(const int &x, const int &y);
	virtual ~e1DynamicEntity();
	
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	
	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

	virtual void GetHitted(const int & damage_taken) {}

	void PushBack();

	bool NextTileFree(const Direction & dir) const;

	bool RestTimeAfterAttack(float time_finish);

	void CheckBasicAttackEffects(const e1Entity::EntityType &type, const Direction & direction, const int &attack_damage);

	void ChangeAnimation(Direction &dir, State &states, Attacks attacks = Attacks::NONE);

	void ResetAnims();

	void ChangeAnimsInCutscene(const int &x, const int &y, const int & anim_num, int &pos_x, int &pos_y);



public:

	EaseSplineInfo* return_spline = nullptr;

	Direction direction = Direction::NONE;
	State state = State::NONE;

	iPoint target_position = { 0,0 };
	iPoint initial_position = { 0,0 };
	iPoint movement_count = { 0,0 };

	animation anim;

	SDL_Texture * ground = nullptr;

	Attacks type_attack = Attacks::NONE;

	float time_attack = 0.f;
	float time_after_attack = 500.f;

};

#endif
