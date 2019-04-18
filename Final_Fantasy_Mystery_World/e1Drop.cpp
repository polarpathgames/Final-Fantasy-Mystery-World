#include "e1Drop.h"
#include "m1Scene.h"
#include "App.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "p2log.h"
#include "m1Render.h"
#include "m1Map.h"

e1Drop::e1Drop(const int & x, const int & y, const char * name) : e1StaticEntity(x,y,name)
{

	if (strcmp(name, "gold") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GOLD_DROP;
		frame = { 1030,4,28,12 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		position = App->map->MapToWorld(actual_tile.x, actual_tile.y);
	}
	else if (strcmp(name, "ability1") == 0) {
		drop_type = DropsType::ABILITY1;
		frame = { 1044,21,11,16 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x, position.y) };
		position.x += 12;
		position.y -= 4;
	}
}

e1Drop::~e1Drop()
{
}

bool e1Drop::Update(float adt)
{
	if (actual_tile == App->scene->player->actual_tile) {
		switch (drop_type) {
		case DropsType::GOLD_DROP:
		{
			App->audio->PlayFx(App->scene->fx_drop_pick_up);
			App->scene->player->AugmentGold(gold);
			to_delete = true;
			break;
		}
		case DropsType::ABILITY1:
		{
			App->scene->player->BlockControls(true);
			App->audio->PlayFx(App->scene->fx_drop_pick_up);
			App->scene->CreateFirstAbilityPanel();
			App->scene->SetMenuState(StatesMenu::FIRSTABILITY_MENU);
			to_delete = true;
			break;
		}
		}
	}


	return true;
}

void e1Drop::SetGold(const int & gold)
{
	this->gold = gold;
}
