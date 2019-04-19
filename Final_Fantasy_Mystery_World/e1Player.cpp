#include "e1Player.h"
#include "m1Input.h"
#include "App.h"
#include "m1Render.h"
#include "p2Log.h"
#include "m1Cutscene.h"
#include "App.h"
#include "m1Textures.h"
#include "e1Enemy.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "e1Warrior.h"
#include "e1Archer.h"
#include "e1Mage.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1GUI.h"
#include "m1Pathfinding.h"
#include "m1Collisions.h"
#include "m1Scene.h"
#include "m1FadeToBlack.h"
#include "m1Scene.h"
#include "u1Label.h"
#include "u1Button.h"
#include "u1Bar.h"
#include <string>
#include "u1UI_Element.h"
#include "Brofiler/Brofiler.h"
#include "m1EasingSplines.h"
#include "m1MainMenu.h"
#include "m1ParticleManager.h"

e1Player::e1Player(const int &x, const int &y) : e1DynamicEntity(x,y)
{
	direction = Direction::DOWN_LEFT;
	state = State::IDLE;
	current_animation = &IdleDownLeft;
}

e1Player::~e1Player()
{
}

bool e1Player::PreUpdate()
{
	if (!block_controls)
		ReadPlayerInput();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-15 }, { 8,0,2,2 }, RANDOM, { 20,20 }, { 10,5 }, { 0,0 }, P_UP, 200, 4, { 0,-2 });

	return true;
}

bool e1Player::Update(float dt)
{
	PerformActions(dt);

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	if (coll != nullptr)
		coll->SetPos(position.x, position.y + 25);


	return true;
}

bool e1Player::Load(pugi::xml_node &)
{
	return true;
}

bool e1Player::Save(pugi::xml_node &) const
{
	return true;
}

bool e1Player::CleanUp()
{
	App->tex->UnLoad(ground);
	return true;
}

void e1Player::OnCollision(Collider * c2)
{
}

void e1Player::OnCollisionEnter(Collider * c2)
{
	if (c2->type == COLLIDER_SHOP) {
		if (App->map->actual_map == Maps::LOBBY)
			App->fade_to_black->FadeToBlack(Maps::SHOP);
		else
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
	if (c2->type == COLLIDER_HOME) {
		if (App->map->actual_map == Maps::LOBBY)
			App->fade_to_black->FadeToBlack(Maps::HOME);
		else
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
	if (c2->type == COLLIDER_MENU_QUEST) {
		App->scene->CreateGoToQuestMenu();
		App->scene->SetMenuState(StatesMenu::GO_TO_QUEST_MENU);
	}
	if (c2->type == COLLIDER_CUTSCENE_BRIDGE) {
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneBlockPass.xml");
		App->scene->ShowHUD(false);
	}
}

void e1Player::OnCollisionExit(Collider * c2)
{
	if (c2->type == COLLIDER_CUTSCENE_BRIDGE) {
		App->scene->ShowHUD(true);
	}
}

void e1Player::CheckLobbyCollision(const float & dt, const Direction & dir)
{
	switch (direction) {
	case Direction::RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt))})) {
			current_animation = &GoDownRight;
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			current_animation = &GoUpRight;
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::DOWN:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			current_animation = &GoDownLeft;
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			current_animation = &GoDownRight;
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::LEFT:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			current_animation = &GoUpLeft;
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })){
			current_animation = &GoDownLeft;
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::UP:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			current_animation = &GoUpLeft;
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })){
			current_animation = &GoUpRight;
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	default:
		LOG("No direction found");
		break;
	}



}

void e1Player::CenterPlayerInTile()
{
	type = e1Entity::EntityType::PLAYER;

	velocity.x = 160;
	velocity.y = 80;
	has_turn = true;
	
	if (state == State::MENU) {
		direction = Direction::DOWN_LEFT;
		state = State::IDLE;
		current_animation = &IdleDownLeft;
		DeathDownLeft.Reset();
		DeathDownRight.Reset();
		DeathUpRight.Reset();
		DeathUpLeft.Reset();
		DeathDown.Reset();
		DeathRight.Reset();
		DeathUp.Reset();
		DeathLeft.Reset();
	}

	if (App->map->data.properties.GetValue("movement") == 1)
		movement_type = Movement_Type::InLobby;
	else
		movement_type = Movement_Type::InQuest;
	
	actual_tile = App->map->WorldToMap(position.x, position.y);
	coll = App->collision->AddCollider(SDL_Rect{ 0,0,19,6 }, COLLIDER_PLAYER, (m1Module*)App->entity_manager);
	movement_count = { 0,0 };
	// THIS ALWAYS LAST
	if (App->scene->player_type == PlayerType::WARRIOR) {
		SetPivot(14, 27);
		position.x += 3;
		position.y -= 19;
	}
	else {
		SetPivot(10, 30);
		position.x += 8;
		position.y -= 22;
	}

	target_position = position;
	initial_position = position;
}



