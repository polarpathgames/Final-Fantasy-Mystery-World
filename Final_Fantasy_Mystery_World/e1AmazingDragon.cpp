#include "e1AmazingDragon.h"
#include "App.h"
#include "m1EntityManager.h"
#include "e1Player.h"
#include "m1Map.h"
#include "m1GUI.h"
#include "e1Particles.h"
#include "u1UI_Element.h"
#include "m1Window.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "m1Fonts.h"
#include "u1Bar.h"
#include "u1Label.h"
#include "m1MenuManager.h"

e1AmazingDragon::e1AmazingDragon(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/AmazingDragon.tsx");
	name.assign("AmazingDragon");
	enemy_type = EnemyType::AMAZING_DRAGON;

	SetPivot(30, 55);

	CenterOnTile();

	target_position = position;
	initial_position = position;
	position.x -= 35;
	position.y += 62;
	e1Enemy::InitStats();
	allow_turn = false;
	drawable = false;

	turns_to_wait_after_fire_ball = 2U;
	waves_before_recover_energy = 3U;
	turns_recovering_energy = 12U;
	number_of_fire_balls = 4U;
	turns_to_wait_before_attack_again = 8U;

	/*megadrake_hp_bar = App->gui->AddBar(100, 80, stats.max_live, ENEMYBAR, (u1GUI*)App->menu_manager->hud.bg_hud, nullptr);
	megadrake_label = App->gui->AddLabel(355, 20, "Mega Dragon", megadrake_hp_bar, BLACK, FontType::FF64, nullptr, false);*/

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
				App->map->data.no_walkables.pop_back();
				actual_tile = { 1000,1000 };
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
				App->audio->PlayFx(fx_ancient_drake_weak);
				current_animation = &anim.GoDownLeft;
				turn_done = true;
				App->map->data.no_walkables.push_back(iPoint{ 22,14 });
				actual_tile = { 22,15 };
			}
			else if (auxiliar_turn_count == turns_to_wait_before_attack_again) {
				current_animation = &anim.BasicAttackDownLeft;
				dragon_states = AmazingDragonStates::ATTACK;
				time.Start();
			}
			else {
				turn_done = true;
				++auxiliar_turn_count;
			}
		break; }
		case e1AmazingDragon::AmazingDragonStates::ATTACK: {
			if (1000 < time.Read()) {
				++auxiliar_attack_count;
				turn_done = true;
				dragon_states = AmazingDragonStates::WAIT_FIRE_BALLS;
				current_animation = &anim.IdleDownLeft;
				auxiliar_turn_count = 0U;
				anim.BasicAttackDownLeft.Reset();
			}
			// TODO App->audio->PlayFx(fx_fireball_ancient_dragon);
			break; }
		case e1AmazingDragon::AmazingDragonStates::WAIT_FIRE_BALLS:
			if (turns_to_wait_after_fire_ball == auxiliar_turn_count && !waiting_fire_balls) {
				std::vector<iPoint> random_pos;
				App->entity_manager->FindFreeTileAround(App->scene->player->actual_tile, 4, &random_pos);
				for (uint i = 0; i < number_of_fire_balls; ++i) {
					iPoint pos = random_pos[App->random.Generate(0, random_pos.size() - 1)];
					fire_ball = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, pos.x, pos.y, "");
					fire_ball->SetParticle(e1Particles::ParticleType::AMAZING_DRAGON_FIRE_BALL, direction, turns_to_wait_after_fire_ball);
					App->audio->PlayFx(fx_drake_throw);
					std::vector<iPoint>::iterator item = random_pos.begin();
					for (; item != random_pos.end(); ++item) {
						if ((*item) == pos) {
							random_pos.erase(item);
							break;
						}
					}
				}
				waiting_fire_balls = true;
			}
			else if (turns_to_wait_after_fire_ball == auxiliar_turn_count && waiting_fire_balls) {
				std::vector<e1Entity*> item = App->entity_manager->GetEntities();
				if (std::find(item.begin(), item.end(), (e1Entity*)fire_ball) == item.end()) {
					turn_done = true;
					waiting_fire_balls = false;
					auxiliar_turn_count = 0U;
					dragon_states = AmazingDragonStates::IDLE;
				}
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
	if (first_update == true && drawable == true) {
		megadrake_hp_bar = App->gui->AddBar(100, 80, stats.max_live, ENEMYBAR, (u1GUI*)App->menu_manager->hud.bg_hud, nullptr);
		megadrake_label = App->gui->AddLabel(355, 20, "Mega Dragon", megadrake_hp_bar, BLACK, FontType::FF64, nullptr, false);
		first_update = false;
	}
	if (active) {




	}
	return true;
}

void e1AmazingDragon::GetHitted(const int & dmg)
{
	App->audio->PlayFx(fx_ancient_drake_hit);

	stats.live -= dmg;
	times_hitted++;
	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 5) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(dmg).data(), App->gui->screen, RED, FontType::PMIX24);
	state = State::IDLE;
	App->audio->PlayFx(fx_enemy_hit);
	if (stats.live <= 0 || App->scene->player->god_mode) {
		state = State::DEATH;
		App->audio->PlayFx(fx_ancient_drake_dead);
		current_animation = &anim.DeathDownLeft;
		to_delete = true;
		App->gui->DeleteUIElement(megadrake_hp_bar);
	}
	megadrake_hp_bar->UpdateBar(-dmg, ENEMYBAR);
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
		case 10:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		}
	}
}
