#include "Enemy.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include <string>
#include "j1Pathfinding.h"
#include "Player.h"
#include "j1Scene.h"
#include "Brofiler/Brofiler.h"

Enemy::Enemy(const int &x, const int &y) : DynamicEntity(x,y)
{
	//LoadXML("player_config.xml");
	LoadEntityData("entities/WarriorSpriteSheet.tsx");
	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");

	type = Entity::EntityType::ENEMY;
	ground = App->tex->Load("textures/enemy_pos.png");
	current_animation = &IdleDownLeft;

	SetPivot(10, 30);

	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	has_turn = false;
	velocity.x = 160;
	velocity.y = 80;
	

	movement_count = { 0,0 };
	actual_tile = App->map->WorldToMap(position.x, position.y);

	// THIS ALWAYS LAST
	position.x += 8;
	position.y -= 22;

	target_position = position;
	initial_position = position;
	
}

Enemy::~Enemy()
{
}

bool Enemy::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEnemy", Profiler::Color::Orange);

	if (state == State::IDLE) {
		if (IsPlayerNextTile()) {
			state = State::BEFORE_ATTACK;
			time_to_wait_before_attack = SDL_GetTicks();
		}
		else {
			state = State::WALKING; //Aixo sha de canviar I know :D
		}

	}
	if (state == State::WALKING) {
		if (!IsPlayerNextTile()) {
			MovementLogic();
		}
	}	
	if (state == State::BEFORE_ATTACK) {
		if (time_to_wait_before_attack < SDL_GetTicks() - 250) {
			type_attack = Attacks::BASIC;
			state = State::ATTACKING;
			ChangeAnimation(direction, state, type_attack);
		}

	}
	return true;
}

bool Enemy::Update(float dt)
{

	BROFILER_CATEGORY("UpdateEnemy", Profiler::Color::Aqua);


	if (state == State::IDLE) {
		position.x = initial_position.x + movement_count.x;
		position.y = initial_position.y + movement_count.y;
		target_position = position;
	}

	if (state == State::WALKING) {
		switch (direction)
		{
		case Direction::DOWN_LEFT:
			if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				current_animation = &GoDownLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleDownLeft;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::UP_RIGHT:
			if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoUpRight;
			}
			else {
				target_position = position;
				current_animation = &IdleUpRight;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::UP_LEFT:
			if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoUpLeft;
			}
			else {
				target_position = position;
				current_animation = &IdleUpLeft;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::DOWN_RIGHT:
			if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				current_animation = &GoDownRight;
			}
			else {
				target_position = position;
				current_animation = &IdleDownRight;
				IsPlayerNextTile();
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
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::RIGHT:
			if (position.x <= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				current_animation = &GoRight;
			}
			else {
				target_position = position;
				current_animation = &IdleRight;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::UP:
			if (position.x == initial_position.x + movement_count.x && position.y >= initial_position.y + movement_count.y) {
				position.y -= floor(velocity.y * dt);
				current_animation = &GoUp;
			}
			else {
				target_position = position;
				current_animation = &IdleUp;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		case Direction::DOWN:
			if (position.x == initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.y += floor(velocity.y * dt);
				current_animation = &GoDown;
			}
			else {
				target_position = position;
				current_animation = &IdleDown;
				IsPlayerNextTile();
				state = State::IDLE;
			}
			break;
		default:
			break;
		}
	}
	if (state == State::ATTACKING) {
		if (current_animation->Finished()) {
			CheckBasicAttackEfects(Entity::EntityType::PLAYER, direction, stats.attack_power);
			state = State::AFTER_ATTACK;
			ChangeAnimation(direction, state);
			time_attack = SDL_GetTicks();
		}
	}
	if (state == State::AFTER_ATTACK) {
		RestTimeAfterAttack(time_attack);
	}


	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	return true;
}



bool Enemy::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEnemy", Profiler::Color::Purple);
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
	App->tex->UnLoad(ground);
	return true;
}

bool Enemy::IsPlayerNextTile() 
{
	bool ret = false;
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	std::vector<Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == Entity::EntityType::PLAYER) {
			iPoint origin = actual_tile;
			iPoint destination = (*item)->actual_tile;

			if (origin.x + 1 == destination.x && origin.y == destination.y) {
				direction = Direction::DOWN_RIGHT;
				current_animation = &IdleDownRight;
				ret = true;
			}
			if (origin.x == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::DOWN_LEFT;
				current_animation = &IdleDownLeft;
				ret = true;
			}
			if (origin.x == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::UP_RIGHT;
				current_animation = &IdleUpRight;
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y == destination.y) {
				direction = Direction::UP_LEFT;
				current_animation = &IdleUpLeft;
				ret = true;
			}
			if (origin.x + 1 == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::DOWN;
				current_animation = &IdleDown;
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::LEFT;
				current_animation = &IdleLeft;
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::UP;
				current_animation = &IdleUp;
				ret = true;
			}
			if (origin.x + 1 == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::RIGHT;
				current_animation = &IdleRight;
				ret = true;
			}
				
		}
	}

	return ret;
}

void Enemy::MovementLogic()
{
	iPoint origin = actual_tile;
	iPoint destination = App->scene->player->actual_tile;
	App->pathfinding->CreatePath(origin, destination);

	iPoint target = App->pathfinding->GetLastPath();
	if (target_position == position && !IsPlayerNextTile()) {
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
		else if (target.x < origin.x && target.y < origin.y) {
			direction = Direction::UP;
			target_position.create(position.x, position.y - App->map->data.tile_height);
			movement_count.y -= App->map->data.tile_height;
			actual_tile += {-1, -1};
		}
		else if (target.x > origin.x && target.y > origin.y) {
			direction = Direction::DOWN;
			target_position.create(position.x, position.y + App->map->data.tile_height);
			movement_count.y += App->map->data.tile_height;
			actual_tile += {1, 1};
		}
		else if (target.x < origin.x && target.y > origin.y) {
			direction = Direction::LEFT;
			target_position.create(position.x - App->map->data.tile_width, position.y);
			movement_count.x -= App->map->data.tile_width;
			actual_tile += {-1, 1};
		}
		else if (target.x > origin.x && target.y < origin.y) {
			direction = Direction::RIGHT;
			target_position.create(position.x + App->map->data.tile_width, position.y);
			movement_count.x += App->map->data.tile_width;
			actual_tile += {1, -1};
		}
		ChangeTurn(type);
	}



}

void Enemy::GetHitted(const int & damage_taken)
{
	stats.live -= damage_taken;

	if (stats.live <= 0) {
		App->entity_manager->DeleteEntity(this);
	}

}
