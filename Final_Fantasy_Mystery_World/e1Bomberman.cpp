#include "e1Bomberman.h"

e1Bomberman::e1Bomberman(const int & x, const int & y) :e1Enemy(x,y)
{
	LoadEntityData("assets/entities/Bomberman.tsx");
	name.assign("Bomberman");
	enemy_type = EnemyType::BOMBERMAN;

	target_position = position;
	initial_position = position;

	InitStats();
}

e1Bomberman::~e1Bomberman()
{
}

void e1Bomberman::PrepareBasicAttack()
{
}

void e1Bomberman::FinishBasicAttack()
{
}

void e1Bomberman::IdAnimToEnum()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 33:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 27:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 21:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 18:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 16:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 22:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 19:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 39:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 45:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 65:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 77:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 61:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 78:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 73:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		}

	}
}
