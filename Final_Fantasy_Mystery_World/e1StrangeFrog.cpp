#include "e1StrangeFrog.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "App.h"
#include "m1Map.h"
#include "m1Audio.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1Render.h"
#include "m1EasingSplines.h"
#include "Brofiler/Brofiler.h"

e1StrangeFrog::e1StrangeFrog(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/StrangeFrog.tsx");
	name.assign("StrangeFrog");
	enemy_type = EnemyType::STRANGE_FROG;

	position.y -= 25;
	SetPivot(21, 33);
	target_position = position;
	initial_position = position;

	InitStats();
}

e1StrangeFrog::~e1StrangeFrog()
{
}

void e1StrangeFrog::PrepareBasicAttack()
{
	switch (direction) {
	case Direction::DOWN_LEFT:
		App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 200, EASE);
		App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 200, EASE);
		break;
	case Direction::UP_RIGHT:
		App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 200, EASE);
		App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 200, EASE);
		break;
	case Direction::DOWN_RIGHT:
		App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 200, EASE);
		App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 200, EASE);
		break;
	case Direction::UP_LEFT:
		App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 200, EASE);
		App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 200, EASE);
		break;
	case Direction::UP:
		App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3, 200, EASE);
		break;
	case Direction::DOWN:
		App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3, 200, EASE);
		break;
	case Direction::RIGHT:
		App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3, 200, EASE);
		break;
	case Direction::LEFT:
		App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3, 200, EASE);
		break;
	}
}

void e1StrangeFrog::FinishBasicAttack()
{
	switch (direction) {
	case Direction::DOWN_LEFT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
		break;
	case Direction::UP_RIGHT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
		break;
	case Direction::DOWN_RIGHT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
		break;
	case Direction::UP_LEFT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
		break;
	case Direction::UP:
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3 + 1, 200, EASE);
		break;
	case Direction::DOWN:
		return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3 + 1, 200, EASE);
		break;
	case Direction::RIGHT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3 + 1, 200, EASE);
		break;
	case Direction::LEFT:
		return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3 + 1, 200, EASE);
		break;
	}
}

void e1StrangeFrog::IdAnimToEnum()
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
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 17:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 20:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 45:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 75:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 92:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 95:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 98:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 101:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 90:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 93:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 96:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 99:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 105:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 120:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 135:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 150:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 165:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 166:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 167:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 168:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 169:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 170:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		case 171:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 172:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		}

	}

}
