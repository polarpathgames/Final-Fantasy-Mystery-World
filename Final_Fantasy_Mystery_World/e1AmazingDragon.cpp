#include "e1AmazingDragon.h"

e1AmazingDragon::e1AmazingDragon(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/AmazingDragon.tsx");
	name.assign("AmazingDragon");
	enemy_type = EnemyType::AMAZING_DRAGON;

	SetPivot(110, 170);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1AmazingDragon::~e1AmazingDragon()
{
}

bool e1AmazingDragon::PreUpdate()
{
	return true;
}

bool e1AmazingDragon::Update(float dt)
{
	return true;
}

void e1AmazingDragon::GetHitted(const int & dmg)
{
}

void e1AmazingDragon::IdAnimToEnum()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		}
	}
}
