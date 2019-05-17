#include "e1Player.h"
#include "m1Input.h"
#include "App.h"
#include "m1Render.h"
#include "p2Log.h"
#include "m1Cutscene.h"
#include "App.h"
#include "m1DialogSystem.h"
#include "m1Textures.h"
#include "e1Enemy.h"
#include "e1State.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "e1Warrior.h"
#include "e1Archer.h"
#include "e1Mage.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1Window.h"
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
#include "m1MenuManager.h"
#include "m1MainMenu.h"
#include "m1ParticleManager.h"


e1Player::e1Player(const int &x, const int &y) : e1DynamicEntity(x,y)
{
	type = EntityType::PLAYER;
	ground = App->tex->Load("assets/sprites/player_pos.png");
	current_animation = &anim.IdleDownLeft;
	direction = Direction::DOWN_LEFT;
	Init();
}

void e1Player::Init()
{
	state = State::IDLE;

	velocity.x = 160;
	velocity.y = 80;
	//has_turn = true;

	App->entity_manager->AssignEntityTurn(this);

	if (App->map->data.properties.GetValue("movement") == 1)
		movement_type = Movement_Type::InLobby;
	else
		movement_type = Movement_Type::InQuest;

	coll = App->collision->AddCollider(SDL_Rect{ 0,0,19,6 }, COLLIDER_PLAYER, (m1Module*)App->entity_manager);

	timer_ability1.Stop();
}

e1Player::~e1Player()
{
	App->tex->UnLoad(ground);
	ground = nullptr;
}

bool e1Player::PreUpdate()
{
	BROFILER_CATEGORY("Player PreUpdate", Profiler::Color::Yellow);

	if (!block_controls)
		ReadPlayerInput();

	return true;
}

bool e1Player::Update(float dt)
{
	BROFILER_CATEGORY("Player Update", Profiler::Color::Yellow);

	PerformActions(dt);

	if (App->debug)
		App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	if (coll != nullptr)
		coll->SetPos(position.x + pivot.x/2 - 2, position.y + 20);


	return true;
}

bool e1Player::Load(pugi::xml_node & node)
{
	pugi::xml_node p_stats = node.child("stats");
	stats.max_lives = p_stats.attribute("max_lives").as_int();
	stats.max_mana = p_stats.attribute("max_mana").as_int();
	stats.gold = p_stats.attribute("gold").as_int();
	stats.xp = p_stats.attribute("xp").as_int();
	stats.max_xp = p_stats.attribute("max_xp").as_int();
	stats.attack_power = p_stats.attribute("attack_power").as_int();
	stats.num_hp_potions = p_stats.attribute("num_hp_potions").as_int();
	stats.num_mana_potions = p_stats.attribute("num_mana_potions").as_int();
	stats.level = p_stats.attribute("level").as_int();
	stats.attack_power_ability_1 = p_stats.attribute("attack_power_ability_1").as_int();
	stats.attack_power_ability_3 = p_stats.attribute("attack_power_ability_3").as_int();
	App->main_menu->entity_type = (EntityType)p_stats.attribute("entity_type").as_int();
	pugi::xml_node p_globals = node.child("globals");
	App->globals.player_name = p_globals.attribute("player_name").as_string();
	App->globals.ability1_gained = p_globals.attribute("ability1_gained").as_bool();
	App->globals.ability2_gained = p_globals.attribute("ability2_gained").as_bool();
	App->globals.CutSceneAfterBossTutorialPlayed = p_globals.attribute("CutSceneAfterBossTutorialPlayed").as_bool();
	App->globals.CutSceneFinalRoomTutorialPlayed = p_globals.attribute("CutSceneFinalRoomTutorialPlayed").as_bool();
	App->globals.CutSceneLobbyExplain = p_globals.attribute("CutSceneLobbyExplain").as_bool();
	App->globals.CutSceneMiddleRoomTutorialPlayed = p_globals.attribute("CutSceneMiddleRoomTutorialPlayed").as_bool();
	App->globals.CutSceneTutorialGirlEscapingPlayed = p_globals.attribute("CutSceneTutorialGirlEscapingPlayed").as_bool();
	App->globals.Tutorial_first_time = p_globals.attribute("Tutorial_first_time").as_bool();
	App->scene->player_type = (PlayerType)p_globals.attribute("player_type").as_bool();
	App->scene->player->Init();
	App->scene->player->CenterPlayerInTile();
	App->render->CenterCameraOnPlayer(App->scene->player->position);
	return true;
}

