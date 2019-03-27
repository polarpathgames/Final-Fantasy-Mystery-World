#include "Player.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "Enemy.h"
#include "j1Audio.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include <string>
#include "Brofiler/Brofiler.h"
#include "EasingSplines.h"

Player::Player(const int &x, const int &y) : DynamicEntity(x,y)
{
	//LoadXML("player_config.xml");
	LoadEntityData("entities/WarriorSpritesheet.tsx");

	//GoLeft = LoadPushbacks(node, "GoLeft");
	//IdleLeft = LoadPushbacks(node, "IdleLeft");

	type = Entity::EntityType::PLAYER;

	current_animation = &IdleDownLeft;

	SetPivot(9, 30);
	has_turn = true;
	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	movement_type = Movement_Type::InLobby;
	ground = App->tex->Load("textures/player_pos.png");
	
	velocity.x = 160;
	velocity.y = 80;
	position.x -= 5;
	position.y += 5;
	target_position = position;
	initial_position = position;
	movement_count = { 0,0 };
	actual_tile = App->map->WorldToMap(position.x + pivot.x, position.y + pivot.y);

	coll = App->collision->AddCollider(SDL_Rect{ 0,0,19,6 }, COLLIDER_PLAYER, (j1Module*)App->entity_manager);

	App->collision->AddCollider(iLine{ 100,300,419,356 }, COLLIDER_WALL, nullptr);

}

Player::~Player()
{
}

bool Player::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdatePlayer", Profiler::Color::Orange);

	ReadPlayerInput();
	
	return true;
}

bool Player::Update(float dt)
{
	BROFILER_CATEGORY("UpdatePlayer", Profiler::Color::Aqua);

	PerformActions(dt);

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x, App->map->MapToWorld(actual_tile.x, actual_tile.y).y, NULL, true);

	/*App->render->DrawLine(position.x, position.y + 25, position.x + 18, position.y + 25, 255, 255, 255);
	App->render->DrawLine(position.x, position.y + 32, position.x + 18, position.y + 32, 255, 255, 255);
	App->render->DrawLine(position.x, position.y + 25, position.x, position.y + 32, 255, 255, 255);
	App->render->DrawLine(position.x + 18, position.y + 25, position.x + 18, position.y + 32, 255, 255, 255);

	iPoint pos = App->map->MapToWorld(actual_tile.x, actual_tile.y);
	iPoint pos2 = { pos.x + 16, pos.y + 8 };
	App->render->DrawLine(pos2.x, pos2.y, pos2.x + 16, pos2.y + 8, 255, 0, 255);
	App->render->DrawLine(pos2.x - 16, pos.y + 16, pos.x + 16, pos.y + 8, 255, 0, 255);
	App->render->DrawLine(pos2.x - 16, pos.y + 16, pos.x + 16, pos.y + 24, 255, 0, 255);
	App->render->DrawLine(pos.x + 16, pos.y + 24, pos2.x + 16, pos2.y + 8, 255, 0, 255);
	*/

	coll->SetPos(position.x, position.y + 25);

	return true;
}



bool Player::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdatePlayer", Profiler::Color::Purple);
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
	App->tex->UnLoad(ground);
	return true;
}

void Player::OnCollision(Collider * c2)
{
	iPoint colliding_pos = c2->collided_point;

	if (colliding_pos.y <= coll->rect.y) { // colliding up

		if (colliding_pos.x < coll->rect.x) { // up left

		}
		else { // up right

		}
	}
	else if (colliding_pos.y >= coll->rect.y + coll->rect.h) { // colliding down

		if (colliding_pos.x < coll->rect.x) { // down left

		}
		else { // down right

		}
	}
	else if (colliding_pos.y > coll->rect.y && colliding_pos.y < coll->rect.y + coll->rect.h && colliding_pos.x <= coll->rect.x) { // colliding left

		if (colliding_pos.y < coll->rect.y + coll->rect.h / 2) { // left up

		}
		else { // left down

		}

	}
	else { // colliding right

		if (colliding_pos.y < coll->rect.y + coll->rect.h / 2) { // right up

		}
		else { // right down

		}

	}


}



