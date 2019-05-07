#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2PerfTimer.h"
#include "e1Entity.h"

enum class Attacks {
	BASIC, SPECIAL_1, SPECIAL_2, NONE
};

enum class Direction {
	UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT, NONE
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

	Direction direction = Direction::NONE;
	State state = State::NONE;

	Animation GoDownLeft;
	Animation IdleDownLeft;
	Animation BasicAttackDownLeft;
	Animation DeathDownLeft;
	Animation AbilitiDownLeft1;
	Animation AbilitiDownLeft2;
	Animation DistanceAttackDownLeft;

	Animation GoDownRight;
	Animation IdleDownRight;
	Animation BasicAttackDownRight;
	Animation DeathDownRight;
	Animation AbilitiDownRight1;
	Animation AbilitiDownRight2;
	Animation DistanceAttackDownRight;

	Animation GoUpRight;
	Animation IdleUpRight;
	Animation BasicAttackUpRight;
	Animation DeathUpRight;
	Animation AbilitiUpRight1;
	Animation AbilitiUpRight2;
	Animation DistanceAttackUpRight;

	Animation GoUpLeft;
	Animation IdleUpLeft;
	Animation BasicAttackUpLeft;
	Animation DeathUpLeft;
	Animation AbilitiUpLeft1;
	Animation AbilitiUpLeft2;
	Animation DistanceAttackUpLeft;

	Animation GoLeft;
	Animation IdleLeft;
	Animation BasicAttackLeft;
	Animation DeathLeft;
	Animation AbilitiLeft1;
	Animation AbilitiLeft2;
	Animation DistanceAttackLeft;

	Animation GoRight;
	Animation IdleRight;
	Animation BasicAttackRight;
	Animation DeathRight;
	Animation AbilitiRight1;
	Animation AbilitiRight2;
	Animation DistanceAttackRight;

	Animation GoUp;
	Animation IdleUp;
	Animation BasicAttackUp;
	Animation DeathUp;
	Animation AbilitiUp1;
	Animation AbilitiUp2;
	Animation DistanceAttackUp;

	Animation GoDown;
	Animation IdleDown;
	Animation BasicAttackDown;
	Animation DeathDown;
	Animation AbilitiDown1;
	Animation AbilitiDown2;
	Animation DistanceAttackDown;

	iPoint target_position;
	iPoint initial_position; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DIGUALAR A LA POSICIO INICIAL!!
	iPoint movement_count; //IMPORTANT: SEMPRE QUE ES CARREGUI UN NOU MAPA AQUESTA VARIABLE SHA DE POSAR A 0!! 


	SDL_Texture * ground = nullptr;

	Attacks type_attack = Attacks::NONE;

	float time_attack;
	float time_after_attack = 500;

};

#endif
