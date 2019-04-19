#include "e1Warrior.h"
#include "e1Player.h"
#include "m1Input.h"
#include "App.h"
#include "m1Render.h"
#include "p2Log.h"
#include "m1Cutscene.h"
#include "App.h"
#include "m1Textures.h"
#include "e1Enemy.h"
#include "e1StaticEntity.h"
#include "e1Rock.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1GUI.h"
#include "m1Pathfinding.h"
#include "m1Collisions.h"
#include "m1Scene.h"
#include "m1FadeToBlack.h"
#include "u1Label.h"
#include "u1Button.h"
#include "u1Bar.h"
#include <string>
#include "u1UI_Element.h"
#include "Brofiler/Brofiler.h"
#include "m1EasingSplines.h"
#include "m1MainMenu.h"

e1Warrior::e1Warrior(const int & x, const int & y) : e1Player(x, y)
{
	LoadEntityData("assets/entities/merche.tsx");

	ground = App->tex->Load("assets/sprites/player_pos.png");
	CenterPlayerInTile();
	InitStats();
}

e1Warrior::~e1Warrior()
{
}

bool e1Warrior::CleanUp()
{
	App->tex->UnLoad(ground);
	ground = nullptr;
	return true;
}

void e1Warrior::InitStats()
{
	stats.attack_power = 500;
	stats.attack_power_ability_1 = 100;
	stats.cost_mana_special_attack1 = 0;
	stats.gold = 400;
	stats.level = 1;
	stats.live = 25;
	stats.mana = 100;
	stats.max_lives = 250;
	stats.max_mana = 100;
	stats.num_hp_potions = 0;
	stats.num_mana_potions = 0;
	stats.xp = 0;
}
void e1Warrior::PrepareSpecialAttack1()
{
	App->audio->PlayFx(App->scene->fx_ability_warrior);
	if (stats.mana - stats.cost_mana_special_attack1 >= 0) {
		if(!god_mode)
		ReduceMana(stats.cost_mana_special_attack1);

		type_attack = Attacks::SPECIAL_1;
		state = State::ATTACKING;
		ChangeAnimation(direction, state, type_attack);
	}
	else { // no enough mana so return to idle
		state = State::IDLE;
	}
}

void e1Warrior::SpecialAttack1()
{
	if (current_animation->Finished()) {
		CheckSpecialAttack1Efects(stats.attack_power_ability_1);
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}
}

void e1Warrior::CheckSpecialAttack1Efects(const int & damage)
{
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::const_iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == e1Entity::EntityType::ENEMY) {
				bool has_succeeded = false;
				if (actual_tile + iPoint{ -1,-1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ -1,0 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ -1,1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ 0,1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ 1,1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ 1,0 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ 1,-1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}
				else if (actual_tile + iPoint{ 0,-1 } == (*item)->actual_tile) {
					has_succeeded = true;
				}

				if (has_succeeded) {
					App->input->ControllerVibration(0.2F, 200);
					e1Enemy* enemy_attacked = (e1Enemy*)(*item);
					enemy_attacked->GetHitted(damage);
				}
			}
			else if ((*item)->type == e1Entity::EntityType::STATIC) {
				bool has_succeeded = false;
				e1StaticEntity* ent = (e1StaticEntity*)*item;
				if (ent->static_type == e1StaticEntity::Type::BREAKABLE_ROCK) {
					if (actual_tile + iPoint{ -1,-1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ -1,0 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ -1,1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ 0,1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ 1,1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ 1,0 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ 1,-1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}
					else if (actual_tile + iPoint{ 0,-1 } == (*item)->actual_tile) {
						has_succeeded = true;
					}

					if (has_succeeded) {
						e1Rock* enemy_attacked = (e1Rock*)(*item);
						enemy_attacked->GetHitted();
					}
				}
				
			}
		}
	}
}

void e1Warrior::IdAnimToEnum() //Assign every id animation to enum animation
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;//
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;//
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;//
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;//
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;//
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;//
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;//
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;//
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;//
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;//
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;//
		case 16:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;//
		case 18:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;//
		case 19:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;//
		case 21:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;//
		case 22:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;//
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;//
		case 33:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;//
		case 27:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;//
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;//
		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;//
		case 39:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;//
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;//
		case 54:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;//
		case 60:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;//
		case 63:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;//
		case 66:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;//
		case 69:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;//
		case 72:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_1;
			break;//
		case 78:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_1;
			break;//
		case 76:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_1;
			break;//
		case 74:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_1;
			break;//
		case 73:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_1;
			break;//
		case 75:
			data.animations[i].animType = AnimationState::ABILITY_UP_1;
			break;//
		case 77:
			data.animations[i].animType = AnimationState::ABILITY_RIGHT_1;
			break;//
		case 79:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_1;
			break;//
		case 61:
			data.animations[i].animType = AnimationState::DEATH_DOWN;
			break;//
		case 64:
			data.animations[i].animType = AnimationState::DEATH_LEFT;
			break;//
		case 70:
			data.animations[i].animType = AnimationState::DEATH_RIGHT;
			break;//
		case 65:
			data.animations[i].animType = AnimationState::DEATH_UP;
			break;//
		}

	}
}