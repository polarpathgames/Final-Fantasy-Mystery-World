#include "Player.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Map.h"
#include <string>

Player::Player(const int &x, const int &y) : DynamicEntity(x,y)
{
	//LoadXML("player_config.xml");
	LoadEntityData("entities/Player.tsx");

	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");

	type = Entity::EntityType::PLAYER;

	current_animation = &IdleLeft;

	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	movement_type = Movement_Type::InQuest;

	velocity.x = 160;
	velocity.y = 80;
	target_position = position;
	initial_position = position;
	movement_count = { 0,0 };
	actual_tile = App->map->WorldToMap(position.x, position.y);
}

Player::~Player()
{
}

bool Player::PreUpdate()
{
	ReadPlayerInput();
	
	return true;
}

bool Player::Update(float dt)
{
	PerformActions(dt);

	return true;
}



bool Player::PostUpdate()
{

	return true;
}

bool Player::Load(pugi::xml_node &)
{
	return true;
}

bool Player::Save(pugi::xml_node &) const
{
	return true;
}

bool Player::CleanUp()
{
	return true;
}



void Player::ReadPlayerInput()
{
	player_input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	player_input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	player_input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	player_input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	player_input.pressing_shift = App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT;

	if (state == State::IDLE) {
		if (player_input.pressing_A || player_input.pressing_S || player_input.pressing_W || player_input.pressing_D) {
			state = State::WALKING;
		}
	}
	if (state == State::WALKING) {
		switch (movement_type) {
		case Movement_Type::InQuest: {
			ReadPlayerMovementInQuest();
			break;
		}
		case Movement_Type::InLobby: {
			ReadPlayerMovementInLobby();
			break;
		}
		default:
			break;
		}
	}
}

