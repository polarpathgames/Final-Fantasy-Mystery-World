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
	//LoadXML("player_config.xml");
	LoadEntityData("entities/Animist.tsx");
	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");
	position.x = 100;
	position.y = 50;

	current_animation = &IdleLeft;

	direction = Direction::LEFT;
	state = State::IDLE;

	iPoint p;
	p = App->map->WorldToMap(position.x, position.y);
	p = App->map->MapToWorld(p.x, p.y);
	position.x = p.x + 3;
	position.y = p.y + 5;
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
	if (state == State::IDLE) {
		state = State::WALKING; //Aixo sha de canviar I know :D
	}
	if (state == State::WALKING) {
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(App->entity_manager->GetPlayerData()->position.x, App->entity_manager->GetPlayerData()->position.y);
		App->pathfinding->CreatePath(origin, destination);

		iPoint target = App->pathfinding->GetLastPath();
		if (target_position == position) {
			if (target.x == origin.x && target.y > origin.y) {
				direction = Direction::DOWN_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (target.x > origin.x && target.y == origin.y) {
				direction = Direction::DOWN_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (target.x == origin.x && target.y < origin.y) {
				direction = Direction::UP_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
			}
			else if (target.x < origin.x && target.y == origin.y) {
				direction = Direction::UP_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
			}
			ChangeTurn(type);
		}
	}


	

	return true;
}

bool Enemy::Update(float dt)
{
	if (state == State::WALKING) {
		switch (direction)
		{
		case Direction::DOWN_LEFT:
			if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				state = State::IDLE;
			}
			break;
		case Direction::UP_RIGHT:
			if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				state = State::IDLE;
			}
			break;
		case Direction::UP_LEFT:
			if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				state = State::IDLE;
			}
			break;
		case Direction::DOWN_RIGHT:
			if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				state = State::IDLE;
			}
			break;
		case Direction::LEFT:
			if (position.x >= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
			}
			break;
		case Direction::RIGHT:
			if (position.x <= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
			}
			break;
		case Direction::UP:
			if (position.x == initial_position.x + movement_count.x && position.y >= initial_position.y + movement_count.y) {
				position.y -= floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				ChangeTurn(type);
			}
			break;
		case Direction::DOWN:
			if (position.x == initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.y += floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleLeft;
				ChangeTurn(type);
			}
			break;
		default:
			break;
		}
	}


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