void e1Player::ReadPlayerInput()
{
	if (movement_type == Movement_Type::InLobby) {
		LobbyControls();
	}
	else if (movement_type == Movement_Type::InQuest) {
		QuestControls();
	}

	if (state == State::IDLE) {
		if (player_input.pressing_A || player_input.pressing_S || player_input.pressing_W || player_input.pressing_D) {
			state = State::WALKING;
		}
		else if (player_input.pressing_G || player_input.pressing_F) {
			state = State::BEFORE_ATTACK;
		}
		else if (player_input.pressing_H) {
			state = State::BEFORE_FLASH;
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
	if (state == State::BEFORE_FLASH) {
		LookFlash();
	}
}

void e1Player::ReadPlayerMovementInQuest()
{
	if (target_position == position) {
		bool is_movement_acepted = false;
		if (MultipleButtons(&player_input)) {
			if (player_input.pressing_A && player_input.pressing_shift) {
				direction = Direction::LEFT;
				if (NextTileFree(direction) && App->map->IsWalkable({actual_tile.x - 1, actual_tile.y + 1},false)) {
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
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y - 1 },false)) {
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
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x - 1, actual_tile.y - 1 },false)) {
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
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y + 1 },false)) {
					target_position.create(position.x, position.y + App->map->data.tile_height);
					movement_count.y += App->map->data.tile_height;
					actual_tile += {1, 1};
					is_movement_acepted = true;
				}
				else {
					state = State::IDLE;
				}
			}
			if (player_input.pressing_S && !player_input.pressing_shift) {
				direction = Direction::DOWN_LEFT;
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x, actual_tile.y + 1 },false)) {
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
			else if (player_input.pressing_D && !player_input.pressing_shift) {
				direction = Direction::DOWN_RIGHT;
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y},false)) {
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
			else if (player_input.pressing_W && !player_input.pressing_shift) {
				direction = Direction::UP_RIGHT;
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x, actual_tile.y - 1 },false)) {
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
			else if (player_input.pressing_A && !player_input.pressing_shift) {
				direction = Direction::UP_LEFT;
				if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x - 1, actual_tile.y},false)) {
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

void e1Player::ReadPlayerMovementInLobby()
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
	if (player_input.pressing_W && player_input.pressing_A) {
		direction = Direction::UP_LEFT;
	}
	if (player_input.pressing_S && player_input.pressing_A) {
		direction = Direction::DOWN_LEFT;
	}
	if (player_input.pressing_W && player_input.pressing_D) {
		direction = Direction::UP_RIGHT;
	}
	if (player_input.pressing_S && player_input.pressing_D) {
		direction = Direction::DOWN_RIGHT;
	}
	if (!player_input.pressing_A && !player_input.pressing_S && !player_input.pressing_D && !player_input.pressing_W) {
		state = State::IDLE;
		ChangeAnimation(direction, state);
	}
}

void e1Player::ReadAttack()
{
	if (player_input.pressing_G) {
		PrepareBasicAttack();
		App->audio->PlayFx(App->scene->fx_attack);
		return;
	}
	if (player_input.pressing_F) {
		PrepareSpecialAttack1();
		return;
	}
}

void e1Player::InitStats()
{
}

void e1Player::PrepareBasicAttack()
{
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
	case Direction::UP:
		App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3, 200, EASE);
		break;
	case Direction::DOWN:
		App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3, 200, EASE);
		break;
	case Direction::RIGHT:
		App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3, 200, EASE);
		break;
	case Direction::LEFT:
		App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3, 200, EASE);
		break;
	}
	ChangeAnimation(direction, state, type_attack);
}


	
	
