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

	direction = Direction::down;
	state = State::IDLE;


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

	if (state == State::IDLE) {
		if (player_input.pressing_A || player_input.pressing_S || player_input.pressing_W || player_input.pressing_D) {
			state = State::WALKING;
		}
	}
	if (state == State::WALKING && target_position == position) {
		if (player_input.pressing_A) {
			direction = Direction::left;
			target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
			movement_count.x -= (App->map->data.tile_width / 2);
			movement_count.y += (App->map->data.tile_height / 2);
		}
		else if (player_input.pressing_S) {
			direction = Direction::down;
			target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
			movement_count.x += (App->map->data.tile_width / 2);
			movement_count.y += (App->map->data.tile_height / 2);
		}
		else if (player_input.pressing_D) {
			direction = Direction::right;
			target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
			movement_count.x += (App->map->data.tile_width / 2);
			movement_count.y -= (App->map->data.tile_height / 2);
		}
		else if (player_input.pressing_W) {
			direction = Direction::up;
			target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
			movement_count.x -= (App->map->data.tile_width / 2);
			movement_count.y -= (App->map->data.tile_height / 2);
		}
		else {
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

void Player::PerformActions(float dt)
{
	if (state == State::WALKING) {
		switch (direction)
		{
		case Direction::left:
			if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
			}
			break;
		case Direction::right:
			if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
			}
			break;
		case Direction::up:
			if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
				position.x -= floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				current_animation = &GoLeft;
			}
			else {
				target_position = position;
			}
			break;
		case Direction::down:
			if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
				position.x += floor(velocity.x * dt);
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
}