bool e1Player::Save(pugi::xml_node & node) const
{
	pugi::xml_node p_stats = node.append_child("stats");
	p_stats.append_attribute("max_lives") = (int)stats.max_lives;
	p_stats.append_attribute("max_mana") = (int)stats.max_mana;
	p_stats.append_attribute("gold") = (int)stats.gold;
	p_stats.append_attribute("xp") = (int)stats.xp;
	p_stats.append_attribute("max_xp") = (int)stats.max_xp;
	p_stats.append_attribute("attack_power") = (int)stats.attack_power;
	p_stats.append_attribute("num_hp_potions") = (int)stats.num_hp_potions;
	p_stats.append_attribute("num_mana_potions") = (int)stats.num_mana_potions;
	p_stats.append_attribute("level") = (int)stats.level;
	p_stats.append_attribute("attack_power_ability_1") = (int)stats.attack_power_ability_1;
	p_stats.append_attribute("attack_power_ability_3") = (int)stats.attack_power_ability_3;
	p_stats.append_attribute("entity_type") = (int)App->main_menu->entity_type;
	pugi::xml_node p_globals = node.append_child("globals");
	p_globals.append_attribute("player_name") = App->globals.player_name.data();
	p_globals.append_attribute("ability1_gained") = (bool)App->globals.ability1_gained;
	p_globals.append_attribute("ability2_gained") = (bool)App->globals.ability2_gained;
	p_globals.append_attribute("CutSceneAfterBossTutorialPlayed") = (bool)App->globals.CutSceneAfterBossTutorialPlayed;
	p_globals.append_attribute("CutSceneFinalRoomTutorialPlayed") = (bool)App->globals.CutSceneFinalRoomTutorialPlayed;
	p_globals.append_attribute("CutSceneLobbyExplain") = (bool)App->globals.CutSceneLobbyExplain;
	p_globals.append_attribute("CutSceneMiddleRoomTutorialPlayed") = (bool)App->globals.CutSceneMiddleRoomTutorialPlayed;
	p_globals.append_attribute("CutSceneTutorialGirlEscapingPlayed") = (bool)App->globals.CutSceneTutorialGirlEscapingPlayed;
	p_globals.append_attribute("Tutorial_first_time") = (bool)App->globals.Tutorial_first_time;
	p_globals.append_attribute("player_type") = (int)App->scene->player_type;
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
		else {
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
		}
	}
	if (c2->type == COLLIDER_MENU_QUEST) {
		App->menu_manager->CreateGoToQuestMenu();
		App->scene->SetMenuState(StatesMenu::GO_TO_QUEST_MENU);
	}
	if (c2->type == COLLIDER_CUTSCENE_BRIDGE) {
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneBlockPass.xml");
	}
	if (c2->type == COLLIDER_QUEST_ICE) {
		App->dialog->PerformDialogue(10);
	}
}

void e1Player::OnCollisionExit(Collider * c2)
{
	if (c2->type == COLLIDER_CUTSCENE_BRIDGE) {
		//App->menu_manager->ShowHUD(true);
	}
}

