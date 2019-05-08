#include "e1SuperPurpleFrog.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "App.h"
#include "m1Map.h"
#include "m1Audio.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1Render.h"
#include "m1EntityManager.h"
#include "m1EasingSplines.h"
#include "Brofiler/Brofiler.h"

e1SuperPurpleFrog::e1SuperPurpleFrog(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/SuperPurpleFrog.tsx");

	enemy_type = EnemyType::SUPER_PURPLE_FROG;

	
	SetPivot(16, 33);
	CenterOnTile();
	target_position = position;
	initial_position = position;

	InitStats();
}

e1SuperPurpleFrog::~e1SuperPurpleFrog()
{
}

bool e1SuperPurpleFrog::PreUpdate()
{
	BROFILER_CATEGORY("SuperPurpleFrog PreUpdate", Profiler::Color::Yellow);

	if (state == State::IDLE) {
		if (CanAttack()) {
			state = State::BEFORE_ATTACK;
			time_to_wait_before_attack = SDL_GetTicks();
		}
		else if (actual_tile.DistanceTo(App->scene->player->actual_tile) <= 7) {
			state = State::WALKING; //Aixo sha de canviar I know :D
		}
		else turn_done = true;

	}
	if (state == State::WALKING) {
		MovementLogic();
	}
	if (state == State::BEFORE_ATTACK) {
		if (time_to_wait_before_attack < SDL_GetTicks() - 250) {
			type_attack = Attacks::BASIC;
			state = State::ATTACKING;
			if (distance_to_travel != 1) {
				switch (direction) {
				case Direction::DOWN_LEFT:
					App->easing_splines->CreateSpline(&position.x, position.x - ((App->map->data.tile_width / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					App->easing_splines->CreateSpline(&position.y, position.y + ((App->map->data.tile_height / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::UP_RIGHT:
					App->easing_splines->CreateSpline(&position.x, position.x + ((App->map->data.tile_width / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					App->easing_splines->CreateSpline(&position.y, position.y - ((App->map->data.tile_height / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::DOWN_RIGHT:
					App->easing_splines->CreateSpline(&position.x, position.x + ((App->map->data.tile_width / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					App->easing_splines->CreateSpline(&position.y, position.y + ((App->map->data.tile_height / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::UP_LEFT:
					App->easing_splines->CreateSpline(&position.x, position.x - ((App->map->data.tile_width / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					App->easing_splines->CreateSpline(&position.y, position.y - ((App->map->data.tile_height / 4) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::UP:
					App->easing_splines->CreateSpline(&position.y, position.y - ((App->map->data.tile_height / 3) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::DOWN:
					App->easing_splines->CreateSpline(&position.y, position.y + ((App->map->data.tile_height / 3) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::RIGHT:
					App->easing_splines->CreateSpline(&position.x, position.x + ((App->map->data.tile_width / 3) * distance_to_travel), 1000, EASE_OUT_QUINT);
					break;
				case Direction::LEFT:
					App->easing_splines->CreateSpline(&position.x, position.x - ((App->map->data.tile_width / 3) * distance_to_travel), 1000, EASE_OUT_CUBIC);
					break;
				}
			}
			else {
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
			
			ChangeAnimation(direction, state, type_attack);
		}

	}
	return true;
}

bool e1SuperPurpleFrog::Update(float dt)
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
			if (distance_to_travel == 1) {
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
			else {
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
					return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 2 + 1, 200, EASE);
					break;
				case Direction::DOWN:
					return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 2 + 1, 200, EASE);
					break;
				case Direction::RIGHT:
					return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 2 + 1, 200, EASE);
					break;
				case Direction::LEFT:
					return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 2 + 1, 200, EASE);
					break;
				}
			}
			App->audio->PlayFx(App->scene->fx_frog_attack);
			CheckBasicAttackEffects(e1Entity::EntityType::PLAYER, direction, stats.attack_power);
			state = State::AFTER_ATTACK;
			ChangeAnimation(direction, state);
			time_attack = SDL_GetTicks();
		}
	}
	if (state == State::AFTER_ATTACK) {
		if (RestTimeAfterAttack(time_attack)) {
			CenterOnTile();
			target_position = position;
			initial_position = position;
			movement_count = { 0,0 };
			
		}
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

void e1SuperPurpleFrog::IdAnimToEnum()
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

bool e1SuperPurpleFrog::CanAttack()
{
	bool ret = false;

	iPoint player_pos = App->scene->player->actual_tile;
	iPoint last_tile{ actual_tile.x,actual_tile.y };

	if (player_pos == actual_tile + iPoint{ 0,3 }) {
		distance_to_travel = 5;
		direction = Direction::DOWN_LEFT;
		actual_tile += iPoint{ 0,2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,-3 }) {
		distance_to_travel = 5;
		direction = Direction::UP_RIGHT;
		actual_tile += iPoint{ 0,-2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,0 }) {
		distance_to_travel = 5;
		direction = Direction::UP_LEFT;
		actual_tile += iPoint{ -2,0 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,0 }) {
		distance_to_travel = 5;
		direction = Direction::DOWN_RIGHT;
		actual_tile += iPoint{ 2,0 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,3 }) {
		distance_to_travel = 8;
		direction = Direction::DOWN;
		actual_tile += iPoint{ 2,2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,-3 }) {
		distance_to_travel = 8;
		direction = Direction::UP;
		actual_tile += iPoint{ -2,-2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,3 }) {
		distance_to_travel = 8;
		direction = Direction::LEFT;
		actual_tile += iPoint{ -2,2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,-3 }) {
		distance_to_travel = 8;
		direction = Direction::RIGHT;
		actual_tile += iPoint{ 2,-2 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,2 }) {
		distance_to_travel = 3;
		direction = Direction::DOWN_LEFT;
		actual_tile += iPoint{ 0,1 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,-2 }) {
		distance_to_travel = 3;
		direction = Direction::UP_RIGHT;
		actual_tile += iPoint{ 0,-1 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,0 }) {
		distance_to_travel = 3;
		direction = Direction::UP_LEFT;
		actual_tile += iPoint{ -1,0 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,0 }) {
		distance_to_travel = 3;
		direction = Direction::DOWN_RIGHT;
		actual_tile += iPoint{ 1,0 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,2 }) {
		distance_to_travel = 5;
		direction = Direction::DOWN;
		actual_tile += iPoint{ 1,1 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,-2 }) {
		distance_to_travel = 5;
		direction = Direction::UP;
		actual_tile += iPoint{ -1,-1 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,2 }) {
		distance_to_travel = 5;
		direction = Direction::LEFT;
		actual_tile += iPoint{ -1,1 };
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,-2 }) {
		distance_to_travel = 5;
		actual_tile += iPoint{ 1,-1 };
		direction = Direction::RIGHT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,1 }) {
		distance_to_travel = 1;
		direction = Direction::DOWN_LEFT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,-1 }) {
		distance_to_travel = 1;
		direction = Direction::UP_RIGHT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -1,0 }) {
		distance_to_travel = 1;
		direction = Direction::UP_LEFT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 1,0 }) {
		distance_to_travel = 1;
		direction = Direction::DOWN_RIGHT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 1,1 }) {
		distance_to_travel = 1;
		direction = Direction::DOWN;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -1,-1 }) {
		distance_to_travel = 1;
		direction = Direction::UP;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -1,1 }) {
		distance_to_travel = 1;
		direction = Direction::LEFT;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 1,-1 }) {
		distance_to_travel = 1;
		direction = Direction::RIGHT;
		ret = true;
	}

	if (!App->map->IsWalkable(actual_tile, false)) {
		actual_tile = last_tile;
		ret = false;
	}

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item) != this && (*item)->actual_tile == actual_tile) {
			actual_tile = last_tile;
			ret = false;
		}
	}

	return ret;
}
