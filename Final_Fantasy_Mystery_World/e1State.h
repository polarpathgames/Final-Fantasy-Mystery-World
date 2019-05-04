#ifndef __E1STATE_H__
#define __E1STATE_H__

#include "e1DynamicEntity.h"
#include "p2Timer.h"

enum class EventStates {
	SNOWSTORM,
	POISON,

	NONE
};

class e1State :public e1Entity {
public:
	e1State(int x, int y, const char* name);
	~e1State();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

private:
	EventStates state = EventStates::NONE;
	e1Entity* target = nullptr;

	Animation* animation = nullptr;
	SDL_Rect frame = { 0, 0, 0, 0 };

	p2Timer timer;

	bool doing_effect = false;
	bool dynamic = true;

	uint turn_count = 0u;
	uint turn_effect = 0u;
	uint number_hit = 0u;
	uint max_number_hit = 0u;

	uint time_effect = 1u;
	int damage = 0;
};

#endif // !__E1STATE_H__
