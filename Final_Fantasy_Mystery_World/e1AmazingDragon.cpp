#include "e1AmazingDragon.h"
#include "App.h"
#include "m1EntityManager.h"
#include "e1Player.h"
#include "e1Particles.h"

e1AmazingDragon::e1AmazingDragon(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/AmazingDragon.tsx");
	name.assign("AmazingDragon");
	enemy_type = EnemyType::AMAZING_DRAGON;

	SetPivot(110, 170);

	CenterOnTile();

	target_position = position;
	initial_position = position;
	position.x += 20;
	position.y += 160;
	InitStats();
	allow_turn = false;
	drawable = false;

	turns_to_wait_after_fire_ball = 2U;
	waves_before_recover_energy = 3U;
	turns_recovering_energy = 5U;
	number_of_fire_balls = 5U;
	anim.BasicAttackDownLeft.loop = false;
}

e1AmazingDragon::~e1AmazingDragon()
{
}

bool e1AmazingDragon::PreUpdate()
{

	if (active) {

		switch (dragon_states)
		{
		case e1AmazingDragon::AmazingDragonStates::WEAK:
			if (turns_recovering_energy == auxiliar_turn_count) {
				auxiliar_turn_count = 0U;
				dragon_states = AmazingDragonStates::IDLE;
				current_animation = &anim.IdleDownLeft;
				turn_done = true;
			}
			else {
				++auxiliar_turn_count;
				turn_done = true;
			}
			break;
		case e1AmazingDragon::AmazingDragonStates::IDLE: {
			if (auxiliar_attack_count == waves_before_recover_energy) {
				auxiliar_attack_count = 0U;
				dragon_states = AmazingDragonStates::WEAK;
				current_animation = &anim.GoDownLeft;
				turn_done = true;
			}
			else {
				current_animation = &anim.BasicAttackDownLeft;
				dragon_states = AmazingDragonStates::ATTACK;
			}
		break; }
		case e1AmazingDragon::AmazingDragonStates::ATTACK: {
			if (current_animation->Finished()) {
				++auxiliar_attack_count;
				std::vector<iPoint> random_pos;
				App->entity_manager->FindFreeTileAround(App->scene->player->actual_tile, 8, &random_pos);
				for (uint i = 0; i < number_of_fire_balls; ++i) {
					iPoint pos = random_pos[App->random.Generate(0, random_pos.size() - 1)];
					e1Particles* fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, pos.x, pos.y, "");
					fire_ball->SetParticle(e1Particles::ParticleType::AMAZING_DRAGON_FIRE_BALL, direction, turns_to_wait_after_fire_ball);
					std::vector<iPoint>::iterator item = random_pos.begin();
					for (; item != random_pos.end(); ++item) {
						if ((*item) == pos) {
							random_pos.erase(item);
							break;
						}
					}
				}
				turn_done = true;
				dragon_states = AmazingDragonStates::WAIT_FIRE_BALLS;
				current_animation = &anim.IdleDownLeft;
				anim.BasicAttackDownLeft.Reset();
			}
			break; }
		case e1AmazingDragon::AmazingDragonStates::WAIT_FIRE_BALLS:
			if (turns_to_wait_after_fire_ball == auxiliar_turn_count) {
				auxiliar_turn_count = 0U;
				dragon_states = AmazingDragonStates::IDLE;
				turn_done = true;
			}
			else {
				++auxiliar_turn_count;
				turn_done = true;
			}
			break;
		case e1AmazingDragon::AmazingDragonStates::NONE:
			break;
		default:
			break;
		}

	}
	return true;
}

bool e1AmazingDragon::Update(float dt)
{

	if (active) {




	}
	return true;
}

void e1AmazingDragon::GetHitted(const int & dmg)
{
}

void e1AmazingDragon::IdAnimToEnum()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 8:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		}
	}
}
