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

e1Archer::e1Archer(const int & x, const int & y) : e1Player(x, y)
{
	LoadEntityData("assets/entities/Warrior.tsx");

	ground = App->tex->Load("assets/sprites/player_pos.png");

	CenterPlayerInTile();
}

e1Archer::~e1Archer()
{
}

bool e1Archer::PreUpdate()
{

	if (!block_controls)
		ReadPlayerInput();

	return true;
}

bool e1Archer::Update(float dt)
{

	PerformActions(dt);

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

	if (coll != nullptr)
		coll->SetPos(position.x, position.y + 25);

	return true;
}

bool e1Archer::PostUpdate()
{
	return true;
}

bool e1Archer::CleanUp()
{
	App->tex->UnLoad(ground);
	ground = nullptr;
	return true;
}

void e1Archer::InitStats()
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