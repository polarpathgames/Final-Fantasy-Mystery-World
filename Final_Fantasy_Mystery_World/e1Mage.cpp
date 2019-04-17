#include "e1Mage.h"
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
#include "e1Particles.h"
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

e1Mage::e1Mage(const int & x, const int & y) : e1Player(x, y)
{
	LoadEntityData("assets/entities/Warrior.tsx");

	ground = App->tex->Load("assets/sprites/player_pos.png");
	InitStats();
	CenterPlayerInTile();
}

e1Mage::~e1Mage()
{
}

bool e1Mage::CleanUp()
{
	App->tex->UnLoad(ground);
	ground = nullptr;

	return true;
}

void e1Mage::InitStats()
{
	stats.attack_power = 500;
	stats.attack_power_ability_1 = 100;
	stats.cost_mana_special_attack1 = 0;
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

void e1Mage::PrepareSpecialAttack1()
{
	if (stats.mana - stats.cost_mana_special_attack1 >= 0) {
		ReduceMana(stats.cost_mana_special_attack1);
		type_attack = Attacks::SPECIAL_1;
		state = State::ATTACKING;
		SetFireBalls();
	}
	else { // no enough mana so return to idle
		state = State::IDLE;
	}
}

void e1Mage::SpecialAttack1()
{
	std::vector<e1Entity*> item = App->entity_manager->GetEntities();
	if (std::find(item.begin(), item.end(), (e1Entity*)fire_ball) == item.end()) {
		fire_ball = nullptr;
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}
}

void e1Mage::IdAnimToEnum() //Assign every id animation to enum animation
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
		}

	}
}

void e1Mage::SetFireBalls()
{
	iPoint fire_ball_pos = actual_tile;

	e1Particles* fire_ball2 = nullptr;
	e1Particles* fire_ball3 = nullptr;
	switch (direction) {
	case Direction::DOWN: {
		fire_ball_pos += {2, 2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y - 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x - 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::UP: {
		fire_ball_pos += {-2, -2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y + 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x + 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::LEFT: {
		fire_ball_pos += {-2, 2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y - 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x + 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::RIGHT: {
		fire_ball_pos += {2, -2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y + 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x - 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::UP_RIGHT: {
		fire_ball_pos += {0, -2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x + 1, fire_ball_pos.y, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x - 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::UP_LEFT: {
		fire_ball_pos += {-2, 0};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y + 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y - 1, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::DOWN_LEFT: {
		fire_ball_pos += {0, 2};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x + 1, fire_ball_pos.y, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x - 1, fire_ball_pos.y, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	case Direction::DOWN_RIGHT: {
		fire_ball_pos += {2, 0};
		fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y, "fire_ball");
		fire_ball->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball2 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y + 1, "fire_ball");
		fire_ball2->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		fire_ball3 = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, fire_ball_pos.x, fire_ball_pos.y - 1, "fire_ball");
		fire_ball3->SetParticle(e1Particles::ParticleType::FIREBALL, direction);
		break; }
	}


}

