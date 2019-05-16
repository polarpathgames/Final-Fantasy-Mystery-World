#include "e1BlueDog.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "Brofiler/Brofiler.h"

e1BlueDog::e1BlueDog(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/BlueDog.tsx");
	name.assign("BlueDog");
	enemy_type = EnemyType::BLUE_DOG;

	position.x -= 5;
	position.y -= 24;
	SetPivot(21, 33);
	target_position = position;
	initial_position = position;

	InitStats();
}

e1BlueDog::~e1BlueDog()
{
}

void e1BlueDog::IdAnimToEnum()
{

	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 2:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 5:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 14:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 17:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 39:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 27:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 48:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 51:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 54:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 57:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 50:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 53:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 56:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 59:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 63:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 66:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 69:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 74:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 76:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 78:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 77:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 73:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 79:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 75:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}

	}

}
