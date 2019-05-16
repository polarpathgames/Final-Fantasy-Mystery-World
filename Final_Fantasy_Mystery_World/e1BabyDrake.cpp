#include "e1BabyDrake.h"
#include "e1Enemy.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "App.h"
#include "m1Audio.h"
#include "m1ParticleManager.h"
#include "m1EntityManager.h"
#include "p1Follow.h"
#include "p2Math.h"
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

void e1BabyDrake::AfetSpecialAttack1()
{
	DeleteParticle();
}

void e1BabyDrake::PrepareBasicAttack()
{
	PrepareParticle();
}

void e1BabyDrake::FinishBasicAttack()
{
	DeleteParticle();
}

void e1BabyDrake::UpdateEnemy()
{
	if (state == State::ATTACKING && fire_particle != nullptr) {
		particle_position = lerp(position, App->scene->player->GetPosition() + iPoint{ 0, -10 }, lerp_translation).AproximateToIntFloor();
		lerp_translation += lerp_by;
	}
}

void e1BabyDrake::PrepareParticle()
{
	particle_position = position;
	lerp_translation = 0.f;
	fire_particle = App->particles->CreateFollow(nullptr, &particle_position, { 2,6,2,2 }, { 10,10 }, { 15,5 }, 4, 60, true, false, { 0,5 });
}

void e1BabyDrake::DeleteParticle()
{
	lerp_translation = 0.f;
	App->particles->DeleteFollow_p(fire_particle);
	fire_particle = nullptr;
	if (App->entity_manager->IsPlayerPoisoned() == false)
		App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, App->scene->player->position.x, App->scene->player->position.y, "poison");
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
