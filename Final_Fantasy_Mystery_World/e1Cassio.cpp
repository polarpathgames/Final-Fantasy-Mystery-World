#include "e1Cassio.h"
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

e1Cassio::e1Cassio(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Cassio.tsx");
	name.assign("Cassio");
	enemy_type = EnemyType::CASSIO;
	range_to_distance_attack = 3U;

	SetPivot(14, 33);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1Cassio::~e1Cassio()
{
	if (poison_particle != nullptr)
		App->particles->DeleteFollow_p(poison_particle);
}

void e1Cassio::PrepareDistanceAttack()
{
	App->audio->PlayFx(fx_poison_cassio);
	particle_position = position;
	lerp_translation = 0.f;
	poison_particle = App->particles->CreateFollow(nullptr, &particle_position, { 2,6,2,2 }, { 10,10 }, { 15,5 }, 4, 60, true, false, { 0,5 });
}

bool e1Cassio::IsSpecialAttack1Finished()
{
	return particle_position == App->scene->player->position || lerp_translation > 1.f;
}

void e1Cassio::AfterSpecialAttack1()
{
	App->audio->PlayFx(fx_claw_cassio);
	lerp_translation = 0.f;
	App->particles->DeleteFollow_p(poison_particle);
	poison_particle = nullptr;
	if (App->entity_manager->IsPlayerPoisonedOrBurned() == false)
		App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, App->scene->player->position.x, App->scene->player->position.y, "poison");
}

void e1Cassio::UpdateEnemy()
{
	if (state == State::ATTACKING && poison_particle != nullptr) {
		particle_position = lerp(position, App->scene->player->GetPosition() + iPoint{ 0, -10 }, lerp_translation).AproximateToIntFloor();
		lerp_translation += lerp_by;
	}
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
		case 48:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_1;
			break;
		case 54:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_1;
			break;
		case 50:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_1;
			break;
		case 52:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_1;
			break;
		case 72:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 84:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 77:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 89:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 73:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 85:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 90:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 91:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
