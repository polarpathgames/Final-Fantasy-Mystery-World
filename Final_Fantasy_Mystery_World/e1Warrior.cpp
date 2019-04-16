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
	LoadEntityData("assets/entities/Warrior.tsx");

	ground = App->tex->Load("assets/sprites/player_pos.png");
	InitStats();
	CenterPlayerInTile();
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
	stats.cost_mana_special_attack1 = 50;
	stats.gold = 0;
	stats.level = 1;
	stats.live = 250;
	stats.mana = 100;
	stats.max_lives = 250;
	stats.max_mana = 100;
	stats.num_hp_potions = 0;
	stats.num_mana_potions = 0;
	stats.xp = 0;

}
void e1Warrior::PrepareSpecialAttack1()
{
	if (stats.mana - stats.cost_mana_special_attack1 >= 0) {
		ReduceMana(stats.cost_mana_special_attack1);
		type_attack = Attacks::SPECIAL_1;
		state = State::ATTACKING;
		current_animation = &BasicAttackDown;
	}
	else { // no enough mana so return to idle
		state = State::IDLE;
	}
}

void e1Warrior::SpecialAttack1()
{
	if (current_animation->Finished()) {
		CheckSpecialAttack1Efects(stats.attack_power);
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
					e1Enemy* enemy_attacked = (e1Enemy*)(*item);
					enemy_attacked->GetHitted(damage);
				}
			}
		}
	}
}