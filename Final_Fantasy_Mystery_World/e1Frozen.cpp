#include "e1Frozen.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "m1Audio.h"
#include "e1State.h"
#include "Brofiler/Brofiler.h"

e1Frozen::e1Frozen(const int& x, const int& y) :e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Frozen.tsx");
	name.assign("Frozen");
	enemy_type = EnemyType::FROZEN;
	range_to_distance_attack = 3;
	InitStats();

	CenterOnTile();

	target_position = position;
	initial_position = position;
}

e1Frozen::~e1Frozen()
{
}

void e1Frozen::UpdateEnemy()
{
	if (stats.live <= stats.max_live * 0.5F) {
		phase = Phase::HARD;
	}
	
	if (times_hitted >= 1) {
		if (phase == Phase::NORMAL) {
			//tp
		}
		else {
			// summon slimes
		}
	}
}

void e1Frozen::PrepareDistanceAttack()
{
	if (phase == Phase::NORMAL) {
		e1Particles* needle = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, position.x, position.y, "");
		needle->SetParticle(e1Particles::ParticleType::ARROW, direction);
	}
	else {
		if (!App->entity_manager->ThereIsEntity("blizzard")) {
			e1State* blizz = (e1State*)App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, 0, 0, "blizzard");
			blizz->SetMaxNumberHit(3U);
		}
		else {

		}
	}
}

bool e1Frozen::IsSpecialAttack1Finished()
{
	return true;
}

void e1Frozen::AfetSpecialAttack1()
{
}

void e1Frozen::IdAnimToEnum()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 5:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 11:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 14:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 15:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 40:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 70:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 50:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 19:
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
		case 16:
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
		case 41:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 61:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_1;
			break;
		case 62:
			data.animations[i].animType = AnimationState::ABILITY_UP_1;
			break;
		case 64:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_1;
			break;
		case 66:
			data.animations[i].animType = AnimationState::ABILITY_RIGHT_1;
			break;
		case 80:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_1;
			break;
		case 110:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_1;
			break;
		case 100:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_1;
			break;
		case 90:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_1;
			break;
		case 644:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 81:
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
		case 82:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 89:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
