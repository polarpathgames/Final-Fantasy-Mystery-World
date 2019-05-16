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
	e1Frozen::InitStats();

	CenterOnTile();
	target_position = position;
	initial_position = position;

	tp_number_hit = tp_number_hit_phase1;

	tp_timer.Stop();
}

e1Frozen::~e1Frozen()
{
}

bool e1Frozen::PreUpdate()
{

	if (phase == Phase::NORMAL && stats.live <= stats.max_live * 0.5F) {
		phase = Phase::HARD;
		tp_last_number_hit = times_hitted;
		DoTeleport();
		want_to_attack = false;
		tp_number_hit = tp_number_hit_phase2;
	}

	if (tp_last_number_hit != times_hitted) {
		tp_done = false;
	}

	if (times_hitted != 0 && !tp_done) {
		if (times_hitted % tp_number_hit == 0 && want_to_attack) {
			tp_last_number_hit = times_hitted;
			DoTeleport();
			want_to_attack = false;
		}
	}

	if (!tp_timer.IsRunning()) {
		e1Enemy::PreUpdate();
	}
	else {
		Escape();
	}

	if (type_attack == Attacks::SPECIAL_1) {
		if (phase == Phase::NORMAL) {
			if ((int)current_animation->current_frame == 7) {
				if (laser_play_fx)
				{
					App->audio->PlayFx(fx_laser);
					laser_play_fx = false;
				}
					

				e1Particles* needle = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, actual_tile.x, actual_tile.y, "");
				needle->position.x = GetPosition().x;
				needle->SetParticle(e1Particles::ParticleType::ICE_STAKE, direction);
			}
		}
		else {
			if (App->entity_manager->ThereIsEntity("blizzard")) {
				if ((int)current_animation->current_frame == 7) {
					e1Particles* needle = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, actual_tile.x, actual_tile.y, "");
					needle->position.x = GetPosition().x;
					needle->SetParticle(e1Particles::ParticleType::ICE_STAKE, direction);
				}
			}
			else {
				if (current_animation->Finished()) {
					e1State* blizz = (e1State*)App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, 0, 0, "blizzard");
					blizz->SetMaxNumberHit(3U);
				}
			}
		}
	}
	return true;
}

void e1Frozen::PrepareDistanceAttack()
{
	laser_play_fx = true;

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
		if (phase == Phase::HARD) {
			SummomBlueSlimes();
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
		tp_done = true;
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
		case 20:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 24:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 30:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 34:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 25:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 31:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 35:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 120:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 130:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 140:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 150:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 160:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_1;
			break;
		case 170:
			data.animations[i].animType = AnimationState::ABILITY_UP_1;
			break;
		case 180:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_1;
			break;
		case 190:
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
		case 200:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 220:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 210:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 230:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		case 201:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;
		case 221:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;
		case 211:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;
		case 231:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;
		}
	}
}

void e1Frozen::InitStats()
{
	e1Enemy::InitStats();

	for (std::list<Property<int>*>::iterator item = general_properties.properties.begin(); item != general_properties.properties.end(); item++) {
		if (strcmp((*item)->GetName(), "special_attack_power") == 0) {
			stats.special_attack_damage = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "hits_to_tp_phase1") == 0) {
			tp_number_hit_phase1 = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "hits_to_tp_phase2") == 0) {
			tp_number_hit_phase2 = (*item)->GetValue();
		}
	}
}
