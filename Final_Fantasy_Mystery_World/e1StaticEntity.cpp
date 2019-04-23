#include "e1StaticEntity.h"
#include "m1EntityManager.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"
#include "m1Audio.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1DialogSystem.h"
#include "m1Scene.h"
#include "m1Audio.h"
#include "m1Input.h"
#include "m1EasingSplines.h"
#include "Brofiler/Brofiler.h"
#include "m1GUI.h"
#include "m1Window.h"
#include "u1Image.h"

e1StaticEntity::e1StaticEntity(int x, int y, const char * name):e1Entity(x,y)
{
	BROFILER_CATEGORY("StaticEntity Constructor", Profiler::Color::Yellow);

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
		idle->PushBack({ 1215,27,16,28 });
		frame = idle->frames[0];
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "help1") == 0) {
		static_type = e1StaticEntity::Type::HELP1;
		frame = { 1219,63,45,65 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 8;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "help2") == 0) {
		static_type = e1StaticEntity::Type::HELP2;
		frame = { 1219,63,45,65 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 8;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
	}
	else if (strcmp(name, "help3") == 0) {
		static_type = e1StaticEntity::Type::HELP3;
		frame = { 1219,63,45,65 };
		SetPivot(frame.w*0.5F, frame.h*0.7F);
		size.create(frame.w, frame.h);
		max_distance_to_interact = 1;
		actual_tile = { App->map->WorldToMap(position.x,position.y).x,App->map->WorldToMap(position.x,position.y).y };
		actual_tile += {3, 3};
		position.y += 8;
		position.x += 2;
		interacting_state = InteractingStates::WAITING_INTERACTION;
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
	if (button_interact != nullptr) {
		App->gui->DeleteUIElement((u1GUI*)button_interact);
		button_interact = nullptr;
	}
}

void e1StaticEntity::Draw(SDL_Texture * tex, float dt)
{
	if (has_animation) {
		App->render->Blit(tex, position.x, position.y, &current_animation->GetCurrentFrame(dt), true);
	

	}
	else {
		App->render->Blit(tex, position.x, position.y, &frame, true);
		//App->render->Blit(App->scene->player->ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x + 1, App->map->MapToWorld(actual_tile.x, actual_tile.y).y - 8, NULL, true);
	}
}

void e1StaticEntity::SetRect(int x, int y, int w, int h)
{
	frame = { x,y,w,h };
}

bool e1StaticEntity::Update(float dt)
{
	BROFILER_CATEGORY("StaticEntity Update", Profiler::Color::Yellow);

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

				if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
					App->scene->player->state = State::IDLE;
					App->easing_splines->CleanUp();
					App->scene->player->BlockControls(true);
					interacting_state = InteractingStates::INTERACTING;
					ChangeAnimation(player_pos);
					App->audio->PlayFx(App->scene->fx_writting);
					App->dialog->end_dial = false;
					App->audio->PlayFx(App->scene->fx_writting);
					App->scene->ShowHUD(false);
					App->gui->DeleteUIElement((u1GUI*)button_interact);
					button_interact = nullptr;
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
		App->scene->ShowHUD(true);
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
		case e1StaticEntity::Type::FEATHER:
			App->dialog->PerformDialogue(3);
			break;
		case e1StaticEntity::Type::HELP1:
			App->dialog->PerformDialogue(4);
			break;
		case e1StaticEntity::Type::HELP2:
			App->dialog->PerformDialogue(5);
			break;
		case e1StaticEntity::Type::HELP3:
			App->dialog->PerformDialogue(6);
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
		}
	}
	else if (player_pos.x == actual_tile.x && player_pos.y + 1 == actual_tile.y) { // up right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1248, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y == actual_tile.y) { // down right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x == actual_tile.x && player_pos.y - 1== actual_tile.y) { // down left
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1200, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x + 1== actual_tile.x && player_pos.y + 1 == actual_tile.y) { // up
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1248, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y + 1 == actual_tile.y) { // right
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x + 1 == actual_tile.x && player_pos.y - 1 == actual_tile.y) { // left
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1200, 0, 16, 28);
			break;
		}
	}
	else if (player_pos.x - 1 == actual_tile.x && player_pos.y - 1 == actual_tile.y) { // down
		switch (static_type) {
		case e1StaticEntity::Type::NPC1:
			SetRect(1216, 0, 16, 28);
			break;
		}
	}


}

e1StaticEntity::InteractingStates e1StaticEntity::GetState()
{
	return interacting_state;
}

