#include "e1StaticEntity.h"
#include "m1EntityManager.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1Cutscene.h"
#include "m1DialogSystem.h"
#include "m1FadeToBlack.h"
#include "m1Scene.h"
#include "m1Audio.h"
#include "m1Input.h"
#include "m1MenuManager.h"
#include "m1EasingSplines.h"
#include "Brofiler/Brofiler.h"
#include "m1GUI.h"
#include "m1Window.h"
#include "u1Image.h"
#include "m1Textures.h"

e1StaticEntity::e1StaticEntity(int x, int y, const char * name):e1Entity(x,y)
{
	BROFILER_CATEGORY("StaticEntity Constructor", Profiler::Color::Yellow);

	this->name.assign(name);

	if (strcmp(name,"flower") == 0) {
		static_type = e1StaticEntity::Type::FLOWER;
		has_animation = true;
		idle = DBG_NEW Animation();
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
	else if (strcmp(name, "furniture") == 0) {
		static_type = e1StaticEntity::Type::FURNITURE;
		frame = { 1070,0,64,40 };
		SetPivot(frame.w*0.5F, frame.h*1.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "door_home") == 0) {
		static_type = e1StaticEntity::Type::DOORHOME;
		frame = { 959,44,62,48 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "door_shop") == 0) {
		static_type = e1StaticEntity::Type::DOORSHOP;
		frame = { 1043,44,45,62 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
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
		frame = { 32,8,32,24 };
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
		idle = DBG_NEW Animation();
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
		idle = DBG_NEW Animation();
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
		actual_tile = { App->map->WorldToMap(position.x,position.y).x + 1,App->map->WorldToMap(position.x,position.y).y + 1 };
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 1;
	}
	else if (strcmp(name, "candle") == 0) {
		static_type = e1StaticEntity::Type::CANDLE;
		has_animation = true;
		idle = DBG_NEW Animation();
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
		idle = DBG_NEW Animation();
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
		if (App->dialog->dialogTrees[1]->karma == -1) {
			idle = new Animation();
			idle->PushBack({ 1141, 5,50,43 });
			frame = idle->frames[0];
			current_animation = idle;
			position = { position.x + 7, position.y + 5 };
		}
		else {
			idle = DBG_NEW Animation();
			current_animation = idle;
			idle->PushBack({ 160,0,64,48 });
			idle->PushBack({ 224,0,64,48 });
			idle->PushBack({ 160,48,64,48 });
			idle->PushBack({ 224,48,64,48 });
			idle->speed = 5;
			frame = idle->frames[0];
		}
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x + 1,App->map->WorldToMap(position.x,position.y).y + 1 };
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 3;
		CreateParticleFire(nullptr, nullptr, position + iPoint{int(frame.w*0.5f),0}, SDL_Rect{ 8,4,2,2 }, size, iPoint(12, 4), fPoint(0, -15), P_NON, 70, 2, true, W_NON);
		CreateParticleFire(nullptr, nullptr, position + iPoint{ int(frame.w*0.5f),0 }, SDL_Rect{ 8,2,2,2 }, size, iPoint(12, 4), fPoint(0, -15), P_NON, 30, 2, true, W_NON);
		
	}
	else if (strcmp(name, "NPC1") == 0) {
		static_type = e1StaticEntity::Type::NPC1;
		frame = { 1200, 0, 16, 28 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		position.x += 8;
		position.y -= 16;
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 1;
	}
	else if (strcmp(name, "NPC2") == 0) {
		static_type = e1StaticEntity::Type::NPC2;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1216,28,16,28 });
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "help1") == 0) {
		static_type = e1StaticEntity::Type::HELP1;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1219,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });
		idle->PushBack({ 1309,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });

		idle->speed = 1;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 28;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "help2") == 0) {
		static_type = e1StaticEntity::Type::HELP2;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1219,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });
		idle->PushBack({ 1309,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });

		idle->speed = 1;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 28;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "help3") == 0) {
		static_type = e1StaticEntity::Type::HELP3;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1219,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });
		idle->PushBack({ 1309,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });

		idle->speed = 1;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 28;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "help4") == 0) {
		static_type = e1StaticEntity::Type::HELP4;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1219,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });
		idle->PushBack({ 1309,80,45,48 });
		idle->PushBack({ 1264,80,45,48 });

		idle->speed = 1;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 28;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "NPC_DAUGHTER") == 0) {
		static_type = e1StaticEntity::Type::NPC_DAUGHTER;
		frame = { 1266,0,16,27 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		position.x += 8;
		position.y -= 16;
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 1;
	}
	//QUEST2
	else if (strcmp(name, "plant1_quest1") == 0) {
		static_type = e1StaticEntity::Type::PLANT1;
		frame = { 80,202,32,34 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "plant2_quest1") == 0) {
		static_type = e1StaticEntity::Type::PLANT2_Q1;
		frame = { 79,136,27,27 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "rock_quest1") == 0) {
		static_type = e1StaticEntity::Type::ROCK_Q1;
		frame = { 116,136,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "snow_elevation") == 0) {
		static_type = e1StaticEntity::Type::SNOW_ELEVATION;
		frame = { 7,209,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "rock_elevation") == 0) {
		static_type = e1StaticEntity::Type::ROCK_ELEVATION;
		frame = { 39,209,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree_quest1") == 0) {
		static_type = e1StaticEntity::Type::TREE_Q1;
		frame = { 189,176,29,57 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree2_quest1") == 0) {
		static_type = e1StaticEntity::Type::TREE2_Q1;
		frame = { 3,166,30,42 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "snow_man") == 0) {
		static_type = e1StaticEntity::Type::SNOW_MAN;
		frame = { 6,135,30,29 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "fire_wall_left") == 0) {
		static_type = e1StaticEntity::Type::FIREWALL_LEFT;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 293, 171,16,30 });
		idle->PushBack({ 313,171,16,30 });
		idle->PushBack({ 333,171,16,30 });
		idle->PushBack({ 353,171,16,30 });
		idle->speed = 3;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "fire_wall_right") == 0) {
		static_type = e1StaticEntity::Type::FIREWALL_RIGHT;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 386, 171,16,30 });
		idle->PushBack({ 406,171,16,30 });
		idle->PushBack({ 426,171,16,30 });
		idle->PushBack({ 446,171,16,30 });
		idle->speed = 3;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "fire_floor") == 0) {
		static_type = e1StaticEntity::Type::FIREFLOOR;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1330,160,37,57 });
		idle->PushBack({ 1380,160,37,57 });
		idle->PushBack({ 1430,160,37,57 });
		idle->PushBack({ 1480,160,37,57 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.6F, frame.h*0.9F);
		size.create(frame.w, frame.h);
		position.x += 10;
		position.y -= 2;
	}
	else if (strcmp(name, "fire_wall_special1") == 0) {
		static_type = e1StaticEntity::Type::SPECIAL_FIREWALL1;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1389,103,22,48 });
		idle->PushBack({ 1411,103,22,48 });
		idle->PushBack({ 1433,103,22,48 });
		idle->PushBack({ 1455,103,22,48 });
		idle->speed = 6;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "fire_wall_special2") == 0) {
		static_type = e1StaticEntity::Type::SPECIAL_FIREWALL2;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1480,119,35,40 });
		idle->PushBack({ 1515,119,35,40 });
		idle->PushBack({ 1550,119,35,40 });
		idle->PushBack({ 1585,119,35,40 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if ((strcmp(name, "treasure_1")) == 0 || (strcmp(name, "treasure_boss")) == 0 || (strcmp(name,"treasure_quest3")) == 0) {
		static_type = e1StaticEntity::Type::TREASURE;
		if (strcmp(name, "treasure_1") == 0)
			frame = { 156,137 ,35,32 };
		else if (strcmp(name, "treasure_boss") == 0)
			frame = { 195,137 ,35,32 };
		else if (strcmp(name, "treasure_quest3") == 0)
			frame = { 230,184 ,35,32 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {2, 1};
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 1;
	}
	else if (strcmp(name, "ability_base") == 0) {
		static_type = e1StaticEntity::Type::ABILITY_BASE;
		frame = { 1065,113 ,40,48 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "rocks_door") == 0) {
		static_type = e1StaticEntity::Type::CAVE_ROCKS;
		frame = { 682,174 ,26,49 };
		SetPivot(frame.w*0.5F, frame.h*0.5F);
		size.create(frame.w, frame.h);
		position.x -= 3;
		position.y += 1;
	}
	else if (strcmp(name, "blue_fire") == 0) {
		static_type = e1StaticEntity::Type::BLUE_FIRE;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 54,180,16,20 });
		idle->PushBack({ 89,180,16,20 });
		idle->PushBack({ 124,180,16,20 });
		idle->PushBack({ 159,180,16,20 });
		idle->speed = 3;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "p_fire") == 0) {
		static_type = e1StaticEntity::Type::PARTICLE;
		position += {4, 6};
		CreateParticleFire(this, nullptr, { 0,0 }, { 0,2,2,0 }, { 5, 2 }, { 12, 4 }, { 0, -15 }, P_NON, 30, 4, true, W_NON);
	}
	else if (strcmp(name, "water") == 0) {
		static_type = e1StaticEntity::Type::WATER;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1632,0,32,16 });
		idle->PushBack({ 1664,0,32,16 });
		idle->PushBack({ 1696,0,32,16 });
		idle->PushBack({ 1728,0,32,16 });
		idle->speed = 2;
		frame = idle->frames[0];
		SetPivot(frame.w*0.F, frame.h*0.F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "water2") == 0) {
		static_type = e1StaticEntity::Type::WATER2;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1632,16,32,16 });
		idle->PushBack({ 1664,16,32,16 });
		idle->PushBack({ 1696,16,32,16 });
		idle->PushBack({ 1728,16,32,16 });
		idle->speed = 2;
		frame = idle->frames[0];
		SetPivot(frame.w*0.F, frame.h*0.F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "water3") == 0) {
		static_type = e1StaticEntity::Type::WATER3;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1632,32,32,16 });
		idle->PushBack({ 1664,32,32,16 });
		idle->PushBack({ 1696,32,32,16 });
		idle->PushBack({ 1728,32,32,16 });
		idle->speed = 2;
		frame = idle->frames[0];
		SetPivot(frame.w*0.F, frame.h*0.F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "lava") == 0) {
		static_type = e1StaticEntity::Type::LAVA;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1632,48,32,16 });
		idle->PushBack({ 1664,48,32,16 });
		idle->PushBack({ 1696,48,32,16 });
		idle->PushBack({ 1728,48,32,16 });
		idle->speed = 2;
		frame = idle->frames[0];
		SetPivot(frame.w*0.F, frame.h*0.F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "ability_flash") == 0) {
		frame = { 1027,23,12,14 };
		SetPivot(frame.w*0.5F, frame.h*1.5F);
		size.create(frame.w, frame.h);
		static_type = e1StaticEntity::Type::FLASH_INFO;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		position.x += 14;
		position.y -= 9;
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 1;
	}
	else if (strcmp(name, "portal") == 0) {
		
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		interacting_state = InteractingStates::WAITING_INTERACTION;
		max_distance_to_interact = 2;
		static_type = e1StaticEntity::Type::PORTAL;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1630,142,43,67 });
		idle->PushBack({ 1673,142,43,67 });
		idle->PushBack({ 1716,142,43,67 });
		idle->PushBack({ 1759,142,43,67 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "portal_enter") == 0) {
		static_type = e1StaticEntity::Type::PORTAL;
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		idle->PushBack({ 1630,142,43,67 });
		idle->PushBack({ 1673,142,43,67 });
		idle->PushBack({ 1716,142,43,67 });
		idle->PushBack({ 1759,142,43,67 });
		idle->speed = 7;
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "best_friend") == 0) {
		static_type = e1StaticEntity::Type::BEST_FRIEND;
		frame = { 1299,29,16,28 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		position.x += 8;
		position.y -= 16;
	}
	else {
		LOG("Doesn't have any entity with name %s", name);
	}

	type = e1Entity::EntityType::STATIC;
	data.tileset.imagePath.assign("assets/maps/static_objects_tileset.png");
	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());
	
}