void e1Player::PerformActions(float dt)
{
	if (player_input.pressing_V && App->scene->GetMenuState() != StatesMenu::OPTIONS_MENU && App->scene->GetMenuState() != StatesMenu::CONTROLS_MENU && App->scene->GetMenuState() != StatesMenu::PAUSE_MENU){
		App->audio->PlayFx(App->scene->fx_ability_menu);
		(has_skills) ? DestroySkills() : CreateSkills();
	}

	if (state == State::IDLE) {
		ChangeDirection();
	}
	if (state == State::WALKING) {
		switch (movement_type) {
		case Movement_Type::InQuest:
			PerformMovementInQuest(dt);
			break;
		case Movement_Type::InLobby:
			PerformMovementInLobby(dt);
			break;
		default:
			LOG("There is no movement type...");
			break;
		}
	}
	if (state == State::DEATH) {
		Death();
	}
	if (state == State::ATTACKING) {
		switch (type_attack) {
		case Attacks::BASIC:
			BasicAttack();
			break;
		case Attacks::SPECIAL_1:
			SpecialAttack1();
			break;
		default:
			LOG("There is no attack type...");
			break;
		}
	}
	if (state == State::AFTER_ATTACK) {
		RestTimeAfterAttack(time_attack);
	}
	if (state == State::FLASHING) {
		Flashing();
	}
	if (state == State::AFTER_FLASH) {
		RestTimeAfterFlash();
	}
}

void e1Player::BasicAttack()
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
		case Direction::UP:
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::DOWN:
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		case Direction::LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		}
		CheckBasicAttackEfects(e1Entity::EntityType::ENEMY, direction, stats.attack_power);
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}


}

void e1Player::PerformMovementInLobby(float dt)
{
	switch (direction)
	{
	case Direction::DOWN_LEFT:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &GoDownLeft;
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::UP_RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoUpRight;
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::UP_LEFT:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &GoUpLeft;
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::DOWN_RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &GoDownRight;
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(180 * dt) + pivot.x), position.y + pivot.y })) {
			position.x += floor(velocity.x * dt);
			current_animation = &GoRight;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}
		break;
	case Direction::LEFT:
		if (App->map->IsWalkable({(int)(position.x - floor(180 * dt) + pivot.x), position.y + pivot.y })) {
			position.x -= floor(velocity.x * dt);
			current_animation = &GoLeft;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}
		break;
	case Direction::UP:
		if (App->map->IsWalkable({ (position.x + pivot.x), (int)(position.y + pivot.y - floor(180 * dt)) })) {
			position.y -= floor(velocity.y * 2 * dt);
			current_animation = &GoUp;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}

		break;
	case Direction::DOWN:
		if (App->map->IsWalkable({ (position.x + pivot.x), (int)(position.y + pivot.y + floor(180 * dt)) })) {
			position.y += floor(velocity.y * 2 * dt);
			current_animation = &GoDown;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}
		break;
	default:
		break;
	}
}

void e1Player::PerformMovementInQuest(float dt)
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

void e1Player::ChangeDirection()
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
		if (player_input.pressing_J) {
			direction = Direction::UP_LEFT;
			current_animation = &IdleUpLeft;
		}
		if (player_input.pressing_K) {
			direction = Direction::DOWN_LEFT;
			current_animation = &IdleDownLeft;
		}
		if (player_input.pressing_L) {
			direction = Direction::DOWN_RIGHT;
			current_animation = &IdleDownRight;
		}
		if (player_input.pressing_I) {
			direction = Direction::UP_RIGHT;
			current_animation = &IdleUpRight;
		}
	}




}

const bool e1Player::MultipleButtons(const Input * input)
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

void e1Player::GetHitted(const int & damage_taken)
{

	App->input->ControllerVibration(0.1F, 100);

	if(!god_mode)
		ReduceLives(damage_taken);

	if (stats.live <= 0) {
		state = State::DEATH;
		ChangeAnimation(direction, state);
		death_time = SDL_GetTicks();
	}

	


}

void e1Player::Death()
{
	if (current_animation->Finished() && death_time <= SDL_GetTicks() - 1000) {
		App->map->CleanUp();
		App->entity_manager->DeleteEntitiesNoPlayer();
		App->gui->DeleteUIElement((u1GUI*)App->scene->bg_hud);
		App->scene->CreateGameOver();
		App->scene->SetMenuState(StatesMenu::DIE_MENU);
		state = State::MENU;
		stats.live = stats.max_lives;
		stats.mana = stats.max_mana;
	}
}

void e1Player::DestroySkills()
{
	App->gui->DeleteUIElement(upper_button);
	App->gui->DeleteUIElement(right_button);
	App->gui->DeleteUIElement(left_button);

	has_skills = false;
}

bool e1Player::BlockControls(bool to_block)
{
	if (to_block) {
		player_input.Reset();
		//state = State::IDLE;
		ChangeAnimation(direction, state);
	}
	return block_controls = to_block;
}

