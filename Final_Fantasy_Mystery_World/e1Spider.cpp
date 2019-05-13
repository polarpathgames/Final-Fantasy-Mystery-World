#include "e1Spider.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "App.h"
#include "m1Map.h"
#include "m1Scene.h"
#include "m1Audio.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1Render.h"
#include "p2Animation.h"
#include "Brofiler/Brofiler.h"

e1Spider::e1Spider(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/CarnivorousPlant.tsx");
	name.assign("Spider");
	enemy_type = EnemyType::SPIDER;

	state = State::SLEEPING;

	position.x -= 6;
	position.y -= 22;
	SetPivot(21, 33);
	Sleep.PushBack({ 272, 2, 43, 40 });
	Sleep.PushBack({ 272, 253, 43, 40 });
	Sleep.PushBack({ 272, 44, 43, 40 });
	Sleep.PushBack({ 272, 295, 43, 40 });
	Sleep.speed = 2;

	current_animation = &Sleep;

	target_position = position;
	initial_position = position;
	InitStats();
}

e1Spider::~e1Spider()
{
}

bool e1Spider::PreUpdate()
{
	e1Enemy::PreUpdate();



	return true;
}

void e1Spider::IdAnimToEnum()
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
		case 7:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 14:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 35:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 28:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 44:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 42:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 47:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 45:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 51:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 49:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 54:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 52:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 56:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 63:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 70:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 77:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 84:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 85:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 86:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;

			break;
		case 87:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 88:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 89:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 93:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 100:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
