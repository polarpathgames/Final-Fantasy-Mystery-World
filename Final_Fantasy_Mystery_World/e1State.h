#ifndef __E1STATE_H__
#define __E1STATE_H__

#include "e1DynamicEntity.h"
#include "p2Timer.h"

enum class EventStates {
	BLIZZARD,
	POISON,
	FIRE,

	NONE
};

class e1State :public e1Entity {

public:
	e1State(int x, int y, const char* name);
	~e1State();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void SetMaxNumberHit(const uint& number) { max_number_hit = number; }

public:


	EventStates state = EventStates::NONE;
	e1Entity* target = nullptr;

private:

	Animation* animation = nullptr;
	SDL_Rect frame = { 0, 0, 0, 0 };

	p2Timer timer;
	p2Timer timer_before_effect;

	bool doing_effect = false;
	bool dynamic = true;

	uint turn_count = 0u;
	uint turn_effect = 0u;
	uint number_hit = 0u;
	uint max_number_hit = 0u;

	uint time_effect = 1u;
	float time_before_effect = 0.5f;
	int damage = 0;
public:

	Uint8 color_mod_r = 0u;
	Uint8 color_mod_g = 0u;
	Uint8 color_mod_b = 0u;
};

#endif // !__E1STATE_H__
