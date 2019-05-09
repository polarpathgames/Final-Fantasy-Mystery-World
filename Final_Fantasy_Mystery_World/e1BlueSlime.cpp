#include "e1BlueSlime.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "Brofiler/Brofiler.h"

e1BlueSlime::e1BlueSlime(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/BlueSlime.tsx");

	enemy_type = EnemyType::BLUE_SLIME;

	SetPivot(21, 33);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1BlueSlime::~e1BlueSlime()
{
}

void e1BlueSlime::IdAnimToEnum()
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
		case 8:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 11:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 32:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 43:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 40:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 35:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 18:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 26:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 21:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 29:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 16:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 24:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 19:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 27:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 48:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 56:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 51:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 59:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 64:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 80:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 88:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 65:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 81:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 89:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
