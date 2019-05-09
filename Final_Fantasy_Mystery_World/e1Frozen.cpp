#include "e1Frozen.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "m1Audio.h"
#include "Brofiler/Brofiler.h"

e1Frozen::e1Frozen(const int& x, const int& y) :e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Frozen.tsx");
	name.assign("Frozen");
	enemy_type = EnemyType::FROZEN;
	range_to_distance_attack = 3;
	InitStats();
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
		if(App->entity_manager->ThereIsEntity())
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
		switch (2) {
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
