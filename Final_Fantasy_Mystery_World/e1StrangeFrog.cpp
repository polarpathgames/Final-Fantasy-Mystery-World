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

bool e1StrangeFrog::PreUpdate()
{
	BROFILER_CATEGORY("StrangeFrog PreUpdate", Profiler::Color::Yellow);

	if (state == State::IDLE) {
		if (IsPlayerNextTile()) {
			state = State::BEFORE_ATTACK;
			time_to_wait_before_attack = SDL_GetTicks();
		}
		else if (actual_tile.DistanceTo(App->scene->player->actual_tile) <= 7){
			state = State::WALKING; //Aixo sha de canviar I know :D
		}
		else turn_done = true;

	}
	if (state == State::WALKING) {
		//if (!IsPlayerNextTile()) {
			MovementLogic();
		//}
	}
	if (state == State::BEFORE_ATTACK) {
		if (time_to_wait_before_attack < SDL_GetTicks() - 250) {
			type_attack = Attacks::BASIC;
			state = State::ATTACKING;
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
			ChangeAnimation(direction, state, type_attack);
		}

	}
	return true;
}

bool e1StrangeFrog::Update(float dt)
{
	BROFILER_CATEGORY("StrangeFrog Update", Profiler::Color::Yellow);

	if (state == State::IDLE) {
		position.x = initial_position.x + movement_count.x;
		position.y = initial_position.y + movement_count.y;
		target_position = position;
	}

	if (state == State::WALKING) {
		PerformMovement(dt);
	}

	if (state == State::ATTACKING) {
		if (current_animation->Finished()) {
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
			App->audio->PlayFx(App->scene->fx_frog_attack);
			CheckBasicAttackEffects(e1Entity::EntityType::PLAYER, direction, stats.attack_power);
			state = State::AFTER_ATTACK;
			ChangeAnimation(direction, state);
			time_attack = SDL_GetTicks();
		}
	}
	if (state == State::AFTER_ATTACK) {
		RestTimeAfterAttack(time_attack);
	}
	if (state == State::DEATH) {
		if (current_animation->Finished()) {
			Drop();
			App->audio->PlayFx(App->scene->fx_kill_enemy);
			App->scene->player->UpdateExperience(stats.experience);
			App->map->quest_rooms->AddEntityToNotRepeat(original_position);
			to_delete = true;
			turn_done = true;
		}
	}

	if (App->debug)
		App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	return true;
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
