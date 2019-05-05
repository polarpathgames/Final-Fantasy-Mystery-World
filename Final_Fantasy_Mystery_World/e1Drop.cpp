#include "e1Drop.h"
#include "m1Scene.h"
#include "App.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "p2Rooms.h"
#include "p2Log.h"
#include "Brofiler/Brofiler.h"
#include "m1Render.h"
#include "m1Map.h"
#include "m1MenuManager.h"

e1Drop::e1Drop(const int & x, const int & y, const char * name) : e1StaticEntity(x,y,name)
{

	if (strcmp(name, "gold") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GOLD_DROP;
		frame = { 1030,4,28,12 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();

	}
	else if (strcmp(name, "ability1") == 0 && App->globals.ability1_gained == false) {
		drop_type = DropsType::ABILITY1;
		frame = { 1044,21,11,16 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		position.x += 8;
		position.y -= 13;
		
		moving_pos.x = position.x;
		moving_pos.y = position.y;
	}
	else if (strcmp(name, "health_potion") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::HEALTH_POTION;
		frame = { 995,112,13,15 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();

	}
	else if (strcmp(name, "mana_potion") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::MANA_POTION;
		frame = { 1009,111,13,17 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();

	}
	original_position = position;
}

e1Drop::~e1Drop()
{
}

bool e1Drop::Update(float adt)
{
	BROFILER_CATEGORY("Drop Update", Profiler::Color::Yellow);

	if (actual_tile == App->scene->player->actual_tile) {
		switch (drop_type) {
		case DropsType::GOLD_DROP:
		{
			App->audio->PlayFx(App->scene->fx_drop_pick_up);
			App->scene->player->AugmentGold(gold);
			App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			to_delete = true;
			break;
		}
		case DropsType::ABILITY1:
		{
			App->globals.ability1_gained = true;
			App->scene->player->BlockControls(true);
			App->menu_manager->CreateHelpAbilityMenu();
			App->menu_manager->ShowHUD(false);
			App->scene->SetMenuState(StatesMenu::FIRSTABILITY_MENU);
			to_delete = true;
			break;
		}
		case DropsType::HEALTH_POTION:
		{
			App->scene->player->stats.num_hp_potions++;
			App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			to_delete = true;
			break;
		}
		case DropsType::MANA_POTION:
		{
			App->scene->player->stats.num_mana_potions++;
			App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			to_delete = true;
			break;
		}
	  }
	}
	switch (drop_type) {
	case DropsType::ABILITY1:
		/*if (position.y > moving_pos.y - 13.0F && moving)
		{
			position.y -= 100 * App->GetDeltaTime();
			if (position.y <= moving_pos.y - 13.0F)
				moving = false;
		}
		else if (position.y < moving_pos.y + 13.0F && !moving)
		{
			position.y += 100 * App->GetDeltaTime();
			if (position.y >= moving_pos.y + 13.0F)
				moving = true;
		}*/
		break;
	}
	
	return true;
}

void e1Drop::SetGold(const int & gold)
{
	this->gold = gold;
}
