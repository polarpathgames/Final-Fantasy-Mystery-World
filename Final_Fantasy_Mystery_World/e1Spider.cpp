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
	LoadEntityData("assets/entities/Spider.tsx");
	name.assign("Spider");
	enemy_type = EnemyType::SPIDER;

	state = State::SLEEPING;

	SetPivot(16, 29);
	Sleep.PushBack({ 0, 203, 32, 34 });
	Sleep.PushBack({ 32, 203, 32, 34 });
	Sleep.PushBack({ 64, 203, 32, 34 });
	Sleep.PushBack({ 96, 203, 32, 34 });
	Sleep.speed = 2;

	current_animation = &Sleep;
	CenterOnTile();
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

		if (do_attack && time_awake <= SDL_GetTicks() - 400) {
			++d;
			iPoint player_tile = App->scene->player->actual_tile;
			App->scene->player->state = State::SLEEPING;
			App->scene->player->GetHitted(stats.basic_attack_damage);
			is_awake = true;
			if (player_tile == actual_tile + iPoint{ 0,1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - App->map->data.tile_width, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + App->map->data.tile_height, 500, EASE_OUT_QUINT);
				App->scene->player->actual_tile += {0, 2};
				App->scene->player->direction = Direction::UP_RIGHT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleUpRight;
			}
			else if (player_tile == actual_tile + iPoint{ 0,-1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + App->map->data.tile_width, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - App->map->data.tile_height, 500, EASE_OUT_QUINT);
				App->scene->player->actual_tile += {0, -2};
				App->scene->player->direction = Direction::DOWN_LEFT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleDownLeft;
			}
			else if (player_tile == actual_tile + iPoint{ 1,0 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + App->map->data.tile_width, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + App->map->data.tile_height, 500, EASE_OUT_QUINT);
				App->scene->player->actual_tile += {2, 0};
				App->scene->player->direction = Direction::UP_LEFT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleUpLeft;
			}
			else if (player_tile == actual_tile + iPoint{ -1,0 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - App->map->data.tile_width, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - App->map->data.tile_height, 500, EASE_OUT_QUINT);
				App->scene->player->actual_tile += {-2, 0};
				App->scene->player->direction = Direction::DOWN_RIGHT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleDownRight;
			}
			else if (player_tile == actual_tile + iPoint{ -1,-1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - App->map->data.tile_height * 2, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->scene->player->actual_tile += {-2, -2};
				App->scene->player->direction = Direction::DOWN;
				App->scene->player->current_animation = &App->scene->player->anim.IdleDown;
			}
			else if (player_tile == actual_tile + iPoint{ 1,1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + App->map->data.tile_height * 2, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->scene->player->actual_tile += {2, 2};
				App->scene->player->direction = Direction::UP;
				App->scene->player->current_animation = &App->scene->player->anim.IdleUp;
			}
			else if (player_tile == actual_tile + iPoint{ -1,1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - App->map->data.tile_width*2, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->scene->player->actual_tile += {-2, 2};
				App->scene->player->direction = Direction::RIGHT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleRight;
			}
			else if (player_tile == actual_tile + iPoint{ 1,-1 }) {
				App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + App->map->data.tile_width * 2, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
				App->scene->player->actual_tile += {2, -2};
				App->scene->player->direction = Direction::LEFT;
				App->scene->player->current_animation = &App->scene->player->anim.IdleLeft;
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
		case 31:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 32:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 33:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 34:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 50:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 53:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 55:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 56:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 61:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 62:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 63:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