void e1Player::LobbyControls()
{
	player_input.pressing_A = App->input->GetKey(App->input->keyboard_buttons.buttons_code.LEFT) == KEY_REPEAT || App->input->CheckAxisStates(Axis::AXIS_LEFT);
	player_input.pressing_S = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DOWN) == KEY_REPEAT || App->input->CheckAxisStates(Axis::AXIS_DOWN);
	player_input.pressing_W = App->input->GetKey(App->input->keyboard_buttons.buttons_code.UP) == KEY_REPEAT || App->input->CheckAxisStates(Axis::AXIS_UP);
	player_input.pressing_D = App->input->GetKey(App->input->keyboard_buttons.buttons_code.RIGHT) == KEY_REPEAT || App->input->CheckAxisStates(Axis::AXIS_RIGHT);
	player_input.pressing_I = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN;
	player_input.pressing_J = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN;
	player_input.pressing_K = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN;
	player_input.pressing_L = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN;
	player_input.pressing_shift = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIAGONALS) == KEY_REPEAT || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIAGONALS) == KEY_REPEAT;

	if (App->input->CheckAxisStates(Axis::AXIS_DOWN_LEFT))
		player_input.pressing_A = player_input.pressing_S = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_DOWN_RIGHT))
		player_input.pressing_D = player_input.pressing_S = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_UP_RIGHT))
		player_input.pressing_D = player_input.pressing_W = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_UP_LEFT))
		player_input.pressing_W = player_input.pressing_A = true;
}

void e1Player::QuestControls()
{
	player_input.pressing_A = App->input->GetKey(App->input->keyboard_buttons.buttons_code.LEFT) == KEY_REPEAT;
	player_input.pressing_S = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DOWN) == KEY_REPEAT;
	player_input.pressing_W = App->input->GetKey(App->input->keyboard_buttons.buttons_code.UP) == KEY_REPEAT;
	player_input.pressing_D = App->input->GetKey(App->input->keyboard_buttons.buttons_code.RIGHT) == KEY_REPEAT;
	player_input.pressing_I = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN;
	player_input.pressing_J = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN;
	player_input.pressing_K = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN;
	player_input.pressing_L = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN;
	player_input.pressing_shift = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIAGONALS) == KEY_REPEAT || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.DIAGONALS) == KEY_REPEAT;
	player_input.pressing_V = App->input->GetKey(App->input->keyboard_buttons.buttons_code.SHOW_SKILLS) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.SHOW_SKILLS) == KEY_DOWN;;
	if (App->map->quest_rooms->actual_room->room_type != RoomType::FOUNTAIN) {
		player_input.pressing_G = App->input->GetKey(App->input->keyboard_buttons.buttons_code.BASIC_ATTACK) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.BASIC_ATTACK) == KEY_DOWN;
		player_input.pressing_F = App->input->GetKey(App->input->keyboard_buttons.buttons_code.HABILTY1) == KEY_DOWN || App->input->GetControllerButtonDown(App->input->controller_Buttons.buttons_code.HABILTY1) == KEY_DOWN;
		player_input.pressing_H = App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN;

	}

	if (!player_input.pressing_shift) {
		if (App->input->CheckAxisStates(Axis::AXIS_DOWN_LEFT)) {
			player_input.pressing_S = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_DOWN_RIGHT)) {
			player_input.pressing_D = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_UP_RIGHT)) {
			player_input.pressing_W = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_UP_LEFT)) {
			player_input.pressing_A = true;
		}
	}
	else {
		if (App->input->CheckAxisStates(Axis::AXIS_DOWN)) {
			player_input.pressing_S = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_RIGHT)) {
			player_input.pressing_D = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_UP)) {
			player_input.pressing_W = true;
		}
		else if (App->input->CheckAxisStates(Axis::AXIS_LEFT)) {
			player_input.pressing_A = true;
		}
	}
	
		
}

void e1Player::LookFlash()
{

	state = State::FLASHING;
	iPoint next_pos{ 0,0 };
	switch (direction) {
	case Direction::DOWN_LEFT:
		next_pos = actual_tile + iPoint{ 0,3 };
		break;
	case Direction::UP_LEFT:
		next_pos = actual_tile + iPoint{ -3,0 };
		break;
	case Direction::UP_RIGHT:
		next_pos = actual_tile + iPoint{ 0,-3 };
		break;
	case Direction::DOWN_RIGHT:
		next_pos = actual_tile + iPoint{ 3,0 };
		break;
	case Direction::LEFT:
		next_pos = actual_tile + iPoint{ -3,3 };
		break;
	case Direction::UP:
		next_pos = actual_tile + iPoint{ -3,-3 };
		break;
	case Direction::RIGHT:
		next_pos = actual_tile + iPoint{ 3,-3 };
		break;
	case Direction::DOWN:
		next_pos = actual_tile + iPoint{ 3,3 };
		break;
	}

	if (App->map->IsWalkable(next_pos, false) && !IsEnemyInThatPosition(next_pos)) {
		drawable = false;
		flash_position = next_pos;
		flash_time = SDL_GetTicks();
		App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{0,-10}, { 0,4,2,0 }, RANDOM, { 20,20 }, { 40,10 }, { 15,5 }, P_NON, 200, 5);
	}
	else
		state = State::IDLE;

}

