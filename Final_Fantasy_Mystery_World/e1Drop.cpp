#include "e1Drop.h"
#include "m1Scene.h"
#include "App.h"
#include "e1Player.h"
#include "m1EntityManager.h"
#include "p2log.h"

e1Drop::e1Drop(const int & x, const int & y, const char * name) : e1StaticEntity(x,y,name)
{

	if (strcmp(name, "gold") == 0) {
		actual_tile = { x,y };
		drop_type = DropsType::GOLD_DROP;
		this->gold = gold;
	}
}

e1Drop::~e1Drop()
{
}

bool e1Drop::PreUpdate()
{
	if (actual_tile == App->scene->player->actual_tile) {
		switch (drop_type) {
		case DropsType::GOLD_DROP:
			App->scene->player->GiveGold(gold);
			LOG("PLAYER GOLD: %i", App->scene->player->stats.gold);
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