void e1Player::CheckLobbyCollision(const float & dt, const Direction & dir)
{
	BROFILER_CATEGORY("Player CheckLobbyCollision", Profiler::Color::Yellow);

	switch (direction) {
	case Direction::RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt))})) {
			current_animation = &anim.GoDownRight;
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })) {
			current_animation = &anim.GoUpRight;
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
			current_animation = &anim.GoDownLeft;
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			current_animation = &anim.GoDownRight;
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
			current_animation = &anim.GoUpLeft;
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })){
			current_animation = &anim.GoDownLeft;
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
			current_animation = &anim.GoUpLeft;
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else if (App->map->IsWalkable({ (int)(position.x + floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y - floor(velocity.y * dt)) })){
			current_animation = &anim.GoUpRight;
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
	if (state == State::MENU) {
		direction = Direction::DOWN_LEFT;
		state = State::IDLE;
		current_animation = &anim.IdleDownLeft;
		anim.DeathDownLeft.Reset();
		anim.DeathDownRight.Reset();
		anim.DeathUpRight.Reset();
		anim.DeathUpLeft.Reset();
		anim.DeathDown.Reset();
		anim.DeathRight.Reset();
		anim.DeathUp.Reset();
		anim.DeathLeft.Reset();
	}

	actual_tile = App->map->WorldToMap(position.x, position.y);
	movement_count = { 0,0 };
	CenterOnTile();

	target_position = position;
	initial_position = position;
}



void e1Player::ReadPlayerInput()
{
	BROFILER_CATEGORY("ReadPlayerInput", Profiler::Color::Yellow);

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
		else if (player_input.pressing_SPACE || (player_input.pressing_1 && App->globals.ability1_gained == true) || (player_input.pressing_3 && App->globals.ability3_gained)) {
			state = State::BEFORE_ATTACK;
		}
		else if (player_input.pressing_2 && App->globals.ability2_gained == true) {
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
	BROFILER_CATEGORY("ReadPlayerMovementInQuest", Profiler::Color::Yellow);

	if (target_position == position) {
		bool is_movement_acepted = false;
		if (MultipleButtons(&player_input)) {
			if (player_input.pressing_shift) {
				if (player_input.pressing_A) {
					direction = Direction::LEFT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x - 1, actual_tile.y + 1 }, false)) {
						target_position.create(position.x - App->map->data.tile_width, position.y);
						movement_count.x -= App->map->data.tile_width;
						actual_tile += {-1, 1};
						is_movement_acepted = true;
					}
					else {
						state = State::IDLE;
					}
				}
				else if (player_input.pressing_D) {
					direction = Direction::RIGHT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y - 1 }, false)) {
						target_position.create(position.x + App->map->data.tile_width, position.y);
						movement_count.x += App->map->data.tile_width;
						actual_tile += {1, -1};
						is_movement_acepted = true;
					}
					else {
						state = State::IDLE;
					}
				}
				else if (player_input.pressing_W) {
					direction = Direction::UP;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x - 1, actual_tile.y - 1 }, false)) {
						target_position.create(position.x, position.y - App->map->data.tile_height);
						movement_count.y -= App->map->data.tile_height;
						actual_tile += {-1, -1};
						is_movement_acepted = true;
					}
					else {
						state = State::IDLE;
					}
				}
				else if (player_input.pressing_S) {
					direction = Direction::DOWN;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y + 1 }, false)) {
						target_position.create(position.x, position.y + App->map->data.tile_height);
						movement_count.y += App->map->data.tile_height;
						actual_tile += {1, 1};
						is_movement_acepted = true;
					}
					else {
						state = State::IDLE;
					}
				}
			}
			else {
				if (player_input.pressing_S) {
					direction = Direction::DOWN_LEFT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x, actual_tile.y + 1 }, false)) {
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
				else if (player_input.pressing_D) {
					direction = Direction::DOWN_RIGHT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x + 1, actual_tile.y }, false)) {
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
				else if (player_input.pressing_W) {
					direction = Direction::UP_RIGHT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x, actual_tile.y - 1 }, false)) {
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
				else if (player_input.pressing_A) {
					direction = Direction::UP_LEFT;
					if (NextTileFree(direction) && App->map->IsWalkable({ actual_tile.x - 1, actual_tile.y }, false)) {
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
			if (is_movement_acepted) {
				turn_done = true;
			}
			else {
				ChangeAnimation(direction, state);
			}
		}
		else {
			state = State::IDLE;
			target_position = position;
			ChangeAnimation(direction, state);
		}
	}
}

