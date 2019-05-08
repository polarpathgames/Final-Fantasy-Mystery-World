#include "e1Archer.h"
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
#include "m1MenuManager.h"
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
#include "m1Window.h"
#include "m1ParticleManager.h"

e1Archer::e1Archer(const int & x, const int & y) : e1Player(x, y)
{
	LoadEntityData("assets/entities/ArcherSpritesheet.tsx");

	SetPivot(8, 25);
	CenterPlayerInTile();
	InitStats();
}

e1Archer::~e1Archer()
{
}

bool e1Archer::CleanUp()
{
	return true;
}

void e1Archer::PrepareSpecialAttack1()
{
	BROFILER_CATEGORY("PrepareSpecialAttack1", Profiler::Color::Yellow);

	if (stats.mana - stats.cost_mana_special_attack1 >= 0 || god_mode == true) {
		if (!god_mode)
			ReduceMana(stats.cost_mana_special_attack1);
		App->audio->PlayFx(App->scene->fx_ability_archer);
		App->input->ControllerVibration(0.2F, 200);

		type_attack = Attacks::SPECIAL_1;
		state = State::ATTACKING;
		arrow = (e1Particles*)App->entity_manager->CreateEntity(e1Entity::EntityType::PARTICLE, actual_tile.x, actual_tile.y, "arrow");
		arrow->SetParticle(e1Particles::ParticleType::ARROW, direction);
	}
	else { // no enough mana so return to idle
		App->audio->PlayFx(App->scene->fx_ability_no_mana);
		state = State::IDLE;
	}
}

void e1Archer::SpecialAttack1()
{
	BROFILER_CATEGORY("ApecialAttack1", Profiler::Color::Yellow);

	std::vector<e1Entity*> item = App->entity_manager->GetEntities();
	if (std::find(item.begin(),item.end(),(e1Entity*)arrow) == item.end()) {
		arrow = nullptr;
		state = State::AFTER_ATTACK;
		ChangeAnimation(direction, state);
		time_attack = SDL_GetTicks();
	}
}

void e1Archer::IdAnimToEnum() //Assign every id animation to enum animation
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
		case 60:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;//
		case 63:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;//
		case 69:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;//
		case 84:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_LEFT_2;
			break;//
		case 90:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_RIGHT_2;
			break;//
		case 93:
			data.animations[i].animType = AnimationState::ABILITY_UP_RIGHT_2;
			break;//
		case 87:
			data.animations[i].animType = AnimationState::ABILITY_UP_LEFT_2;
			break;//
		case 102:
			data.animations[i].animType = AnimationState::ABILITY_LEFT_2;
			break;//
		case 99:
			data.animations[i].animType = AnimationState::ABILITY_UP_2;
			break;//
		case 105:
			data.animations[i].animType = AnimationState::ABILITY_RIGHT_2;
			break;//
		case 96:
			data.animations[i].animType = AnimationState::ABILITY_DOWN_2;
			break;//
		}

	}
}

void e1Archer::UpdateLevel()
{
	App->audio->PlayFx(App->scene->fx_controller_conection);
	stats.max_xp *= stats.level;
	AugmentLives(stats.max_lives*0.3f, true);
	AugmentMana(stats.max_mana*0.3f, true);
	App->particles->CreateExplosion(nullptr, nullptr, GetPosition() + iPoint{ 0,-15 }, { 8,0,2,2 }, RANDOM, { 20,20 }, { 10,5 }, { 0,0 }, P_UP, 200, 4, { 0,-2 });

	int mana = (int)stats.max_mana*0.3f;
	int life = (int)stats.max_lives*0.3f;

	iPoint pos{ 0,0 };
	pos.x = (int)(App->render->camera.x) + (position.x + pivot.x - 10) * (int)App->win->GetScale();
	pos.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos.x, pos.y, std::to_string(life).data(), App->gui->screen, GREEN, FontType::PMIX24);

	iPoint pos2{ 0,0 };
	pos2.x = (int)(App->render->camera.x) + (position.x + pivot.x + 10) * (int)App->win->GetScale();
	pos2.y = (int)(App->render->camera.y) + position.y * (int)App->win->GetScale();
	App->gui->AddHitPointLabel(pos2.x, pos2.y, std::to_string(mana).data(), App->gui->screen, BLUE, FontType::PMIX24);
	stats.max_lives += 5;
	stats.max_mana += 5;
	stats.attack_power += 2;
	stats.attack_power_ability_1 += 5;
	stats.attack_power_ability_3 += 5;


	App->menu_manager->hud.player_hp_bar->max_capacity = stats.max_lives;
	App->menu_manager->hud.player_mana_bar->max_capacity = stats.max_mana;
	App->menu_manager->hud.player_exp_bar->max_capacity = stats.max_xp;

	App->menu_manager->hud.player_hp_bar->PrintBarNumbers();
	App->menu_manager->hud.player_mana_bar->PrintBarNumbers();
}