void Player::ReadPlayerMovementInQuest()
{
	if (target_position == position) {
		bool is_movement_acepted = false;
		if (MultipleButtons(&player_input)) {
			if (player_input.pressing_A && player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::LEFT)) {
					direction = Direction::LEFT;
					target_position.create(position.x - App->map->data.tile_width, position.y);
					movement_count.x -= App->map->data.tile_width;
					actual_tile += {-1, 1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_D && player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::RIGHT)) {
					direction = Direction::RIGHT;
					target_position.create(position.x + App->map->data.tile_width, position.y);
					movement_count.x += App->map->data.tile_width;
					actual_tile += {1, -1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_W && player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::UP)) {
					direction = Direction::UP;
					target_position.create(position.x, position.y - App->map->data.tile_height);
					movement_count.y -= App->map->data.tile_height;
					actual_tile += {-1, -1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_S && player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::DOWN)) {
					direction = Direction::DOWN;
					target_position.create(position.x, position.y + App->map->data.tile_height);
					movement_count.y += App->map->data.tile_height;
					actual_tile += {1, 1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			if (player_input.pressing_A && !player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::DOWN_LEFT)) {
					direction = Direction::DOWN_LEFT;
					target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
					movement_count.x -= (App->map->data.tile_width / 2);
					movement_count.y += (App->map->data.tile_height / 2);
					actual_tile += {0, 1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_S && !player_input.pressing_shift) {

				if (!CheckEnemyNextTile(Direction::DOWN_RIGHT)) {
					direction = Direction::DOWN_RIGHT;
					target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
					movement_count.x += (App->map->data.tile_width / 2);
					movement_count.y += (App->map->data.tile_height / 2);
					actual_tile += {1, 0};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_D && !player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::UP_RIGHT)) {
					direction = Direction::UP_RIGHT;
					target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
					movement_count.x += (App->map->data.tile_width / 2);
					movement_count.y -= (App->map->data.tile_height / 2);
					actual_tile += {0, -1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			else if (player_input.pressing_W && !player_input.pressing_shift) {
				if (!CheckEnemyNextTile(Direction::UP_LEFT)) {
					direction = Direction::UP_LEFT;
					target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
					movement_count.x -= (App->map->data.tile_width / 2);
					movement_count.y -= (App->map->data.tile_height / 2);
					actual_tile += {-1, 0};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			
			
		}
		if (!MultipleButtons(&player_input)) {
			state = State::IDLE;
			target_position = position;
			if (current_animation == &GoLeft)
				current_animation = &IdleLeft;
			if (current_animation == &GoRight)
				current_animation = &IdleRight;
			if (current_animation == &GoDown)
				current_animation = &IdleDown;
			if (current_animation == &GoUp)
				current_animation = &IdleUp;
		}
		else {
			if (is_movement_acepted) {
				ChangeTurn(type);
			}
		}
	}
}

void Player::ReadPlayerMovementInLobby()
{
	if (player_input.pressing_A) {
		direction = Direction::LEFT;
	}
	if (player_input.pressing_S) {
		direction = Direction::DOWN;
	}
	if (player_input.pressing_D) {
		direction = Direction::RIGHT;
	}
	if (player_input.pressing_W) {
		direction = Direction::UP;
	}
	if (player_input.pressing_A && player_input.pressing_W) {
		direction = Direction::UP_LEFT;
	}
	if (player_input.pressing_A && player_input.pressing_S) {
		direction = Direction::DOWN_LEFT;
	}
	if (player_input.pressing_D && player_input.pressing_W) {
		direction = Direction::UP_RIGHT;
	}
	if (player_input.pressing_D && player_input.pressing_S) {
		direction = Direction::DOWN_RIGHT;
	}
	if (!player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D && !player_input.pressing_W) {
		state = State::IDLE;
		if (current_animation == &GoLeft)
			current_animation = &IdleLeft;
		if (current_animation == &GoRight)
			current_animation = &IdleRight;
		if (current_animation == &GoDown)
			current_animation = &IdleDown;
		if (current_animation == &GoUp)
			current_animation = &IdleUp;
	}
}
	
	
void Player::PerformActions(float dt)
{
	if (state == State::WALKING) {
		switch (movement_type) {
		case Movement_Type::InQuest: {
			PerformMovementInQuest(dt);
		break;
		}
		case Movement_Type::InLobby: {
			PerformMovementInLobby(dt);
			break;
		}
		default:
			break;
		}		
	}
}

void Player::PerformMovementInLobby(float dt)
{
	switch (direction)
	{
	case Direction::DOWN_LEFT:
		position.x -= floor(velocity.x * dt);
		position.y += floor(velocity.y * dt);
		current_animation = &GoLeft;
		break;
	case Direction::UP_RIGHT:
		position.x += floor(velocity.x * dt);
		position.y -= floor(velocity.y * dt);
		current_animation = &GoLeft;
		break;
	case Direction::UP_LEFT:
		position.x -= floor(velocity.x * dt);
		position.y -= floor(velocity.y * dt);
		current_animation = &GoLeft;
		break;
	case Direction::DOWN_RIGHT:
		position.x += floor(velocity.x * dt);
		position.y += floor(velocity.y * dt);
		current_animation = &GoLeft;
		break;
	case Direction::RIGHT:
		position.x += floor(180 * dt);
		current_animation = &GoLeft;
		break;
	case Direction::LEFT:
		position.x -= floor(180 * dt);
		current_animation = &GoLeft;
		break;
	case Direction::UP:
		position.y -= floor(180 * dt);
		current_animation = &GoLeft;
		break;
	case Direction::DOWN:
		position.y += floor(180 * dt);
		current_animation = &GoLeft;
		break;
	default:
		break;
	}
}

void Player::PerformMovementInQuest(float dt)
{
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
		}
		break;
	case Direction::LEFT:
		if (position.x >= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			current_animation = &GoLeft;
		}
		else {
			target_position = position;
		}
		break;
	case Direction::RIGHT:
		if (position.x <= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			current_animation = &GoLeft;
		}
		else {
			target_position = position;
		}
		break;
	case Direction::UP:
		if (position.x == initial_position.x + movement_count.x && position.y >= initial_position.y + movement_count.y) {
			position.y -= floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			target_position = position;
		}
		break;
	case Direction::DOWN:
		if (position.x == initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.y += floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			target_position = position;
		}
		break;
	default:
		break;
	}
}

const bool Player::MultipleButtons(const Input * input)
{
	bool ret;

	if (input->pressing_A && !input->pressing_D && !input->pressing_S && !input->pressing_W)
		ret = true;
	else if (input->pressing_D && !input->pressing_A && !input->pressing_S && !input->pressing_W)
		ret = true;
	else if (input->pressing_S && !input->pressing_A && !input->pressing_D && !input->pressing_W)
		ret = true;
	else if (input->pressing_W && !input->pressing_A && !input->pressing_D && !input->pressing_S)
		ret = true;
	else
		ret = false;

	return ret;
}

const bool Player::CheckEnemyNextTile(const Direction & dir)
{
	bool ret = false;
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	std::vector<Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
			iPoint origin = actual_tile;
			iPoint destination = App->map->WorldToMap((*item)->position.x, (*item)->position.y);
			
			switch (dir) {
			case Direction::DOWN:
				origin += {1, 1};
				if (destination == origin)
					ret = true;
				break;
			case Direction::UP:
				origin += {-1, -1};
				if (destination == origin)
					ret = true;
				break;
			case Direction::LEFT:
				origin += {-1, 1};
				if (destination == origin)
					ret = true;
				break;
			case Direction::RIGHT:
				origin += {1, -1};
				if (destination == origin)
					ret = true;
				break;
			case Direction::DOWN_LEFT:
				origin += {0, 1};
				if (destination == origin)
					ret = true;
				break;
			case Direction::DOWN_RIGHT:
				origin += {1, 0};
				if (destination == origin)
					ret = true;
				break;
			case Direction::UP_LEFT:
				origin += {-1, 0};
				if (destination == origin)
					ret = true;
				break;
			case Direction::UP_RIGHT:
				origin += {0, -1};
				if (destination == origin)
					ret = true;
				break;
			}
		}
	}

	return ret;
}