void e1Player::ReadPlayerMovementInLobby()
{
	BROFILER_CATEGORY("ReadPlayerMovementInLobby", Profiler::Color::Yellow);

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
	BROFILER_CATEGORY("ReadAttack", Profiler::Color::Yellow);

	if (player_input.pressing_SPACE) {
		PrepareBasicAttack();
		App->audio->PlayFx(App->scene->fx_attack);
		return;
	}
	if ((App->input->GetKeyDownOrRepeat(App->input->keyboard_buttons.buttons_code.HABILTY1) || App->input->GetControllerButtonDownOrRepeat(App->input->controller_Buttons.buttons_code.HABILTY1)) 
		&& App->globals.ability1_gained == true) {
		if (timer_ability1.IsRunning()) {
			if (timer_ability1.ReadSec() >= time_to_wait_ability1) {
				PrepareSpecialAttack1();
				timer_ability1.Stop();
			}
		}
		else {
			timer_ability1.Start();
		}

		return;
	}
	else if (timer_ability1.IsRunning()) timer_ability1.Stop();

	if (player_input.pressing_3 && App->globals.ability3_gained == true) {
		App->audio->PlayFx(App->scene->fx_ability3);
		PrepareSpecialAttack2();
		return;
	}
}

void e1Player::InitStats()
{
	for (std::list<Property<int>*>::iterator item = general_properties.properties.begin(); item != general_properties.properties.end(); item++) {
		if (strcmp((*item)->GetName(), "max_lives") == 0) {
			stats.max_lives = (*item)->GetValue();
			stats.live = stats.max_lives;
		}
		else if (strcmp((*item)->GetName(), "attack_power") == 0) {
			stats.attack_power = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "max_mana") == 0) {
			stats.max_mana = (*item)->GetValue();
			stats.mana = stats.max_mana;
		}
		else if (strcmp((*item)->GetName(), "attack_power_ability") == 0) {
			stats.attack_power_ability_1 = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "attack_power_ability3") == 0) {
			stats.attack_power_ability_3 = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "cost_mana_special_attack") == 0) {
			stats.cost_mana_special_attack1 = (*item)->GetValue();
		}
		else if (strcmp((*item)->GetName(), "cost_mana_special_attack3") == 0) {
			stats.cost_mana_special_attack3 = (*item)->GetValue();
		}
	}
}

void e1Player::PrepareBasicAttack()
{
	BROFILER_CATEGORY("PrepareBasicAttack", Profiler::Color::Yellow);

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
	BROFILER_CATEGORY("PerformActions", Profiler::Color::Yellow);

	if (player_input.pressing_V && App->scene->GetMenuState() != StatesMenu::OPTIONS_MENU && App->scene->GetMenuState() != StatesMenu::CONTROLS_MENU && App->scene->GetMenuState() != StatesMenu::PAUSE_MENU && !App->cutscene_manager->is_executing){
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
		case Attacks::SPECIAL_2:
			SpecialAttack2();
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
	BROFILER_CATEGORY("basicAttack", Profiler::Color::Yellow);

	if (current_animation->Finished()) {
		switch (direction) {
		case Direction::DOWN_LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::DOWN_RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP:
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::DOWN:
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		case Direction::LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		}
		CheckBasicAttackEffects(e1Entity::EntityType::ENEMY, direction, stats.attack_power);
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}


}

void e1Player::PrepareSpecialAttack2()
{

	if (stats.mana - stats.cost_mana_special_attack3 >= 0 || god_mode == true) {
		if (!god_mode)
			ReduceMana(stats.cost_mana_special_attack3);
		//App->audio->PlayFx(App->scene->fx_ability_warrior);

		type_attack = Attacks::SPECIAL_2;
		state = State::ATTACKING;
		switch (direction) {
		case Direction::DOWN_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 400, EASE_IN_BACK);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 400, EASE_IN_BACK);
			break;
		case Direction::UP_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 400, EASE_IN_BACK);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 400, EASE_IN_BACK);
			break;
		case Direction::DOWN_RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4, 400, EASE_IN_BACK);
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4, 400, EASE_IN_BACK);
			break;
		case Direction::UP_LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4, 400, EASE_IN_BACK);
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4, 400, EASE_IN_BACK);
			break;
		case Direction::UP:
			App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3, 400, EASE_IN_BACK);
			break;
		case Direction::DOWN:
			App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3, 400, EASE_IN_BACK);
			break;
		case Direction::RIGHT:
			App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3, 400, EASE_IN_BACK);
			break;
		case Direction::LEFT:
			App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3, 400, EASE_IN_BACK);
			break;
		}
		ChangeAnimation(direction, state, type_attack);
	}
	else { // no enough mana so return to idle
		App->audio->PlayFx(App->scene->fx_ability_no_mana);
		state = State::IDLE;
	}
}

