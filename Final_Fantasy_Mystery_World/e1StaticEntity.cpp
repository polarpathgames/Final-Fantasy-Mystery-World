#include "e1StaticEntity.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1DialogSystem.h"
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
		frame = { 291,0,106,111 };
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
	else if (strcmp(name, "quest_tree1") == 0) {
		static_type = e1StaticEntity::Type::QUEST_TREE1;
		frame = { 817,0,34,74 };
		SetPivot(frame.w*0.2F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "quest_tree2") == 0) {
		static_type = e1StaticEntity::Type::QUEST_TREE2;
		frame = { 853,0,32,80 };
		SetPivot(frame.w*0.2F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "quest_tree3") == 0) {
		static_type = e1StaticEntity::Type::QUEST_TREE3;
		frame = { 886,0,32,72 };
		SetPivot(frame.w*0.2F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "quest_tree4") == 0) {
		static_type = e1StaticEntity::Type::QUEST_TREE4;
		frame = { 922,0,32,89 }; 
		SetPivot(frame.w*0.2F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree1") == 0) {
		static_type = e1StaticEntity::Type::TREE1;
		frame = { 128,10,31,54 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "piece_shop") == 0) {
		static_type = e1StaticEntity::Type::PIECE_SHOP;
		frame = { 960,0,64,32 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "feather") == 0) {
		static_type = e1StaticEntity::Type::FEATHER;
		has_animation = true;
		idle = new Animation();
		current_animation = idle;
		idle->PushBack({ 686,3,8,27 });
		idle->PushBack({ 698,3,8,27 });
		idle->PushBack({ 710,3,8,27 });
		idle->PushBack({ 722,3,8,27 });
		idle->PushBack({ 734,3,8,27 });
		idle->PushBack({ 746,3,8,27 });
		idle->PushBack({ 758,3,8,27 });
		idle->PushBack({ 770,3,8,27 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "candle") == 0) {
		static_type = e1StaticEntity::Type::CANDLE;
		has_animation = true;
		idle = new Animation();
		current_animation = idle;
		idle->PushBack({ 686,42,28,32 });
		idle->PushBack({ 720,42,28,32 });
		idle->PushBack({ 753,42,28,32 });
		idle->PushBack({ 786,42,28,32 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
  }
	else if (strcmp(name, "shop_man_place") == 0) {
		static_type = e1StaticEntity::Type::SHOP_MAN;
		has_animation = true;
		idle = new Animation();
		current_animation = idle;
		idle->PushBack({ 686,82,32,32 });
		idle->PushBack({ 718,82,32,32 });
		idle->speed = 0.8F;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x + 1,App->map->WorldToMap(position.x,position.y).y + 1};
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 3;
	}
	else if (strcmp(name, "quest_fountain") == 0) {
		static_type = e1StaticEntity::Type::QUEST_FOUNTAIN;
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
		App->render->Blit(App->scene->player->ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

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
	iPoint player_pos = App->map->WorldToMap(App->scene->player->position.x, App->scene->player->position.y + App->scene->player->pivot.y);
	if (interacting_state == InteractingStates::WAITING_INTERACTION) {	
		if (actual_tile.DistanceManhattan(player_pos) <= max_distance_to_interact) {
			if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
				interacting_state = InteractingStates::INTERACTING;
				App->dialog->end_dial = false;
			}
		}			
	}
	if (interacting_state == InteractingStates::INTERACTING && actual_tile.DistanceManhattan(player_pos) > max_distance_to_interact || App->dialog->end_dial)
	{
		App->dialog->DeleteText();
		App->dialog->waiting_input = false;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}

	if (interacting_state == InteractingStates::INTERACTING) {
		switch (static_type) {
		case e1StaticEntity::Type::SHOP_MAN:
			App->dialog->PerformDialogue(0);
			break;
		case e1StaticEntity::Type::QUEST_FOUNTAIN:
			App->dialog->PerformDialogue(1);
			break;
		default:
			break;
		}
	}
	DebugDrawRangeInteractive();


	return true;
}
void e1StaticEntity::DebugDrawRangeInteractive()
{
	iPoint pos = App->map->MapToWorld(actual_tile.x, actual_tile.y);
	App->render->DrawCircle(pos.x + pivot.x*1.5f, pos.y + pivot.y/5, 90, 255, 255, 255,255,true);

}

e1StaticEntity::InteractingStates e1StaticEntity::GetState()
{
	return interacting_state;
}
