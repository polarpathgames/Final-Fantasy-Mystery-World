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


	iPoint p = App->render->ScreenToWorld(position.x, position.y);
	p = App->map->WorldToMap(p.x, p.y);
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
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && target_position == position) {
		direction = Direction::left;
		target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
		movement_count.x -= (App->map->data.tile_width / 2);
		movement_count.y += (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && target_position == position) {
		direction = Direction::down;
		target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
		movement_count.x += (App->map->data.tile_width / 2);
		movement_count.y += (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && target_position == position) {
		direction = Direction::right;
		target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
		movement_count.x += (App->map->data.tile_width / 2);
		movement_count.y -= (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && target_position == position) {
		direction = Direction::up;
		target_position.create(position.x - (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
		movement_count.x -= (App->map->data.tile_width / 2);
		movement_count.y -= (App->map->data.tile_height / 2);
	}

	return true;
}

bool Player::Update(float dt)
{
	switch  (direction)
	{
	case Direction::left:
		if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = Direction::down;
				current_animation = &IdleLeft;
			}
		}
		break;
	case Direction::right:
		if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = Direction::left;
				current_animation = &IdleLeft;
			}
		}
		break;
	case Direction::up:
		if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = Direction::left;
				current_animation = &IdleLeft;
			}
		}
		break;
	case Direction::down:
		if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = Direction::left;
				current_animation = &IdleLeft;
			}
		}
		break;
	/*case Direction::idle:
		target_position = position;
		break;*/
	default:
		break;
	}

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