void e1Player::SpecialAttack2()
{
	if (current_animation->Finished()) {
		switch (direction) {
		case Direction::DOWN_LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::DOWN_RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP_LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 4 + 1, 200, EASE);
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 4 + 1, 200, EASE);
			break;
		case Direction::UP:
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y + App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::DOWN:
			return_spline = App->easing_splines->CreateSpline(&position.y, position.y - App->map->data.tile_height / 3 + 1, 200, EASE);
			break;
		case Direction::RIGHT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x - App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		case Direction::LEFT:
			return_spline = App->easing_splines->CreateSpline(&position.x, position.x + App->map->data.tile_width / 3 + 1, 200, EASE);
			break;
		}
		CheckBasicSpecialAttack2Effects();
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
		App->audio->PlayFx(App->scene->fx_ability3_hit);
	}
}

void e1Player::CheckBasicSpecialAttack2Effects()
{
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			iPoint origin = actual_tile;
			iPoint destination = (*item)->actual_tile;
			bool has_succeeded = false;
			switch (direction) {
			case Direction::DOWN_LEFT: {
				origin += {0, 1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::DOWN_RIGHT: {
				origin += {1, 0};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::DOWN: {
				origin += {1, 1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP: {
				origin += {-1, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP_LEFT: {
				origin += {-1, 0};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP_RIGHT: {
				origin += {0, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::LEFT: {
				origin += {-1, 1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::RIGHT: {
				origin += {1, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			default:
				LOG("There is no valid direction to attack");
				break;
			}
			if (has_succeeded) {
				e1Enemy* enemy_attacked = (e1Enemy*)(*item);
				enemy_attacked->GetHitted(stats.attack_power_ability_3);
				AugmentLives(stats.attack_power_ability_3*((float)((float)App->random.Generate(20, 60) / (float)100.0F)));
			}
		}
	}



}

void e1Player::PerformMovementInLobby(float dt)
{
	BROFILER_CATEGORY("PerformMovementInLobby", Profiler::Color::Yellow);

	switch (direction)
	{
	case Direction::DOWN_LEFT:
		if (App->map->IsWalkable({ (int)(position.x - floor(velocity.x * dt) + pivot.x), (int)(position.y + pivot.y + floor(velocity.y * dt)) })) {
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &anim.GoDownLeft;
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
			current_animation = &anim.GoUpRight;
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
			current_animation = &anim.GoUpLeft;
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
			current_animation = &anim.GoDownRight;
		}
		else {
			state = State::IDLE;
			ChangeAnimation(direction, state);
		}
		break;
	case Direction::RIGHT:
		if (App->map->IsWalkable({ (int)(position.x + floor(180 * dt) + pivot.x), position.y + pivot.y })) {
			position.x += floor(velocity.x * dt);
			current_animation = &anim.GoRight;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}
		break;
	case Direction::LEFT:
		if (App->map->IsWalkable({(int)(position.x - floor(180 * dt) + pivot.x), position.y + pivot.y })) {
			position.x -= floor(velocity.x * dt);
			current_animation = &anim.GoLeft;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}
		break;
	case Direction::UP:
		if (App->map->IsWalkable({ (position.x + pivot.x), (int)(position.y + pivot.y - floor(180 * dt)) })) {
			position.y -= floor(velocity.y * 2 * dt);
			current_animation = &anim.GoUp;
		}
		else {
			CheckLobbyCollision(dt, direction);
		}

		break;
	case Direction::DOWN:
		if (App->map->IsWalkable({ (position.x + pivot.x), (int)(position.y + pivot.y + floor(180 * dt)) })) {
			position.y += floor(velocity.y * 2 * dt);
			current_animation = &anim.GoDown;
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
	BROFILER_CATEGORY("PerformMovementInQuest", Profiler::Color::Yellow);

	switch (direction)
	{
	case Direction::DOWN_LEFT:
		if (position.x >= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &anim.GoDownLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleDownLeft;
		}
		break;
	case Direction::UP_RIGHT:
		if (position.x <= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &anim.GoUpRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleUpRight;
		}
		break;
	case Direction::UP_LEFT:
		if (position.x >= initial_position.x + movement_count.x  && position.y >= initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
			current_animation = &anim.GoUpLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleUpLeft;
		}
		break;
	case Direction::DOWN_RIGHT:
		if (position.x <= initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
			current_animation = &anim.GoDownRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleDownRight;
		}
		break;
	case Direction::LEFT:
		if (position.x >= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x -= floor(velocity.x * dt);
			current_animation = &anim.GoLeft;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleLeft;
		}
		break;
	case Direction::RIGHT:
		if (position.x <= initial_position.x + movement_count.x && position.y == initial_position.y + movement_count.y) {
			position.x += floor(velocity.x * dt);
			current_animation = &anim.GoRight;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleRight;
		}
		break;
	case Direction::UP:
		if (position.x == initial_position.x + movement_count.x && position.y >= initial_position.y + movement_count.y) {
			position.y -= floor(velocity.y * dt);
			current_animation = &anim.GoUp;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleUp;
		}
		break;
	case Direction::DOWN:
		if (position.x == initial_position.x + movement_count.x && position.y <= initial_position.y + movement_count.y) {
			position.y += floor(velocity.y * dt);
			current_animation = &anim.GoDown;
		}
		else {
			position.x = initial_position.x + movement_count.x;
			position.y = initial_position.y + movement_count.y;
			target_position = position;
			state = State::IDLE;
			current_animation = &anim.IdleDown;
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
			current_animation = &anim.IdleUp;
		}
		if (player_input.pressing_J) {
			direction = Direction::LEFT;
			current_animation = &anim.IdleLeft;
		}
		if (player_input.pressing_K) {
			direction = Direction::DOWN;
			current_animation = &anim.IdleDown;
		}
		if (player_input.pressing_L) {
			direction = Direction::RIGHT;
			current_animation = &anim.IdleRight;
		}
	}
	else if (!player_input.pressing_shift) {
		if (player_input.pressing_UP_LEFT) {
			direction = Direction::UP_LEFT;
			current_animation = &anim.IdleUpLeft;
		}
		if (player_input.pressing_DOWN_LEFT) {
			direction = Direction::DOWN_LEFT;
			current_animation = &anim.IdleDownLeft;
		}
		if (player_input.pressing_DOWN_RIGHT) {
			direction = Direction::DOWN_RIGHT;
			current_animation = &anim.IdleDownRight;
		}
		if (player_input.pressing_UP_RIGHT) {
			direction = Direction::UP_RIGHT;
			current_animation = &anim.IdleUpRight;
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
	App->render->CameraTremble(0.33F, 1.9F);
	if(!god_mode)
		ReduceLives(damage_taken);

	if (stats.live <= 0) {
		App->entity_manager->entity_turn = this;
		state = State::DEATH;
		ChangeAnimation(direction, state);
		death_time = SDL_GetTicks();
		
	}

	


}

void e1Player::Death()
{
	BROFILER_CATEGORY("Player Death", Profiler::Color::Yellow);

	if (current_animation->Finished() && death_time <= SDL_GetTicks() - 1000) {
		std::list<u1GUI*> list = App->gui->GetUIList();
		std::list<u1GUI*>::iterator item = list.begin();
		for (; item != list.end(); ++item) {
			if ((*item) != nullptr && (*item)->GetType() == HIT_POINT_LABEL)
				(*item)->to_delete = true;
		}
		App->audio->PlayFx(App->scene->fx_die);
		App->map->CleanUp();
		App->easing_splines->CleanUp();
		App->entity_manager->DeleteEntitiesNoPlayer();
		App->menu_manager->EnableHUD(false);
		App->menu_manager->CreateGameOver();
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
		state = State::IDLE;
		ChangeAnimation(direction, state);
	}
	return block_controls = to_block;
}

void e1Player::LobbyControls()
{
	player_input.pressing_A = App->input->GetKey(App->input->keyboard_buttons.buttons_code.LEFT) == KEY_REPEAT || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1;
	player_input.pressing_S = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DOWN) == KEY_REPEAT || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1;
	player_input.pressing_W = App->input->GetKey(App->input->keyboard_buttons.buttons_code.UP) == KEY_REPEAT || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1;
	player_input.pressing_D = App->input->GetKey(App->input->keyboard_buttons.buttons_code.RIGHT) == KEY_REPEAT || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1;
	player_input.pressing_I = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == -1;
	player_input.pressing_J = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == -1;
	player_input.pressing_K = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1;
	player_input.pressing_L = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == 1;
	
	player_input.pressing_UP_LEFT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN;
	player_input.pressing_UP_RIGHT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN;
	player_input.pressing_DOWN_LEFT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN;
	player_input.pressing_DOWN_RIGHT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN;


	
	player_input.pressing_shift = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIAGONALS) == KEY_REPEAT || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIAGONALS) == KEY_REPEAT;

	/*if (App->input->CheckAxisStates(Axis::AXIS_DOWN_LEFT))
		player_input.pressing_A = player_input.pressing_S = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_DOWN_RIGHT))
		player_input.pressing_D = player_input.pressing_S = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_UP_RIGHT))
		player_input.pressing_D = player_input.pressing_W = true;
	else if (App->input->CheckAxisStates(Axis::AXIS_UP_LEFT))
		player_input.pressing_W = player_input.pressing_A = true;*/
}

void e1Player::QuestControls()
{
	player_input.pressing_A = App->input->GetKey(App->input->keyboard_buttons.buttons_code.LEFT) == KEY_REPEAT;
	player_input.pressing_S = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DOWN) == KEY_REPEAT;
	player_input.pressing_W = App->input->GetKey(App->input->keyboard_buttons.buttons_code.UP) == KEY_REPEAT;
	player_input.pressing_D = App->input->GetKey(App->input->keyboard_buttons.buttons_code.RIGHT) == KEY_REPEAT;
	player_input.pressing_I = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == -1;
	player_input.pressing_J = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == -1;
	player_input.pressing_K = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == 1;
	player_input.pressing_L = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == 1;
	player_input.pressing_shift = App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIAGONALS) == KEY_REPEAT || App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
	//player_input.pressing_V = App->input->GetKey(App->input->keyboard_buttons.buttons_code.SHOW_SKILLS) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.SHOW_SKILLS) == KEY_DOWN;;
	
	player_input.pressing_UP_LEFT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == -1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_LEFT) == KEY_DOWN;
	player_input.pressing_UP_RIGHT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == -1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECTION_UP) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECTION_UP) == KEY_DOWN;
	player_input.pressing_DOWN_LEFT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == 1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN) == KEY_DOWN;
	player_input.pressing_DOWN_RIGHT = (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY) == 1) || App->input->GetKey(App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT) == KEY_DOWN;

	
	if ((App->map->quest_rooms != nullptr &&App->map->quest_rooms->actual_room->room_type != RoomType::FOUNTAIN) || App->fast_start) {
		player_input.pressing_SPACE = App->input->GetKey(App->input->keyboard_buttons.buttons_code.BASIC_ATTACK) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.BASIC_ATTACK) == KEY_DOWN;
		player_input.pressing_1 = App->input->GetKey(App->input->keyboard_buttons.buttons_code.HABILTY1) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.HABILTY1) == KEY_DOWN;
		player_input.pressing_2 = App->input->GetKey(App->input->keyboard_buttons.buttons_code.HABILITY2) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.HABILITY2) == KEY_DOWN;
		player_input.pressing_3 = App->input->GetKey(App->input->keyboard_buttons.buttons_code.HABILITY3) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.HABILITY3) == KEY_DOWN;
	}

	if (!player_input.pressing_shift) {
		App->menu_manager->ChangeCompass(false);
		if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1) {
			player_input.pressing_S = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1) {
			player_input.pressing_D = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1) {
			player_input.pressing_W = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1 && App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1) {
			player_input.pressing_A = true;
		}
	}
	else {
		App->menu_manager->ChangeCompass(true);
		if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1) {
			player_input.pressing_S = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == 1) {
			player_input.pressing_D = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1) {
			player_input.pressing_W = true;
		}
		else if (App->input->GetAxisRaw(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) == -1) {
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
		App->audio->PlayFx(App->scene->fx_flash);
		state = State::AFTER_FLASH;
		drawable = true;
		position = App->map->MapToWorld(actual_tile.x, actual_tile.y);
		movement_count = { 0,0 };
		CenterPlayerInTile();
		App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-10 }, { 0,4,2,0 }, RANDOM, { 20,20 }, { 40,10 }, { 15,5 }, P_NON, 200, 5);
		target_position = position;
		initial_position = position;
		flash_time = SDL_GetTicks();
	}

}

