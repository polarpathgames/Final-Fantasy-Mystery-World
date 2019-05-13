#include "e1MegaEye.h"
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

e1MegaEye::e1MegaEye(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/MegaEye.tsx");
	name.assign("MegaEye");
	enemy_type = EnemyType::MEGA_EYE;
	range_to_distance_attack = 2U;

	SetPivot(13, 27);

	CenterOnTile();

	target_position = position;
	initial_position = position;

	InitStats();
}

e1MegaEye::~e1MegaEye()
{
	if (poison_particle != nullptr)
		App->particles->DeleteFollow_p(poison_particle);
}

void e1MegaEye::PrepareDistanceAttack()
{
	particle_position = position;
	lerp_translation = 0.f;
	poison_particle = App->particles->CreateFollow(nullptr, &particle_position, { 2,6,2,2 }, { 10,10 }, { 15,5 }, 4, 60, true, false, { 0,5 });
}

void e1MegaEye::PrepareBasicAttack() {
	particle_position = position;
	lerp_translation = 0.f;
	poison_particle = App->particles->CreateFollow(nullptr, &particle_position, { 2,6,2,2 }, { 10,10 }, { 15,5 }, 4, 60, true, false, { 0,5 });
}

bool e1MegaEye::IsSpecialAttack1Finished()
{
	return particle_position == App->scene->player->position || lerp_translation > 1.f;
}

void e1MegaEye::AfetSpecialAttack1()
{
	lerp_translation = 0.f;
	App->particles->DeleteFollow_p(poison_particle);
	poison_particle = nullptr;

}

void e1MegaEye::UpdateEnemy()
{
	if (state == State::ATTACKING && poison_particle != nullptr) {
		particle_position = l.lerp(position, App->scene->player->GetPosition() + iPoint{ 0, -10 }, lerp_translation).AproximateToIntFloor();
		lerp_translation += lerp_by;
	}
}

void e1MegaEye::FinishBasicAttack() {
	lerp_translation = 0.f;
	App->particles->DeleteFollow_p(poison_particle);
	poison_particle = nullptr;
}

void e1MegaEye::IdAnimToEnum()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 2:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 8:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 5:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 11:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
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
		case 37:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_1;
			break;
		case 39:
			data.animations[i].animType = AnimationState::ABILITY_UP_1;
			break;
		case 43:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_1;
			break;
		case 41:
			data.animations[i].animType = AnimationState::ABILITY_RIGHT_1;
			break;
		case 25:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_1;
			break;
		case 31:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_1;
			break;
		case 27:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_1;
			break;
		case 29:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_1;
			break;
		case 48:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 52:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 64:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 50:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 51:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 54:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 62:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}