void Player::ReadPlayerInput()
{
	player_input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	player_input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	player_input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	player_input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	player_input.pressing_I = App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN;
	player_input.pressing_J = App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN;
	player_input.pressing_K = App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN;
	player_input.pressing_L = App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN;
	player_input.pressing_G = App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN;
	player_input.pressing_shift = App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT;

	if (state == State::IDLE) {
		if (player_input.pressing_A || player_input.pressing_S || player_input.pressing_W || player_input.pressing_D) {
			state = State::WALKING;
		}
		else if (player_input.pressing_G) {
			state = State::BEFORE_ATTACK;
		}
		else if (movement_type == Movement_Type::InQuest){
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
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
	if (state == State::BEFORE_ATTACK) {
		ReadAttack();
	}
}

void Player::ReadPlayerMovementInQuest()
{
	if (target_position == position) {
		bool is_movement_acepted = false;
		if (MultipleButtons(&player_input)) {
			if (player_input.pressing_A && player_input.pressing_shift) {
				direction = Direction::LEFT;
				if (NextTileFree(direction)) {
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
				direction = Direction::RIGHT;
				if (NextTileFree(direction)) {
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
				direction = Direction::UP;
				if (NextTileFree(direction)) {
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
				direction = Direction::DOWN;
				if (NextTileFree(direction)) {
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
				direction = Direction::DOWN_LEFT;
				if (NextTileFree(direction)) {
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
				direction = Direction::DOWN_RIGHT;
				if (NextTileFree(direction)) {
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
				direction = Direction::UP_RIGHT;
				if (NextTileFree(direction)) {
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
				direction = Direction::UP_LEFT;
				if (NextTileFree(direction)) {
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
			ChangeAnimation(direction, state);
		}
		else {
			if (is_movement_acepted) {
				ChangeTurn(type);
			}
			else {
				ChangeAnimation(direction, state);
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
		ChangeAnimation(direction, state);
	}
}

void Player::ReadAttack()
{
	if (player_input.pressing_G) {
		type_attack = Attacks::BASIC;
		state = State::ATTACKING;
		switch (direction) {
		case Direction::DOWN_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 200, EASE);
			break;
		case Direction::UP_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 200, EASE);
			break;
		case Direction::DOWN_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 200, EASE);
			break;
		case Direction::UP_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 200, EASE);
			break;
		}
		ChangeAnimation(direction, state, type_attack);
	}
}
	
	
void Player::PerformActions(float dt)
{
	if (state == State::IDLE) {
		ChangeDirection();
	}
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
			LOG("There is no movement type...");
			break;
		}		
	}
	if (state == State::ATTACKING) {
		switch (type_attack) {
		case Attacks::BASIC:
			BasicAttack();
			break;
		default:
			LOG("There is no attack type...");
			break;
		}
	}
	if (state == State::AFTER_ATTACK) {
		RestTimeAfterAttack(time_attack);
	}
}

void Player::BasicAttack()
{

	if (current_animation->Finished()) {
		switch (direction) {
		case Direction::DOWN_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::DOWN_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		}
		CheckAttackEfects(Entity::EntityType::ENEMY, direction, stats.attack_power);
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}


}

void Player::PerformMovementInLobby(float dt)
{
	switch (direction)
	{
	case Direction::DOWN_LEFT:
		position.x -= floor(velocity.x * dt);
		position.y += floor(velocity.y * dt);
		current_animation = &GoDownLeft;
		break;
	case Direction::UP_RIGHT:
		position.x += floor(velocity.x * dt);
		position.y -= floor(velocity.y * dt);
		current_animation = &GoUpRight;
		break;
	case Direction::UP_LEFT:
		position.x -= floor(velocity.x * dt);
		position.y -= floor(velocity.y * dt);
		current_animation = &GoUpLeft;
		break;
	case Direction::DOWN_RIGHT:
		position.x += floor(velocity.x * dt);
		position.y += floor(velocity.y * dt);
		current_animation = &GoDownRight;
		break;
	case Direction::RIGHT:
		position.x += floor(180 * dt);
		current_animation = &GoRight;
		break;
	case Direction::LEFT:
		position.x -= floor(180 * dt);
		current_animation = &GoLeft;
		break;
	case Direction::UP:
		position.y -= floor(180 * dt);
		current_animation = &GoUp;
		break;
	case Direction::DOWN:
		position.y += floor(180 * dt);
		current_animation = &GoDown;
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
			current_animation = &GoDownLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleDownLeft;
		}
		break;
	case Direction::UP_RIGHT:
		if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoUpRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleUpRight;
		}
		break;
	case Direction::UP_LEFT:
		if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoUpLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleUpLeft;
		}
		break;
	case Direction::DOWN_RIGHT:
		if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &GoDownRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleDownRight;
		}
		break;
	case Direction::LEFT:
		if (position.x >= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			current_animation = &GoLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleLeft;
		}
		break;
	case Direction::RIGHT:
		if (position.x <= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			current_animation = &GoRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleRight;
		}
		break;
	case Direction::UP:
		if (position.x == initial_position.x + movement_count.x && position.y >= initial_position.y + movement_count.y) {
			position.y -= floor(velocity.y * dt);
			current_animation = &GoUp;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleUp;
		}
		break;
	case Direction::DOWN:
		if (position.x == initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.y += floor(velocity.y * dt);
			current_animation = &GoDown;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &IdleDown;
		}
		break;
	default:
		break;
	}
}

void Player::ChangeDirection()
{
	if (player_input.pressing_shift) {
		if (player_input.pressing_I) {
			direction = Direction::UP;
			current_animation = &IdleUp;
		}
		if (player_input.pressing_J) {
			direction = Direction::LEFT;
			current_animation = &IdleLeft;
		}
		if (player_input.pressing_K) {
			direction = Direction::DOWN;
			current_animation = &IdleDown;
		}
		if (player_input.pressing_L) {
			direction = Direction::RIGHT;
			current_animation = &IdleRight;
		}
	}
	else if (!player_input.pressing_shift) {
		if (player_input.pressing_I) {
			direction = Direction::UP_LEFT;
			current_animation = &IdleUpLeft;
		}
		if (player_input.pressing_J) {
			direction = Direction::DOWN_LEFT;
			current_animation = &IdleDownLeft;
		}
		if (player_input.pressing_K) {
			direction = Direction::DOWN_RIGHT;
			current_animation = &IdleDownRight;
		}
		if (player_input.pressing_L) {
			direction = Direction::UP_RIGHT;
			current_animation = &IdleUpRight;
		}
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





