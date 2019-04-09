#include "e1StaticEntity.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1Scene.h"
#include "m1Input.h"

e1StaticEntity::e1StaticEntity(int x, int y, const char * name):e1Entity(x,y)
{
	if (strcmp(name,"flower") == 0) {
		static_type = e1StaticEntity::Type::FLOWER;
		has_animation = true;
		idle = new Animation();
		current_animation = idle;
		idle->PushBack({ 132,103,24,21 });
		idle->PushBack({ 157,103,24,21 });
		idle->PushBack({ 182,103,24,21 });
		idle->PushBack({ 207,103,24,21 });
		idle->speed = 2;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "rock1") == 0) {
		static_type = e1StaticEntity::Type::ROCK1;
		frame = { 64,0,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "rock2") == 0) {
		static_type = e1StaticEntity::Type::ROCK2;
		frame = { 96,0,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree2") == 0) {
		static_type = e1StaticEntity::Type::TREE2;
		frame = { 96,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree3") == 0) {
		static_type = e1StaticEntity::Type::TREE3;
		frame = { 64,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "barrel") == 0) {
		static_type = e1StaticEntity::Type::BARREL;
		frame = { 32,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "streetlight") == 0) {
		static_type = e1StaticEntity::Type::STREETLIGHT;
		frame = { 0,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "plant1") == 0) {
		static_type = e1StaticEntity::Type::PLANT1;
		frame = { 80,32,48,32 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "plant2") == 0) {
		static_type = e1StaticEntity::Type::PLANT2;
		frame = { 32,32,38,32 };
		SetPivot(frame.w*0.5F, frame.h*0.75F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "red_plant") == 0) {
		static_type = e1StaticEntity::Type::RED_PLANT;
		frame = { 32,8,38,24 };
		SetPivot(frame.w*0.5F, frame.h*0.75F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "half_tree") == 0) {
		static_type = e1StaticEntity::Type::HALF_TREE;
		frame = { 1,13,30,35 };
		SetPivot(frame.w*0.5F, frame.h*0.75F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "fountain") == 0) {
		static_type = e1StaticEntity::Type::FOUNTAIN;
		has_animation = true;
		idle = new Animation();
		current_animation = idle;
		idle->PushBack({ 160,0,64,48 });
		idle->PushBack({ 224,0,64,48 });
		idle->PushBack({ 160,48,64,48 });
		idle->PushBack({ 224,48,64,48 });
		idle->speed = 5;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "house1") == 0) {
		static_type = e1StaticEntity::Type::HOUSE1;
		frame = { 401,11,86,87 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "shop") == 0) {
		static_type = e1StaticEntity::Type::SHOP;
		frame = { 291,11,106,95 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "house2") == 0) {
		static_type = e1StaticEntity::Type::HOUSE2;
		frame = { 498,11,70,79 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "home") == 0) {
		static_type = e1StaticEntity::Type::HOME;
		frame = { 577,11,96,95 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "floor") == 0) {
		static_type = e1StaticEntity::Type::FLOOR;
		frame = { 293,113,32,14 };
		SetPivot(frame.w*0.8F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "corner_floor") == 0) {
		static_type = e1StaticEntity::Type::CORNER_FLOOR;
		frame = { 325,113,32,14 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "corner") == 0) {
		static_type = e1StaticEntity::Type::CORNER;
		frame = { 261,113,32,14 };
		SetPivot(frame.w*0.2F, frame.h*0.2F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "shop_man") == 0) {
		static_type = e1StaticEntity::Type::SHOP_MAN;
		frame = { 80,32,48,32 };
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 2;
	}
	else {
		LOG("Doesn't have any entity with name %s", name);
	}

	type = e1Entity::EntityType::STATIC;
}

e1StaticEntity::~e1StaticEntity()
{
	if (idle != nullptr) {
		delete idle;
		idle = nullptr;
		current_animation = nullptr;
	}
}

void e1StaticEntity::Draw(SDL_Texture * tex, float dt)
{
	if (has_animation) {
		App->render->Blit(tex, position.x, position.y, &current_animation->GetCurrentFrame(dt), true);
	}
	else {
		App->render->Blit(tex, position.x, position.y, &frame, true);
	}
}

void e1StaticEntity::SetRect(int x, int y, int w, int h)
{
	frame = { x,y,w,h };
}

bool e1StaticEntity::Update(float dt)
{
	if (interacting_state == InteractingStates::NONE)
		return true;

	if (interacting_state == InteractingStates::WAITING_INTERACTION) {
		iPoint player_pos = App->map->WorldToMap(App->scene->player->position.x + App->scene->player->pivot.x, App->scene->player->position.y + App->scene->player->pivot.y);
		if (actual_tile.DistanceManhattan(player_pos) <= max_distance_to_interact) {
			if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
				interacting_state = InteractingStates::INTERACTING;
			}
		}
	}




	return true;
}

