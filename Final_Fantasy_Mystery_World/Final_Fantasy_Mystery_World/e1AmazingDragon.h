#ifndef _E1AMAZINGDRAGON_H_
#define _E1AMAZINGDRAGON_H_

#include "e1Enemy.h"

class e1Particles;

class e1AmazingDragon : public e1Enemy {

public:

	enum class AmazingDragonStates {
		WEAK,
		IDLE,
		ATTACK,
		WAIT_FIRE_BALLS,

		NONE
	};


	e1AmazingDragon(const int &x, const int &y);

	virtual ~e1AmazingDragon();

	bool PreUpdate();
	bool Update(float dt);
	void GetHitted(const int&dmg);
	void IdAnimToEnum();
public:
	bool active = false;
	bool first_update = true;
	AmazingDragonStates dragon_states = AmazingDragonStates::IDLE;

	uint turns_to_wait_after_fire_ball = 0U;
	uint waves_before_recover_energy = 0U;
	uint turns_recovering_energy = 0U;
	uint number_of_fire_balls = 0U;
	uint turns_to_wait_before_attack_again = 0U;

	uint auxiliar_turn_count = 0U;
	uint auxiliar_attack_count = 0U;

	p2Timer time;

	e1Particles* fire_ball = nullptr;
	bool waiting_fire_balls = false;

};

#endif // !_E1AMAZINGDRAGON_H_
