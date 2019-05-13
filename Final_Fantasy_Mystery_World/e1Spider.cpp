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
	State aux_state = state;
	e1Enemy::PreUpdate();

	if (!is_awake) {

		if (aux_state == State::SLEEPING && state == State::IDLE && !do_attack) {
			time_awake = SDL_GetTicks();
			state = State::BEFORE_ATTACK;
			do_attack = true;
		}
		if (do_attack) {
			turn_done = false;
		}

		if (do_attack && time_awake <= SDL_GetTicks() - 700) {
			iPoint player_tile = App->scene->player->actual_tile;
			App->scene->player->state = State::SLEEPING;
			is_awake = true;
			App->scene->player->GetHitted(stats.basic_attack_damage);
			if (player_tile == actual_tile + iPoint{ 0,1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - App->map->data.tile_width, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + App->map->data.tile_height, 500, EASE_OUT_QUINT);
				App->scene->player->actual_tile += {0, 2};
			}
		}
	}
	


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
