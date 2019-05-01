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

bool e1BlueSlime::PreUpdate()
{
	BROFILER_CATEGORY("BlueDog PreUpdate", Profiler::Color::Yellow);

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
		//if (!IsPlayerNextTile()) {
		MovementLogic();
		//}
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

bool e1BlueSlime::Update(float dt)
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
			ChangeTurn(type);
		}
	}

	if (App->debug)
		App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	return true;
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