void e1Player::RestTimeAfterFlash()
{
	if (flash_time <= SDL_GetTicks() - 400) {
		turn_done = true;
		state = State::IDLE;
	}
}

void e1Player::ReduceMana(const int & cost_mana)
{
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(-cost_mana).data(), App->gui->screen, BLUE, FontType::PMIX24);
	stats.mana -= cost_mana;
	if (stats.mana < 0)
		stats.mana = 0;
	App->menu_manager->hud.player_mana_bar->UpdateBar(-cost_mana, MANABAR);
}

void e1Player::AugmentMana(const int & plus_mana, bool level_up)
{
	if (!level_up) {
		iPoint pos{ 0,0 };
		pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
		pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
		App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(plus_mana).data(), App->gui->screen, BLUE, FontType::PMIX24);
	}

	stats.mana += plus_mana;
	if (stats.mana > stats.max_mana)
		stats.mana = stats.max_mana;

	App->menu_manager->hud.player_mana_bar->UpdateBar(plus_mana, MANABAR);

}

void e1Player::ReduceLives(const int & cost_lives)
{
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	if (stats.live > 0)
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(cost_lives).data(), App->gui->screen, RED, FontType::PMIX24);

	stats.live -= cost_lives;
	if (stats.live < 0)
		stats.live = 0;
	App->menu_manager->hud.player_hp_bar->UpdateBar(-cost_lives, HPBAR);
}

