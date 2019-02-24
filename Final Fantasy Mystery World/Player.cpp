#include "Player.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Map.h"
#include <string>

Player::Player()
{
	LoadXML("player_config.xml");

	GoLeft = LoadPushbacks(node, "GoLeft");
	IdleLeft = LoadPushbacks(node, "IdleLeft");
	position.x = 100;
	position.y = 200;

	current_animation = &IdleLeft;

	direction = idle;


	iPoint p = App->render->ScreenToWorld(position.x, position.y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);
	position.x = p.x - 5;
	position.y = p.y - 6;
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
		direction = left;
		target_position.create(position.x - (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
		movement_count.x -= (App->map->data.tile_width / 2);
		movement_count.y += (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && target_position == position) {
		direction = down;
		target_position.create(position.x + (App->map->data.tile_width / 2), position.y + (App->map->data.tile_height / 2));
		movement_count.x += (App->map->data.tile_width / 2);
		movement_count.y += (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && target_position == position) {
		direction = right;
		target_position.create(position.x + (App->map->data.tile_width / 2), position.y - (App->map->data.tile_height / 2));
		movement_count.x += (App->map->data.tile_width / 2);
		movement_count.y -= (App->map->data.tile_height / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && target_position == position) {
		direction = up;
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
	case left:
		if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x -= floor(160 * dt);
			position.y += floor(80 * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = idle;
				current_animation = &IdleLeft;
			}
		}
		break;
	case right:
		if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x += floor(160 * dt);
			position.y -= floor(80 * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = idle;
				current_animation = &IdleLeft;
			}
		}
		break;
	case up:
		if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x -= floor(160 * dt);
			position.y -= floor(80 * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = idle;
				current_animation = &IdleLeft;
			}
		}
		break;
	case down:
		if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x += floor(160 * dt);
			position.y += floor(80 * dt);
			current_animation = &GoLeft;
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				target_position = position;
			}
			else {
				direction = idle;
				current_animation = &IdleLeft;
			}
		}
		break;
	case idle:
		target_position = position;
		break;
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
