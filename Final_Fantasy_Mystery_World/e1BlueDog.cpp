#include "e1BlueDog.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Audio.h"

e1BlueDog::e1BlueDog(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/BlueDog.tsx");

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

bool e1BlueDog::PreUpdate()
{
	if (state == State::IDLE) {
		if (IsPlayerNextTile()) {
			state = State::BEFORE_ATTACK;
			time_to_wait_before_attack = SDL_GetTicks();
		}
		else if (actual_tile.DistanceTo(App->scene->player->actual_tile) <= 7) {
			state = State::WALKING; //Aixo sha de canviar I know :D
		}
		else ChangeTurn(type);

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

bool e1BlueDog::Update(float dt)
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
			App->audio->PlayFx(App->scene->fx_dog_attack);
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
			


		case 360:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 633:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 636:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 639:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		}

	}

}
