#include "e1CarnivorousPlant.h"
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

e1CarnivorousPlant::e1CarnivorousPlant(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/CarnivorousPlant.tsx");

	enemy_type = EnemyType::CARNIVOROUS_PLANT;

	state = State::SLEEPING;

	position.x -= 6;
	position.y -= 22;
	SetPivot(21,33);
	Sleep.PushBack({272, 2, 43, 40});
	Sleep.PushBack({272, 253, 43, 40});
	Sleep.PushBack({ 272, 44, 43, 40 });
	Sleep.PushBack({ 272, 295, 43, 40 });
	Sleep.speed = 2;

	current_animation = &Sleep;
	
	target_position = position;
	initial_position = position;
	InitStats();
}

e1CarnivorousPlant::~e1CarnivorousPlant()
{
}

bool e1CarnivorousPlant::PreUpdate()
{
	BROFILER_CATEGORY("CarnivorousPlant PreUpdate", Profiler::Color::Yellow);

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
	if (state == State::SLEEPING) {
		if (IsPlayerNextTile()) {
			state = State::IDLE;
		}
		ChangeTurn(type);
	}
	return true;
}

bool e1CarnivorousPlant::Update(float dt)
{
	BROFILER_CATEGORY("CarnivorousPlant Update", Profiler::Color::Yellow);

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
			App->audio->PlayFx(App->scene->fx_plant_attack);
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
			int drop = App->random.Generate(1, 3);
			if (drop == 1)
				Drop();
			App->audio->PlayFx(App->scene->fx_kill_enemy);
			App->scene->player->UpdateExperience(stats.experience);
			App->map->quest_rooms->AddEntityToNotRepeat(original_position);
			to_delete = true;
			ChangeTurn(type);
		}
	}

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	return true;
}

void e1CarnivorousPlant::IdAnimToEnum()
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
