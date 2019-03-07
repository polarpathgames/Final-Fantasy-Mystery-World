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
	position.x = p.x - 12;
	position.y = p.y - 11;
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

void Player::PushBack()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			switch (data.animations[i].animType) {
			case State::IDLE:
				IdleLeft.PushBack(data.animations[i].frames[j]);
				break;
			case State::WALKING:
				GoLeft.PushBack(data.animations[i].frames[j]);
				break;
			default:
				break;
			}
		}
	}
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
		if (player_input.pressing_shift) {
			if (player_input.pressing_A && !player_input.pressing_D && !player_input.pressing_S && !player_input.pressing_W) {
				direction = Direction::LEFT;
				target_position.create(position.x - App->map->data.tile_width, position.y);
				movement_count.x -= App->map->data.tile_width;
			}
			else if (player_input.pressing_D && !player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_W) {
				direction = Direction::RIGHT;
				target_position.create(position.x + App->map->data.tile_width, position.y);
				movement_count.x += App->map->data.tile_width;
			}
			else if (player_input.pressing_W && !player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D) {
				direction = Direction::UP;
				target_position.create(position.x, position.y - App->map->data.tile_height);
				movement_count.y -= App->map->data.tile_height;
			}
			else if (player_input.pressing_S && !player_input.pressing_A && !player_input.pressing_W && !player_input.pressing_D) {
				direction = Direction::DOWN;
				target_position.create(position.x, position.y + App->map->data.tile_height);
				movement_count.y += App->map->data.tile_height;
			}
		}
		else {
			if (player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D && !player_input.pressing_W) {
				direction = Direction::DOWN_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_S && !player_input.pressing_D && !player_input.pressing_A && !player_input.pressing_W) {
				direction = Direction::DOWN_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y += (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_D && !player_input.pressing_W && !player_input.pressing_A && !player_input.pressing_S) {
				direction = Direction::UP_RIGHT;
				target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x += (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
			}
			else if (player_input.pressing_W && !player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D) {
				direction = Direction::UP_LEFT;
				target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
				movement_count.x -= (App->map->data.tile_width / 2);
				movement_count.y -= (App->map->data.tile_height / 2);
			}
		}
		if (!player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D && !player_input.pressing_W) {
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
