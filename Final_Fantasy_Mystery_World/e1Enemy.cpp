#include "e1Enemy.h"
#include "m1Input.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Audio.h"
#include "u1UI_Element.h"
#include "e1Drop.h"
#include "m1GUI.h"
#include "m1EntityManager.h"
#include "m1Fonts.h"
#include "p2Rooms.h"
#include "m1Map.h"
#include <vector>
#include <string>
#include "m1Pathfinding.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1Window.h"
#include "Brofiler/Brofiler.h"
#include <map>
#include <stdlib.h> 


e1Enemy::e1Enemy(const int &x, const int &y) : e1DynamicEntity(x,y)
{
	

	type = e1Entity::EntityType::ENEMY;
	ground = App->tex->Load("assets/sprites/enemy_pos.png");
	current_animation = &IdleDownLeft;

	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	has_turn = false;
	velocity.x = 160;
	velocity.y = 80;
	
	original_position = position;
	movement_count = { 0,0 };
	actual_tile = App->map->WorldToMap(position.x, position.y);

	// THIS ALWAYS LAST
	
	
}

e1Enemy::~e1Enemy()
{
}

void e1Enemy::InitStats()
{
	for (std::list<Property<int>*>::iterator item = general_properties.properties.begin(); item != general_properties.properties.end(); item++) {
		if (strcmp((*item)->GetName(), "experience") == 0) {
			stats.experience = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "attack_power") == 0) {
			stats.attack_power = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "live") == 0) {
			stats.live = (*item)->GetValue();
		}
	}
}

bool e1Enemy::Load(pugi::xml_node &)
{
	return true;
}

bool e1Enemy::Save(pugi::xml_node &) const
{
	return true;
}

bool e1Enemy::CleanUp()
{
	App->tex->UnLoad(ground);
	ground = nullptr;
	return true;
}

bool e1Enemy::IsAnotherEnemyNextTile()
{
	BROFILER_CATEGORY("IsAnotherEnemyNextTile", Profiler::Color::SeaGreen);
	bool ret = false;
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			iPoint origin = actual_tile;
			iPoint destination = (*item)->actual_tile;

			if (origin.x + 1 == destination.x && origin.y == destination.y) {
				direction = Direction::DOWN_RIGHT;
				current_animation = &IdleDownRight;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::DOWN_LEFT;
				current_animation = &IdleDownLeft;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::UP_RIGHT;
				current_animation = &IdleUpRight;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y == destination.y) {
				direction = Direction::UP_LEFT;
				current_animation = &IdleUpLeft;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x + 1 == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::DOWN;
				current_animation = &IdleDown;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y + 1 == destination.y) {
				direction = Direction::LEFT;
				current_animation = &IdleLeft;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x - 1 == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::UP;
				current_animation = &IdleUp;
				next_enemy_pos.push_back(destination);
				ret = true;
			}
			if (origin.x + 1 == destination.x && origin.y - 1 == destination.y) {
				direction = Direction::RIGHT;
				current_animation = &IdleRight;
				next_enemy_pos.push_back(destination);
				ret = true;
			}

		}
	}

	return ret;
}

bool e1Enemy::IsPlayerNextTile()
{
	BROFILER_CATEGORY("IsAnotherPlayerNextTile", Profiler::Color::SeaGreen);
	bool ret = false;
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::PLAYER) {
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

void e1Enemy::MovementLogic()
{
	BROFILER_CATEGORY("MovementLogic Enemy", Profiler::Color::SeaGreen);
	iPoint origin = actual_tile;
	iPoint destination = App->scene->player->actual_tile;

	if (!IsAnotherEnemyNextTile())
		App->pathfinding->CreatePath(origin, destination);
	else {
		App->pathfinding->RecalculatePath(origin, destination, next_enemy_pos);
		next_enemy_pos.clear();
	}
		
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

void e1Enemy::PerformMovement(float dt)
{
	BROFILER_CATEGORY("PerformMovement Enemy", Profiler::Color::SeaGreen);
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

void e1Enemy::GetHitted(const int & damage_taken)
{
	stats.live -= damage_taken;
	//(int)(camera.x * speed) + x * scale;
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(damage_taken).data(), App->gui->screen,RED, FontType::PMIX24);
	if (stats.live <= 0 || App->scene->player->god_mode) {
		rand_num = rand() % 3;
		if(rand_num  == 0)
			Drop();
		App->audio->PlayFx(App->scene->fx_kill_enemy);
		App->scene->player->UpdateExperience(stats.experience);
		App->map->quest_rooms->AddEntityToNotRepeat(original_position);
		to_delete = true;
		state = State::DEATH;
		current_animation = &DeathDownLeft;
	}
}

void e1Enemy::Drop()
{
	int drop_gold = App->random.Generate(20, 50);
	e1Drop* drop = (e1Drop*)App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, actual_tile.x, actual_tile.y, "gold");
	drop->SetGold(drop_gold);
}
