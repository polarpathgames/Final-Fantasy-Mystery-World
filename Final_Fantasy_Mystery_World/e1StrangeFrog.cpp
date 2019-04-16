#include "e1StrangeFrog.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"

e1StrangeFrog::e1StrangeFrog(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/StrangeFrog.tsx");

	enemy_type = EnemyType::STRANGE_FROG;

	position.x;
	position.y -= 25;

	target_position = position;
	initial_position = position;

	InitStats();
}

e1StrangeFrog::~e1StrangeFrog()
{
}

bool e1StrangeFrog::PreUpdate()
{
	if (state == State::IDLE) {
		if (IsPlayerNextTile()) {
			state = State::BEFORE_ATTACK;
			time_to_wait_before_attack = SDL_GetTicks();
		}
		else {
			state = State::WALKING; //Aixo sha de canviar I know :D
		}

	}
	if (state == State::WALKING) {
		if (!IsPlayerNextTile()) {
			MovementLogic();
		}
	}
	if (state == State::BEFORE_ATTACK) {
		if (time_to_wait_before_attack < SDL_GetTicks() - 250) {
			type_attack = Attacks::BASIC;
			state = State::ATTACKING;
			ChangeAnimation(direction, state, type_attack);
		}

	}
	return true;
}

bool e1StrangeFrog::Update(float dt)
{
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
			CheckBasicAttackEfects(e1Entity::EntityType::PLAYER, direction, stats.attack_power);
			state = State::AFTER_ATTACK;
			ChangeAnimation(direction, state);
			time_attack = SDL_GetTicks();
		}
	}
	if (state == State::AFTER_ATTACK) {
		RestTimeAfterAttack(time_attack);
	}


	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	return true;
}

void e1StrangeFrog::InitStats()
{
	stats.attack_power = 25;
	stats.live = 100;

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

		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 39:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 54:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 650:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 63:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 69:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		}

	}

}
