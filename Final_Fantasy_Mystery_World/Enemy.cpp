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

	direction = Direction::LEFT;


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
	iPoint origin = App->map->WorldToMap(position.x - 5, position.y - 6);
	iPoint destination = App->map->WorldToMap(App->entity_manager->GetPlayerData()->position.x - 11, App->entity_manager->GetPlayerData()->position.y - 12);

	App->pathfinding->CreatePath(origin, destination);

	iPoint target = App->pathfinding->GetLastPath();

	if (target.x < origin.x && target.y == origin.y) {
		position.x -= 32;
		position.y -= 16;
	}
	if (target.x == origin.x && target.y < origin.y) {
		position.x += 32;
		position.y -= 16;
	}
	if (target.x == origin.x && target.y > origin.y) {
		position.x -= 32;
		position.y += 16;
	}
	if (target.x > origin.x && target.y == origin.y) {
		position.x += 32;
		position.y += 16;
	}

	return true;
}

bool Enemy::Update(float dt)
{
	
	



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
