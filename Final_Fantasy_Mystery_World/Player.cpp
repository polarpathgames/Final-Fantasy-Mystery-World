#include "Player.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Map.h"
#include <string>

Player::Player() : DynamicEntity()
{
	//LoadXML("player_config.xml");
	LoadEntityData("entities/Animist.tsx");

	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");
	position.x = 100;
	position.y = 200;

	current_animation = &IdleLeft;

	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	movement_type = Movement_Type::InQuest;

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
		if (MultipleButtons(&player_input)) {
			if (player_input.pressing_A && player_input.pressing_shift) {
				direction = Direction::LEFT;
				target_position.create(position.x - App->map->data.tile_width, position.y);
				movement_count.x -= App->map->data.tile_width;
			}
			else if (player_input.pressing_D && player_input.pressing_shift) {
				direction = Direction::RIGHT;
				target_position.create(position.x + App->map->data.tile_width, position.y);
				movement_count.x += App->map->data.tile_width;
			}
			else if (player_input.pressing_W && player_input.pressing_shift) {
				direction = Direction::UP;
				target_position.create(position.x, position.y - App->map->data.tile_height);
				movement_count.y -= App->map->data.tile_height;
			}
			else if (player_input.pressing_S && player_input.pressing_shift) {
				direction = Direction::DOWN;
				target_position.create(position.x, position.y + App->map->data.tile_height);
				movement_count.y += App->map->data.tile_height;
			}
			if (player_input.pressing_A && !player_input.pressing_shift) {
				direction = Direction::DOWN_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_S && !player_input.pressing_shift) {
				direction = Direction::DOWN_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_D && !player_input.pressing_shift) {
				direction = Direction::UP_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_W && !player_input.pressing_shift) {
				direction = Direction::UP_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
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
			ChangeTurn(type);
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

const bool Player::CheckEnemyNextTile(const Direction * dir)
{
	bool ret = true;
	std::list<Entity*> entities = App->entity_manager->GetEntities();
	std::list<Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
			iPoint origin = App->map->WorldToMap(position.x, position.y);
			iPoint destination = App->map->WorldToMap((*item)->position.x, (*item)->position.y);
			
			switch (*dir) {
			case Direction::DOWN:
				origin += {1, 1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::UP:
				origin -= {1, 1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::LEFT:

				break;
			case Direction::RIGHT:

				break;
			case Direction::DOWN_LEFT:

				break;
			case Direction::DOWN_RIGHT:

				break;
			case Direction::UP_LEFT:

				break;
			case Direction::UP_RIGHT:

				break;
			}
		}
	}

	return ret;
}



