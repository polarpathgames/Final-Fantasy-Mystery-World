#include "e1Drop.h"
#include "m1Scene.h"
#include "App.h"
#include "e1Player.h"
#include "m1EntityManager.h"
#include "p2log.h"
#include "m1Map.h"

e1Drop::e1Drop(const int & x, const int & y, const char * name) : e1StaticEntity(x,y,name)
{

	if (strcmp(name, "gold") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GOLD_DROP;
		this->gold = gold;
		frame = { 80,32,48,32 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		position = App->map->MapToWorld(actual_tile.x, actual_tile.y);
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
			App->scene->player->GiveGold(gold);
			to_delete = true;
			break;
		}
	}

	return true;
}

void e1Drop::SetGold(const int & gold)
{
	this->gold = gold;
}
