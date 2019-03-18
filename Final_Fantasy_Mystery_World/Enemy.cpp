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

Enemy::Enemy(const int &x, const int &y) : DynamicEntity(x,y)
{
	//LoadXML("player_config.xml");
	LoadEntityData("entities/Enemy.tsx");
	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");

	type = Entity::EntityType::ENEMY;
	ground = App->tex->Load("textures/enemy_pos.png");
	current_animation = &IdleLeft;

	SetPivot(12, 30);

	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	has_turn = false;
	velocity.x = 160;
	velocity.y = 80;
	
	position.x += 3;
	position.y -= 2;
	target_position = position;
	initial_position = position;
	movement_count = { 0,0 };
	actual_tile = App->map->WorldToMap(position.x + pivot.x, position.y + pivot.y);
	
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
				actual_tile += {0, 1};
			}
			else if (target.x > origin.x && target.y == origin.y) {
				direction = Direction::DOWN_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
				actual_tile += {1, 0};
			}
			else if (target.x == origin.x && target.y < origin.y) {
				direction = Direction::UP_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
				actual_tile += {0, -1};
			}
			else if (target.x < origin.x && target.y == origin.y) {
				direction = Direction::UP_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
				actual_tile += {-1, 0};
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

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x, App->map->MapToWorld(actual_tile.x, actual_tile.y).y);

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