void e1Player::AugmentLives(const int & plus_lives, bool level_up)
{
	if (!level_up) {
		iPoint pos{ 0,0 };
		pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
		pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
		App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(plus_lives).data(), App->gui->screen, GREEN, FontType::PMIX24);
	}

	stats.live += plus_lives;
	if (stats.live > stats.max_lives)
		stats.live = stats.max_lives;

	//App->scene->player_hp_bar->max_capacity += plus_lives;
	App->menu_manager->hud.player_hp_bar->UpdateBar(plus_lives, HPBAR);


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

void e1Player::ReduceGold(const int & cost_gold)
{
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(-cost_gold).data(), App->gui->screen, YELLOW, FontType::PMIX24);
	stats.gold -= cost_gold;
	if (stats.gold < 0)
		stats.gold = 0;
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

void e1Player::AugmentGold(const int & plus_gold)
{
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(plus_gold).data(), App->gui->screen, YELLOW, FontType::PMIX24);
	stats.gold += plus_gold;
}

void e1Player::SetPlayerIdle()
{
	state = State::IDLE;

	position = App->map->MapToWorld(actual_tile.x, actual_tile.y) - pivot;
	position.x += App->map->data.tile_width * 0.5F;
	position.y += App->map->data.tile_height * 0.5F;

	movement_count = { 0,0 };

	target_position = position;
	initial_position = position;
}

void e1Player::UpdateExperience(int experience) {

	if (stats.xp < stats.max_xp) {
		stats.xp += experience;
	}

	App->menu_manager->hud.player_exp_bar->UpdateBar(experience, UIType::EXPBAR);

	if(stats.xp >= stats.max_xp) {
		stats.level += 1;
		stats.xp = 0;
		UpdateLevel();
	}
}