e1StaticEntity::~e1StaticEntity()
{
	if (idle != nullptr) {
		delete idle;
		idle = nullptr;
		current_animation = nullptr;
	}
	if (button_interact != nullptr) {
		App->gui->DeleteUIElement((u1GUI*)button_interact);
		button_interact = nullptr;
	}
}

void e1StaticEntity::Draw(float dt)
{
	if (has_animation) {
		App->render->Blit(data.tileset.texture, position.x, position.y, &current_animation->GetCurrentFrame(dt), true);
	}
	else {
		App->render->Blit(data.tileset.texture, position.x, position.y, &frame, true);
	}
	if (App->debug)
		App->render->Blit(App->scene->player->ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);

}

void e1StaticEntity::SetRect(int x, int y, int w, int h)
{
	frame = { x,y,w,h };
}

bool e1StaticEntity::Update(float dt)
{
	BROFILER_CATEGORY("StaticEntity Update", Profiler::Color::Yellow);
	//if (App->scene->player != nullptr)
	//{

	//}
	if (interacting_state == InteractingStates::NONE)
		return true;
	iPoint player_pos = App->map->WorldToMap(App->scene->player->position.x, App->scene->player->position.y + App->scene->player->pivot.y);
	if (interacting_state == InteractingStates::WAITING_INTERACTION) {
		if (actual_tile.DistanceTo(player_pos) <= max_distance_to_interact) {
			if (App->scene->GetMenuState() == StatesMenu::NO_MENU) {
				if (button_interact == nullptr) {
					button_interact = App->gui->AddImage(0, 0, { 1524,2052,31,31 }, nullptr, App->gui->screen, true, false, false, false);

					iPoint pos{ 0,0 };
					pos.x = (int)(App->render->camera.x) + (App->scene->player->GetPosition().x) * (int)App->win->GetScale() - button_interact->section.w*0.5F;
					pos.y = (int)(App->render->camera.y) + (App->scene->player->position.y) * (int)App->win->GetScale() - button_interact->section.h;

					button_interact->SetPos(pos.x, pos.y);
				}
				else {
					iPoint pos{ 0,0 };
					pos.x = (int)(App->render->camera.x) + (App->scene->player->GetPosition().x) * (int)App->win->GetScale() - button_interact->section.w*0.5F;
					pos.y = (int)(App->render->camera.y) + (App->scene->player->position.y) * (int)App->win->GetScale() - button_interact->section.h;
					button_interact->SetPos(pos.x, pos.y);
				}
				if ((static_type == Type::TREASURE) && App->entity_manager->ThereAreEnemies()) {
					if (button_interact != nullptr) {
						App->gui->DeleteUIElement((u1GUI*)button_interact);
						button_interact = nullptr;
					}
				}
				else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN && !App->cutscene_manager->is_executing && App->fade_to_black->current_step == m1FadeToBlack::fade_step::none) {
					App->scene->player->state = State::IDLE;
					App->easing_splines->CleanUp();
					App->scene->player->BlockControls(true);
					interacting_state = InteractingStates::INTERACTING;
					ChangeAnimation(player_pos);
					App->audio->PlayFx(App->scene->fx_writting);
					App->dialog->end_dial = false;
					App->audio->PlayFx(App->scene->fx_writting);
					//App->menu_manager->ShowHUD(false);
					App->gui->DeleteUIElement((u1GUI*)button_interact);
					button_interact = nullptr;
					App->scene->player->BlockControls(true);
					App->menu_manager->EnableHUD(false);

					if (static_type == Type::FOUNTAIN || static_type == Type::QUEST_FOUNTAIN) {
						App->menu_manager->CreateFountainBars();
					}
				}
			}
			
			}				
			else {
				if (button_interact != nullptr) {
					App->gui->DeleteUIElement((u1GUI*)button_interact);
					button_interact = nullptr;
				}
			}
	}
	if (interacting_state == InteractingStates::INTERACTING && App->dialog->end_dial)
	{
		interacting_state = InteractingStates::WAITING_INTERACTION;
		//if (static_type != Type::HELP1 && static_type != Type::HELP2 && static_type != Type::HELP3 && static_type != Type::FLASH_INFO)
			//App->menu_manager->ShowHUD(true);

		if (static_type == Type::FOUNTAIN || static_type == Type::QUEST_FOUNTAIN) {
			App->menu_manager->DestroyFountainBars();
		}
	}

	if (interacting_state == InteractingStates::INTERACTING) {
		switch (static_type) {
		case e1StaticEntity::Type::SHOP_MAN:
			if (App->scene->GetMenuState() == StatesMenu::SHOP_MENU || App->scene->GetMenuState() == StatesMenu::POTION_MENU || App->scene->GetMenuState() == StatesMenu::INVENTORY_MENU) {
				App->dialog->end_dial = true;
				interacting_state = InteractingStates::WAITING_INTERACTION;
			}
			else
				App->dialog->PerformDialogue(0);
			break;
		case e1StaticEntity::Type::QUEST_FOUNTAIN:
			App->dialog->PerformDialogue(1);
			break;
		case e1StaticEntity::Type::NPC1:
			App->dialog->PerformDialogue(2);
			break; 
		case e1StaticEntity::Type::PORTAL:
			App->dialog->PerformDialogue(11);
			break;
		case e1StaticEntity::Type::FEATHER:
			App->dialog->PerformDialogue(3);
			break;
		case e1StaticEntity::Type::TREASURE:
			if (frame == SDL_Rect{ 156, 137, 35, 32 }) {
				App->entity_manager->SpawnRupees(actual_tile.x, actual_tile.y, 20, 5, 0, 0, 0, 100);
				App->scene->player->BlockControls(false);
				App->globals.treasure_quest2_opened = true;
				App->menu_manager->EnableHUD(true);
				App->dialog->end_dial = true;
				frame = { 301,137 ,35,32 }; // need to put open treasure sprite
				interacting_state = InteractingStates::NONE;
			}
			else if (frame == SDL_Rect{ 195,137, 35, 32 }) {
				App->entity_manager->SpawnRupees(actual_tile.x, actual_tile.y, 5, 5, 30, 70, 0, 0);
				App->scene->player->BlockControls(false);
				App->globals.treasure_boss_opened = true;
				App->menu_manager->EnableHUD(true);
				App->dialog->end_dial = true;
				frame = { 335,137 ,35,32 }; // need to put open treasure sprite
				interacting_state = InteractingStates::NONE;
			}
			else if (frame == SDL_Rect{ 230,184, 35, 32 }) {
				App->entity_manager->SpawnRupees(actual_tile.x, actual_tile.y, 20, 5, 0, 0, 50, 50);
				App->scene->player->BlockControls(false);
				App->globals.treasure_quest3_opened = true;
				App->menu_manager->EnableHUD(true);
				App->dialog->end_dial = true;
				frame = { 301,137 ,35,32 }; // need to put open treasure sprite
				interacting_state = InteractingStates::NONE;
			}
			break;
		case e1StaticEntity::Type::HELP1:
			App->dialog->PerformDialogue(4);
			break;
		case e1StaticEntity::Type::HELP4:
			App->dialog->PerformDialogue(9);
			break;
		case e1StaticEntity::Type::HELP2:
			App->dialog->PerformDialogue(5);
			break;
		case e1StaticEntity::Type::HELP3:
			App->dialog->PerformDialogue(6);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			App->dialog->PerformDialogue(7);
			break;
		case e1StaticEntity::Type::FLASH_INFO:
			App->dialog->PerformDialogue(8);
			break;
		default:
			break;
		}
	}

	return true;
}


void e1StaticEntity::ChangeAnimation(const iPoint &player_pos)
{

	if (player_pos.x + 1 == actual_tile.x && player_pos.y == actual_tile.y) { // up left
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1232, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1283, 0, 16, 27);
			break;
		}
		
	}
	else if (player_pos.x == actual_tile.x && player_pos.y + 1 == actual_tile.y) { // up right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1248, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1317, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y == actual_tile.y) { // down right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1301, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x == actual_tile.x && player_pos.y - 1== actual_tile.y) { // down left
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1200, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1266, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x + 1== actual_tile.x && player_pos.y + 1 == actual_tile.y) { // up
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1248, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1283, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y + 1 == actual_tile.y) { // right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1301, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x + 1 == actual_tile.x && player_pos.y - 1 == actual_tile.y) { // left
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1200, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1266, 0, 16, 27);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y - 1 == actual_tile.y) { // down
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		case e1StaticEntity::Type::NPC_DAUGHTER:
			SetRect(1266, 0, 16, 27);
			break;
		}
	}


}

e1StaticEntity::InteractingStates e1StaticEntity::GetState()
{
	return interacting_state;
}

