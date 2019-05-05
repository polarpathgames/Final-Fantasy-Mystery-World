#include "e1Cassio.h"
#include "e1Enemy.h"
#include "SDL/include/SDL.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "Brofiler/Brofiler.h"

e1Cassio::e1Cassio(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Cassio.tsx");

	enemy_type = EnemyType::CASSIO;

	SetPivot(14, 33);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1Cassio::~e1Cassio()
{
}

bool e1Cassio::PreUpdate()
{
	BROFILER_CATEGORY("BlueDog PreUpdate", Profiler::Color::Yellow);

	if (state == State::IDLE) {
		if (IsPlayerNextTile() || CanAttackDistance()) {
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
			if (IsPlayerNextTile()) {
				type_attack = Attacks::BASIC;
				state = State::ATTACKING;
				ChangeAnimation(direction, state, type_attack);
			}
			else
				PrepareDistanceAttack();
		}
	}
	return true;
}

bool e1Cassio::Update(float dt)
{
	BROFILER_CATEGORY("BlueDog Update", Profiler::Color::Yellow);

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
			if (type_attack== Attacks::BASIC)
				CheckBasicAttackEffects(e1Entity::EntityType::PLAYER, direction, stats.attack_power);
			else if (type_attack == Attacks::SPECIAL_1) {
				DistanceAttackDown.Reset();
				DistanceAttackDownLeft.Reset();
				DistanceAttackDownRight.Reset();
				DistanceAttackLeft.Reset();
				DistanceAttackRight.Reset();
				DistanceAttackUp.Reset();
				DistanceAttackUpLeft.Reset();
				DistanceAttackUpRight.Reset();
			}
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

void e1Cassio::IdAnimToEnum()
{

	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 2:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 8:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 5:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 11:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 26:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 28:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 14:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 17:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 20:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 23:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 38:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 40:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_DOWN;
			break;
		case 62:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_UP;
			break;
		case 64:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_LEFT;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_RIGHT;
			break;
		case 48:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_DOWN_LEFT;
			break;
		case 54:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_UP_RIGHT;
			break;
		case 50:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_UP_LEFT;
			break;
		case 52:
			data.animations[i].animType = AnimationState::DISTANCE_ATTACK_DOWN_RIGHT;
			break;
		case 644:
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
		case 646:
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


bool e1Cassio::CanAttackDistance()
{
	bool ret = false;

	iPoint player_pos = App->scene->player->actual_tile;

	if (player_pos == actual_tile + iPoint{ 0,3 }) {
		direction = Direction::DOWN_LEFT;
		current_animation = &IdleDownLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,-3 }) {
		direction = Direction::UP_RIGHT;
		current_animation = &IdleUpRight;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,0 }) {
		direction = Direction::UP_LEFT;
		current_animation = &IdleUpLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,0 }) {
		direction = Direction::DOWN_RIGHT;
		current_animation = &IdleDownRight;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,3 }) {
		direction = Direction::DOWN;
		current_animation = &IdleDown;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,-3 }) {
		direction = Direction::UP;
		current_animation = &IdleUp;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -3,3 }) {
		direction = Direction::LEFT;
		current_animation = &IdleLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 3,-3 }) {
		direction = Direction::RIGHT;
		current_animation = &IdleRight;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,2 }) {
		direction = Direction::DOWN_LEFT;
		current_animation = &IdleDownLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 0,-2 }) {
		direction = Direction::UP_RIGHT;
		current_animation = &IdleUpRight;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,0 }) {
		direction = Direction::UP_LEFT;
		current_animation = &IdleUpLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,0 }) {
		direction = Direction::DOWN_RIGHT;
		current_animation = &IdleDownRight;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,2 }) {
		direction = Direction::DOWN;
		current_animation = &IdleDown;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,-2 }) {
		direction = Direction::UP;
		current_animation = &IdleUp;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ -2,2 }) {
		direction = Direction::LEFT;
		current_animation = &IdleLeft;
		ret = true;
	}
	else if (player_pos == actual_tile + iPoint{ 2,-2 }) {
		direction = Direction::RIGHT;
		current_animation = &IdleRight;
		ret = true;
	}

	return ret;
}

void e1Cassio::PrepareDistanceAttack()
{
	type_attack = Attacks::SPECIAL_1;
	state = State::ATTACKING;
	if (current_animation == &IdleDown)
		current_animation = &DistanceAttackDown;
	else if (current_animation == &IdleLeft)
		current_animation = &DistanceAttackLeft;
	else if (current_animation == &IdleUp)
		current_animation = &DistanceAttackUp;
	else if (current_animation == &IdleRight)
		current_animation = &DistanceAttackRight;
	else if (current_animation == &IdleUpLeft)
		current_animation = &DistanceAttackUpLeft;
	else if (current_animation == &IdleDownLeft)
		current_animation = &DistanceAttackDownLeft;
	else if (current_animation == &IdleDownRight)
		current_animation = &DistanceAttackDownRight;
	else if (current_animation == &IdleUpRight)
		current_animation = &DistanceAttackUpRight;

}