void e1Player::Flashing()
{

	if (flash_time < SDL_GetTicks() - 500) {
		actual_tile = flash_position;
		state = State::AFTER_FLASH;
		drawable = true;
		position = App->map->MapToWorld(actual_tile.x, actual_tile.y);
		movement_count = { 0,0 };
		if (App->scene->player_type == PlayerType::WARRIOR) {
			position.x += 3;
			position.y -= 19;
		}
		else {
			position.x += 8;
			position.y -= 22;
		}

		App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-10 }, { 0,4,2,0 }, RANDOM, { 20,20 }, { 40,10 }, { 15,5 }, P_NON, 200, 5);
		target_position = position;
		initial_position = position;
		flash_time = SDL_GetTicks();
	}

}

void e1Player::RestTimeAfterFlash()
{
	if (flash_time <= SDL_GetTicks() - 400) {
		ChangeTurn(type);
		state = State::IDLE;
	}
}

void e1Player::ReduceMana(const int & cost_mana)
{
	stats.mana -= cost_mana;
	if (stats.mana < 0)
		stats.mana = 0;
	App->scene->player_mana_bar->UpdateBar(-cost_mana, MANABAR);
}

void e1Player::AugmentMana(const int & plus_mana)
{
	stats.mana += plus_mana;
	if (stats.mana > stats.max_mana)
		stats.mana = stats.max_mana;
	App->scene->player_mana_bar->UpdateBar(plus_mana, MANABAR);
}

void e1Player::ReduceLives(const int & cost_lives)
{
	stats.live -= cost_lives;
	if (stats.live < 0)
		stats.live = 0;
	App->scene->player_hp_bar->UpdateBar(-cost_lives, HPBAR);
}

void e1Player::AugmentLives(const int & plus_lives)
{
	stats.live += plus_lives;
	if (stats.live > stats.max_lives)
		stats.live = stats.max_lives;
	App->scene->player_hp_bar->UpdateBar(plus_lives, HPBAR);
}

bool e1Player::IsEnemyInThatPosition(const iPoint & pos)
{
	bool ret = false;

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			if (pos == (*item)->actual_tile) {
				ret = true;
			}
		}
	}

	return ret;
}


void e1Player::CreateSkills()
{
	upper_button = App->gui->AddButton(684, 600, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, nullptr, App->gui->screen, true, false, false, false);
	upper_skill_button = App->gui->AddLabel(0, 0, "X", upper_button, BLACK, FontType::FF32, nullptr, false);
	upper_skill_button->SetPos(35, -10);
	upper_skill_label = App->gui->AddLabel(0, 0, "Attack 1", upper_skill_button, BLACK, FontType::FF32, nullptr, false);
	upper_skill_label->SetPos(30, 0);

	right_button = App->gui->AddButton(790, 680, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, nullptr, App->gui->screen, true, false, false, false);
	right_skill_button = App->gui->AddLabel(0, 0, "Y", right_button, BLACK, FontType::FF32, nullptr, false);
	right_skill_button->SetPos(35, -10);
	right_skill_label = App->gui->AddLabel(0, 0, "Attack 2", right_skill_button, BLACK, FontType::FF32, nullptr, false);
	right_skill_label->SetPos(30, 0);

	left_button = App->gui->AddButton(590, 680, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, nullptr, App->gui->screen, true, false, false, false);
	left_skill_button = App->gui->AddLabel(0, 0, "B", left_button, BLACK, FontType::FF32, nullptr, false);
	left_skill_button->SetPos(35, -10);
	left_skill_label = App->gui->AddLabel(0, 0, "Attack 3", left_skill_button, BLACK, FontType::FF32, nullptr, false);
	left_skill_label->SetPos(30, 0);

	has_skills = true;
}

void e1Player::UpdateExperience(int experience) {
	if (stats.xp < stats.max_xp) {
		stats.xp += experience;
		LOG("HOLA");
	}
	if(stats.xp >= stats.max_xp) {
		stats.level += 1;
		stats.xp = 0;
		UpdateLevel();
	}
		
}
void e1Player::UpdateLevel()
{
	stats.max_xp *= stats.level;
	App->particles->CreateExplosion(this, nullptr, { 0,0 }, { 8,0,2,2 }, RANDOM);
}
