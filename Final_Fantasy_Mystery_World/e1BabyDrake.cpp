#include "e1BabyDrake.h"
#include "e1Enemy.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "m1ParticleManager.h"
#include "m1EntityManager.h"
#include "p1Follow.h"
#include "p2Math.h"
#include "m1FadeToBlack.h"
#include "Brofiler/Brofiler.h"

e1BabyDrake::e1BabyDrake(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/BabyDrake.tsx");
	name.assign("BabyDrake");
	enemy_type = EnemyType::BABY_DRAKE;
	range_to_distance_attack = 2U;

	SetPivot(17, 31);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1BabyDrake::~e1BabyDrake()
{
	if (fire_particle != nullptr)
		App->particles->DeleteFollow_p(fire_particle);

}

void e1BabyDrake::PrepareDistanceAttack()
{
	PrepareParticle();
}

void e1BabyDrake::AfterSpecialAttack1()
{
	DeleteParticle();
}

bool e1BabyDrake::IsSpecialAttack1Finished()
{
	return particle_position == App->scene->player->position || lerp_translation > 1.f;
}

void e1BabyDrake::PrepareBasicAttack()
{
	PrepareParticle();
}

void e1BabyDrake::FinishBasicAttack()
{
	DeleteParticle();
	if (App->scene->player->state != State::SLEEPING) {
		if (!first_hit) {
			first_hit = true;
			SuperHit();
		}
		else if (stats.max_live * 0.66F >= stats.live && !second_hit) {
			second_hit = true;
			SuperHit();
		}
		else if (stats.max_live * 0.33F >= stats.live && !third_hit) {
			third_hit = true;
			SuperHit();
		}
	}
}

void e1BabyDrake::UpdateEnemy()
{
	if (state == State::ATTACKING && fire_particle != nullptr) {
		particle_position = lerp(position, App->scene->player->GetPosition() + iPoint{ 0, -10 }, lerp_translation).AproximateToIntFloor();
		lerp_translation += lerp_by;
	}
}

void e1BabyDrake::SuperHit()
{
	iPoint player_tile = App->scene->player->actual_tile;
	App->scene->player->state = State::SLEEPING;

	if (player_tile == actual_tile + iPoint{ 0,1 } && App->map->IsWalkable(player_tile + iPoint{ 0,3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - (App->map->data.tile_width)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + (App->map->data.tile_height)*1.5F, 500, EASE_OUT_QUINT);
		App->scene->player->actual_tile += {0, 3};
		App->scene->player->direction = Direction::UP_RIGHT;
		App->scene->player->current_animation = &App->scene->player->IdleUpRight;
	}
	else if (player_tile == actual_tile + iPoint{ 0,-1 } && App->map->IsWalkable(player_tile + iPoint{ 0,-3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + (App->map->data.tile_width)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - (App->map->data.tile_height)*1.5F, 500, EASE_OUT_QUINT);
		App->scene->player->actual_tile += {0, -3};
		App->scene->player->direction = Direction::DOWN_LEFT;
		App->scene->player->current_animation = &App->scene->player->IdleDownLeft;
	}
	else if (player_tile == actual_tile + iPoint{ 1,0 } && App->map->IsWalkable(player_tile + iPoint{ 3,0 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + (App->map->data.tile_width)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + (App->map->data.tile_height)*1.5F, 500, EASE_OUT_QUINT);
		App->scene->player->actual_tile += {3, 0};
		App->scene->player->direction = Direction::UP_LEFT;
		App->scene->player->current_animation = &App->scene->player->IdleUpLeft;
	}
	else if (player_tile == actual_tile + iPoint{ -1,0 } && App->map->IsWalkable(player_tile + iPoint{ -3,0 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - (App->map->data.tile_width)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - (App->map->data.tile_height)*1.5F, 500, EASE_OUT_QUINT);
		App->scene->player->actual_tile += {-3, 0};
		App->scene->player->direction = Direction::DOWN_RIGHT;
		App->scene->player->current_animation = &App->scene->player->IdleDownRight;
	}
	else if (player_tile == actual_tile + iPoint{ -1,-1 } && App->map->IsWalkable(player_tile + iPoint{ -3,-3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y - (App->map->data.tile_height * 2)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->scene->player->actual_tile += {-3, -3};
		App->scene->player->direction = Direction::DOWN;
		App->scene->player->current_animation = &App->scene->player->IdleDown;
	}
	else if (player_tile == actual_tile + iPoint{ 1,1 } && App->map->IsWalkable(player_tile + iPoint{ 3,3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.y, App->scene->player->position.y + (App->map->data.tile_height * 2)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->scene->player->actual_tile += {3, 3};
		App->scene->player->direction = Direction::UP;
		App->scene->player->current_animation = &App->scene->player->IdleUp;
	}
	else if (player_tile == actual_tile + iPoint{ -1,1 } && App->map->IsWalkable(player_tile + iPoint{ -3,3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x - (App->map->data.tile_width * 2)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->scene->player->actual_tile += {-3, 3};
		App->scene->player->direction = Direction::RIGHT;
		App->scene->player->current_animation = &App->scene->player->IdleRight;
	}
	else if (player_tile == actual_tile + iPoint{ 1,-1 } && App->map->IsWalkable(player_tile + iPoint{ 3,-3 }, false)) {
		App->easing_splines->CreateSpline(&App->scene->player->position.x, App->scene->player->position.x + (App->map->data.tile_width * 2)*1.5F, 500, EASE_OUT_QUINT, std::bind(&e1Player::SetPlayerIdle, App->scene->player));
		App->scene->player->actual_tile += {3, -3};
		App->scene->player->direction = Direction::LEFT;
		App->scene->player->current_animation = &App->scene->player->IdleLeft;
	}
	else 
		App->scene->player->state = State::IDLE;
}

void e1BabyDrake::Death()
{
	if (current_animation->Finished() && drawable) {
		Drop();
		App->audio->PlayFx(App->scene->fx_kill_enemy);
		drawable = false;
		App->scene->player->UpdateExperience(stats.experience);
		App->map->quest_rooms->AddEntityToNotRepeat(original_position);
	}
	else if (!drawable) {
		App->fade_to_black->FadeToBlack(4.0F, true);
		to_delete = true;
		turn_done = true;
	}
}

void e1BabyDrake::PrepareParticle()
{
	particle_position = position;
	lerp_translation = 0.f;
	fire_particle = App->particles->CreateFollow(nullptr, &particle_position, { 4,4,2,2 }, { 10,10 }, { 15,5 }, 4, 60, true, false, { 0,5 });

}

void e1BabyDrake::DeleteParticle()
{
	lerp_translation = 0.f;
	App->particles->DeleteFollow_p(fire_particle);
	fire_particle = nullptr;
	if (App->entity_manager->IsPlayerPoisonedOrBurned() == false)
		App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, App->scene->player->position.x, App->scene->player->position.y, "fire");
}

void e1BabyDrake::IdAnimToEnum()
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
		case 40:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 28:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 37:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 14:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 17:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 23:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 20:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 49:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 53:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 65:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 48:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_1;
			break;
		case 52:
			data.animations[i].animType = AnimationState::ABILITY_UP_1;
			break;
		case 64:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_1;
			break;
		case 61:
			data.animations[i].animType = AnimationState::ABILITY_RIGHT_1;
			break;
		case 25:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_1;
			break;
		case 41:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_1;
			break;
		case 29:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_1;
			break;
		case 36:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_1;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 78:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 84:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 90:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 73:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 74:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 85:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 79:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
