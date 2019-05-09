#include "e1Frozen.h"

e1Frozen::e1Frozen(const int& x, const int& y) :e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Frozen.tsx");

	enemy_type = EnemyType::FROZEN;

	InitStats();
	allow_turn = false;
}

e1Frozen::~e1Frozen()
{
}


