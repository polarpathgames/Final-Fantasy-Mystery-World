#include "e1Drop.h"
#include "m1Scene.h"
#include "App.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "p2Rooms.h"
#include "p2Log.h"
#include "p2Math.h"
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
	else if (strcmp(name, "green_rupee") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GREEN_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1024,112,8,14 });
		idle->PushBack({ 1024,112,8,14 });
		idle->PushBack({ 1024,127,8,14 });
		idle->PushBack({ 1024,142,8,14 });
		idle->PushBack({ 1024,157,8,14 });
		idle->PushBack({ 1024,172,8,14 });
		idle->PushBack({ 1024,187,8,14 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
	}
	else if (strcmp(name, "InstaGreenRuppe") == 0) {
		insta_gem_pos = position;
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		drop_type = DropsType::GREEN_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1024,112,8,14 });
		idle->PushBack({ 1024,112,8,14 });
		idle->PushBack({ 1024,127,8,14 });
		idle->PushBack({ 1024,142,8,14 });
		idle->PushBack({ 1024,157,8,14 });
		idle->PushBack({ 1024,172,8,14 });
		idle->PushBack({ 1024,187,8,14 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
		gold = App->random.Generate(15, 25);
		is_insta_ruppe = true;
	}
	else if (strcmp(name, "blue_rupee") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::BLUE_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1033,112,8,14 });
		idle->PushBack({ 1033,112,8,14 });
		idle->PushBack({ 1033,127,8,14 });
		idle->PushBack({ 1033,142,8,14 });
		idle->PushBack({ 1033,157,8,14 });
		idle->PushBack({ 1033,172,8,14 });
		idle->PushBack({ 1033,187,8,14 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
	}
	else if (strcmp(name, "InstaBlueRuppe") == 0) {
		insta_gem_pos = position;
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		drop_type = DropsType::BLUE_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1033,112,8,14 });
		idle->PushBack({ 1033,112,8,14 });
		idle->PushBack({ 1033,127,8,14 });
		idle->PushBack({ 1033,142,8,14 });
		idle->PushBack({ 1033,157,8,14 });
		idle->PushBack({ 1033,172,8,14 });
		idle->PushBack({ 1033,187,8,14 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
		gold = App->random.Generate(45, 65);
		is_insta_ruppe = true;
	}
	else if (strcmp(name, "red_rupee") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::RED_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1042,112,10,18 });
		idle->PushBack({ 1042,112,10,18 });
		idle->PushBack({ 1042,131,10,18 });
		idle->PushBack({ 1042,151,10,18 });
		idle->PushBack({ 1042,169,10,18 });
		idle->PushBack({ 1042,188,10,18 });
		idle->PushBack({ 1042,207,10,18 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
	}
	else if (strcmp(name, "InstaRedRuppe") == 0) {
		insta_gem_pos = position;
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		drop_type = DropsType::RED_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1042,112,10,18 });
		idle->PushBack({ 1042,112,10,18 });
		idle->PushBack({ 1042,131,10,18 });
		idle->PushBack({ 1042,151,10,18 });
		idle->PushBack({ 1042,169,10,18 });
		idle->PushBack({ 1042,188,10,18 });
		idle->PushBack({ 1042,207,10,18 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
		gold = App->random.Generate(90, 110);
		is_insta_ruppe = true;
	}
	else if (strcmp(name, "gold_rupee") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GOLD_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1053,112,10,18 });
		idle->PushBack({ 1053,112,10,18 });
		idle->PushBack({ 1053,131,10,18 });
		idle->PushBack({ 1053,151,10,18 });
		idle->PushBack({ 1053,169,10,18 });
		idle->PushBack({ 1053,188,10,18 });
		idle->PushBack({ 1053,207,10,18 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
	}
	else if (strcmp(name, "InstaGoldRuppe") == 0) {
		insta_gem_pos = position;
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		drop_type = DropsType::GOLD_RUPEE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1053,112,10,18 });
		idle->PushBack({ 1053,112,10,18 });
		idle->PushBack({ 1053,131,10,18 });
		idle->PushBack({ 1053,151,10,18 });
		idle->PushBack({ 1053,169,10,18 });
		idle->PushBack({ 1053,188,10,18 });
		idle->PushBack({ 1053,207,10,18 });
		idle->speed = 9;
		frame = idle->frames[0];
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		CenterOnTile();
		gold = App->random.Generate(300, 400);
		is_insta_ruppe = true;
	}
	else if (strcmp(name, "ability1") == 0 && App->globals.ability1_gained == false) {
		drop_type = DropsType::ABILITY1;
		frame = { 1044,21,11,16 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		position.x += 8;
		position.y -= 13;
		moving = true;
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
		case DropsType::GREEN_RUPEE:
		case DropsType::BLUE_RUPEE:
		case DropsType::RED_RUPEE:
		case DropsType::GOLD_RUPEE:
		{
			App->audio->PlayFx(App->scene->fx_drop_pick_up);
			App->scene->player->AugmentGold(gold);
			if (!is_insta_ruppe)
				App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			else if (is_insta_ruppe)
				App->map->quest_rooms->AddEntityToNotRepeat(insta_gem_pos);
			to_delete = true;
			break;
		}
		case DropsType::ABILITY1:
		{
			App->globals.ability1_gained = true;
			App->scene->player->BlockControls(true);
			App->menu_manager->CreateHelpAbilityMenu(AbilityType::ABILITY1);
			//App->menu_manager->ShowHUD(false);
			App->scene->SetMenuState(StatesMenu::FIRSTABILITY_MENU);
			to_delete = true;
			break;
		}
		case DropsType::HEALTH_POTION:
		{
			App->scene->player->stats.num_hp_potions++;
			App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			App->audio->PlayFx(App->scene->fx_pick_up_poti);
			to_delete = true;
			break;
		}
		case DropsType::MANA_POTION:
		{
			App->scene->player->stats.num_mana_potions++;
			App->map->quest_rooms->DeleteDrop(actual_tile, drop_type);
			App->audio->PlayFx(App->scene->fx_pick_up_poti);
			to_delete = true;
			break;
		}
	  }
	}
	switch (drop_type) {
	case DropsType::ABILITY1:
		if (position.y > moving_pos.y - 13.0F && moving)
		{
			position = lerp(iPoint{ moving_pos.x,moving_pos.y + 13 }, iPoint{ moving_pos.x,moving_pos.y - 13 }, lerp_translation).AproximateToIntCast();
			lerp_translation += lerp_by;
			if (position.y <= moving_pos.y - 13.0F) {
				moving = false;
				lerp_translation = 0.0F;
			}
		}
		else if (position.y < moving_pos.y + 13.0F && !moving)
		{
			position = lerp(iPoint{ moving_pos.x,moving_pos.y - 13 }, iPoint{ moving_pos.x,moving_pos.y + 13 }, lerp_translation).AproximateToIntCast();
			lerp_translation += lerp_by;
			if (position.y >= moving_pos.y + 13.0F) {
				moving = true;
				lerp_translation = 0.0F;
			}
		}
		break;
	}
	
	return true;
}

void e1Drop::SetGold(const int & gold)
{
	this->gold = gold;
}

void e1Drop::FinishSpline()
{
	moving = false;
	actual_tile = moving_pos;
}

void e1Drop::SetSplineToFall() {
	App->easing_splines->CreateSpline(&position.y, (App->map->MapToWorldCentered(moving_pos.x+1, moving_pos.y) - pivot).y, 1000, TypeSpline::EASE_OUT_BOUNCE);
}
