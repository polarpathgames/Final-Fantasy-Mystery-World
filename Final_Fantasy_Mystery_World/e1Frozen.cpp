#include "e1Frozen.h"
#include "App.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1EntityManager.h"
#include "m1Audio.h"
#include "e1State.h"
#include "p2Log.h"
#include "e1BlueSlime.h"
#include "Brofiler/Brofiler.h"

e1Frozen::e1Frozen(const int& x, const int& y) :e1Enemy(x, y)
{
	LoadEntityData("assets/entities/Frozen.tsx");
	name.assign("Frozen");
	enemy_type = EnemyType::FROZEN;
	range_to_distance_attack = 3;
	InitStats();

	CenterOnTile();
	stats.max_live = 500;
	stats.live = 500; ///////////////remember to delete this/////////////////////////////////////////////////////////////////////////////
	target_position = position;
	initial_position = position;
}

e1Frozen::~e1Frozen()
{
}

#include "m1Input.h" //test

bool e1Frozen::PreUpdate()
{
	if (times_hitted % tp_number_hit == 0 && want_to_attack) {
		want_to_attack = false;
		if (phase == Phase::NORMAL) {
			DoTeleport();
		}
		else if (phase == Phase::HARD) {
			SummomBlueSlimes();
		}
	}

	if (!tp_timer.IsRunning()) {
		e1Enemy::PreUpdate();
	}
	else {
		Escape();
	}

	if (stats.live <= stats.max_live * 0.5F || App->input->GetKeyRepeat(SDL_SCANCODE_1)) {
		phase = Phase::HARD;
	}

	if (type_attack == Attacks::SPECIAL_1) {
		if (phase == Phase::NORMAL) {
			if ((int)current_animation->current_frame == 7) {
				e1Particles* needle = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, actual_tile.x, actual_tile.y, "");
				needle->position.x = GetPosition().x;
				needle->SetParticle(e1Particles::ParticleType::ICE_STAKE, direction);
			}
		}
		else {
			if (current_animation->Finished() && !App->entity_manager->ThereIsEntity("blizzard")) {
				e1State* blizz = (e1State*)App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, 0, 0, "blizzard");
				blizz->SetMaxNumberHit(3U);
			}
			else {

			}
		}
	}
	return true;
}

void e1Frozen::PrepareDistanceAttack()
{
	
}

bool e1Frozen::IsSpecialAttack1Finished()
{
	return (current_animation->Finished() && !App->entity_manager->ThereIsEntity("ice stake"));
}

void e1Frozen::AfetSpecialAttack1()
{
}

void e1Frozen::SummomBlueSlimes()
{
	if (!App->entity_manager->IsInEntitiesVector(slime_1)) {
		if (App->map->IsWalkable(actual_tile + iPoint{ 0,1 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 0,1 } && (slime_2 == nullptr || (slime_2 != nullptr &&slime_2->actual_tile != actual_tile + iPoint{ 0,1 }))) {
			slime_1 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x, actual_tile.y + 1).x, App->map->MapToWorld(actual_tile.x, actual_tile.y + 1).y, "BlueSlime");
			slime_1->turn_done = true;
			slime_1->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ 1,0 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 1,0 } && (slime_2 == nullptr || (slime_2 != nullptr &&slime_2->actual_tile != actual_tile + iPoint{ 1,0 }))) {
			slime_1 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x + 1, actual_tile.y).x, App->map->MapToWorld(actual_tile.x + 1, actual_tile.y).y, "BlueSlime");
			slime_1->turn_done = true;
			slime_1->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ -1,0 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ -1,0 } && (slime_2 == nullptr || (slime_2 != nullptr &&slime_2->actual_tile != actual_tile + iPoint{ -1,0 }))) {
			slime_1 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x - 1, actual_tile.y).x, App->map->MapToWorld(actual_tile.x - 1, actual_tile.y).y, "BlueSlime");
			slime_1->turn_done = true;
			slime_1->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ 0,-1 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 0,-1 } && (slime_2 == nullptr || (slime_2 != nullptr &&slime_2->actual_tile != actual_tile + iPoint{ 0,-1 }))) {
			slime_1 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x, actual_tile.y - 1).x, App->map->MapToWorld(actual_tile.x, actual_tile.y - 1).y, "BlueSlime");
			slime_1->turn_done = true;
			slime_1->LookToPlayer();
		}
	}
	if (!App->entity_manager->IsInEntitiesVector(slime_2)) {
		if (App->map->IsWalkable(actual_tile + iPoint{ 0,1 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 0,1 } && (slime_1 == nullptr || (slime_1 != nullptr &&slime_1->actual_tile != actual_tile + iPoint{ 0,1 }))) {
			slime_2 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x, actual_tile.y + 1).x, App->map->MapToWorld(actual_tile.x, actual_tile.y + 1).y, "BlueSlime");
			slime_2->turn_done = true;
			slime_2->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ 1,0 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 1,0 } && (slime_1 == nullptr || (slime_1 != nullptr &&slime_1->actual_tile != actual_tile + iPoint{ 1,0 }))) {
			slime_2 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x + 1, actual_tile.y).x, App->map->MapToWorld(actual_tile.x + 1, actual_tile.y).y, "BlueSlime");
			slime_2->turn_done = true;
			slime_2->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ -1,0 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ -1,0 } && (slime_1 == nullptr || (slime_1 != nullptr &&slime_1->actual_tile != actual_tile + iPoint{ -1,0 }))) {
			slime_2 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x - 1, actual_tile.y).x, App->map->MapToWorld(actual_tile.x - 1, actual_tile.y).y, "BlueSlime");
			slime_2->turn_done = true;
			slime_2->LookToPlayer();
		}
		else if (App->map->IsWalkable(actual_tile + iPoint{ 0,-1 }, false) && App->scene->player->actual_tile != actual_tile + iPoint{ 0,-1 } && (slime_1 == nullptr || (slime_1 != nullptr &&slime_1->actual_tile != actual_tile + iPoint{ 0,-1 }))) {
			slime_2 = (e1BlueSlime*)App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_SLIME, App->map->MapToWorld(actual_tile.x, actual_tile.y - 1).x, App->map->MapToWorld(actual_tile.x, actual_tile.y - 1).y, "BlueSlime");
			slime_2->turn_done = true;
			slime_2->LookToPlayer();
		}
	}
}

void e1Frozen::Escape()
{
	if (phase == Phase::NORMAL) {
		if (tp_timer.ReadSec() >= 0.5f) {
			actual_tile = tp_location;
			state = State::IDLE;
			drawable = true;
			CenterOnTile();
			movement_count = { 0,0 };
			target_position = position;
			initial_position = position;
			want_to_attack = true;
			tp_timer.Stop();
			turn_done = true;
			App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-10 }, { 0,0,2,2 }, RANDOM, { 20,20 }, { 40,10 }, { 15,-5 }, P_NON, 200, 5);
			LookToPlayer();
			//SummomBlueSlimes();
		}
	}
}

void e1Frozen::DoTeleport()
{
	iPoint destination = App->entity_manager->FindRandomFreeTileOnRange(App->scene->player->actual_tile, 3);

	if (destination != App->scene->player->actual_tile) {
		tp_location = destination;
		tp_timer.Start();
		drawable = false;
		App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-10 }, { 0,0,2,2 }, RANDOM, { 20,20 }, { 40,10 }, { 15,5 }, P_NON, 200, 5);
	}
	else {
		turn_done = true;
	}
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
