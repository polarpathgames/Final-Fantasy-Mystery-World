#include "Enemy.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Map.h"
#include <string>
#include "j1Pathfinding.h"
#include "Player.h"

Enemy::Enemy() : DynamicEntity()
{
	LoadXML("player_config.xml");

	GoLeft = LoadPushbacks(node, "GoLeft");
	IdleLeft = LoadPushbacks(node, "IdleLeft");
	position.x = 0;
	position.y = 500;

	current_animation = &IdleLeft;

	direction = idle;


	iPoint p;
	p = App->map->WorldToMap(position.x, position.y);
	p = App->map->MapToWorld(p.x, p.y);
	position.x = p.x - 5;
	position.y = p.y - 6;
	velocity.x = 160;
	velocity.y = 80;
	target_position = position;
	initial_position = position;
	movement_count = { 0,0 };
}

Enemy::~Enemy()
{
}

bool Enemy::PreUpdate()
{


	return true;
}

bool Enemy::Update(float dt)
{
	/*
	float x = App->entity_manager->GetPlayerData()->position.x;
	float y = App->entity_manager->GetPlayerData()->position.y;

	if (position.x - x < 400 && x - position.x < 400) {
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(App->entity_manager->GetPlayerData()->position.x, App->entity_manager->GetPlayerData()->position.y - App->entitymanager->GetPlayerData()->coll->rect.h);
		if (position.DistanceTo(App->entity_manager->GetPlayerData()->position)) {
			App->pathfinding->CreatePath(origin, destination);
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			for (int i = 0; i < path->Count(); i++) {
				PATH.PushBack(*path->At(i));
			}
		}
		if (PATH.Count() > 1) {
			velocity.x = -Speed;
			velocity.y = Speed;
		}
		if (App->entity_manager->GetPlayerData()->position.x < position.x) {
			position.x += velocity.x * dt;
		}
		else {
			position.x += -velocity.x * dt;
		}
		if (App->entity_manager->GetPlayerData()->position.y > position.y) {
			position.y += velocity.y * dt;
		}
		if (App->entity_manager->GetPlayerData()->position.y < position.y) {
			position.y -= velocity.y * dt;
		}
	}
	else {
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(original_pos.x, original_pos.y);
		x = original_pos.x;
		y = original_pos.y;
		fPoint originalpos{ x,y };
		if (position.DistanceTo(originalpos)) {
			App->pathfinding->CreatePath(origin, destination);
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			for (int i = 0; i < path->Count(); i++) {
				PATH.PushBack(*path->At(i));
			}
		}
		if (PATH.Count() > 1) {
			velocity.x = -Speed;
			velocity.y = Speed;
		}
		if (original_pos.x < position.x) {
			position.x += velocity.x * dt;
		}
		else {
			position.x += -velocity.x * dt;
		}
		if (original_pos.y > position.y) {
			position.y += velocity.y * dt;
		}
		if (original_pos.y < position.y) {
			position.y -= velocity.y * dt;
		}
	}

	*/
	return true;
}



bool Enemy::PostUpdate()
{
	return true;
}

bool Enemy::Load(pugi::xml_node &)
{
	return true;
}

bool Enemy::Save(pugi::xml_node &) const
{
	return true;
}

bool Enemy::CleanUp()
{
	return true;
}
