#include "p2Rooms.h"
#include "m1Collisions.h"
#include "m1Map.h"
#include "m1FadeToBlack.h"
#include "App.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "m1EntityManager.h"
#include "m1Pathfinding.h"

Room::Room(const std::string &location, const int &id) 
{
	tmx_location = location;
	this->id = id;
}

Room::~Room()
{

	std::vector<ChangeScene*>::iterator item = change_scene_points.begin();
	for (; item != change_scene_points.end(); ++item) {
		delete (*item);
		(*item) = nullptr;
	}

}

RoomManager::RoomManager(pugi::xml_node &node)
{

	pugi::xml_node room_node; 

	for (room_node = node.child("maps").child("tutorial").child("room"); room_node; room_node = room_node.next_sibling("room")) {
		Room * r = nullptr;
		r = DBG_NEW Room(room_node.child("location").child_value(), room_node.child("id").attribute("num").as_int());
		rooms.push_back(r);
	}

	LoadRoom(1);

}

RoomManager::~RoomManager()
{
}

void RoomManager::OnCollision(Collider * c1, Collider * c2)
{
	iPoint pos_coll = { c1->rect.x,c1->rect.y };
	pos_coll = App->map->WorldToMap(pos_coll.x, pos_coll.y);
	
	if (App->scene->player->actual_tile == pos_coll) {
		std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
		switch (c1->type)
		{
		case COLLIDER_NEXT_A:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::NEXT_A) {
						actual_room->active = false;
						player_next_pos = LocationChangeScene::NEXT_A;
						LoadRoom((*item)->id_next_room);
						break;
					}
				}
			}
			break;
		case COLLIDER_LAST_A:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::LAST_A) {
						actual_room->active = false;
						player_next_pos = LocationChangeScene::LAST_A;
						LoadRoom((*item)->id_next_room);
						break;
					}
				}
			}
			break;
		case COLLIDER_NEXT_B:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::NEXT_B) {
						actual_room->active = false;
						player_next_pos = LocationChangeScene::NEXT_B;
						LoadRoom((*item)->id_next_room);
						break;
					}
				}
			}
			break;
		case COLLIDER_LAST_B:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::LAST_B) {
						actual_room->active = false;
						player_next_pos = LocationChangeScene::LAST_B;
						LoadRoom((*item)->id_next_room);
						break;
					}
				}
			}
			break;
		}
	}
	

}

void RoomManager::LoadRoom(const int & id)
{
	App->fade_to_black->FadeToBlack(0.5f);
	App->entity_manager->DeleteEntitiesNoPlayer();
	App->map->CleanUp();
	std::vector<Room*>::iterator item = rooms.begin();
	for (; item != rooms.end(); ++item) {
		if ((*item) != nullptr && (*item)->id == id) {
			App->map->Load((*item)->tmx_location.data());
			(*item)->active = true;
			actual_room = (*item);
			break;
		}
	}
	int w = 0, h = 0;
	uchar* data = nullptr;
	if (App->map->CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);
	
	App->scene->CreateEntities();
	PlacePlayer();
	LoadColliders();

}

void RoomManager::PlacePlayer() // place player in front of the door
{

	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->name == "player") {
			if ((*position)->ent_type == "lastA" && player_next_pos == LocationChangeScene::LAST_A) {
				App->scene->player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
			}
			else if ((*position)->ent_type == "lastB" && player_next_pos == LocationChangeScene::LAST_B) {
				App->scene->player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
			}
			else if ((*position)->ent_type == "nextA" && player_next_pos == LocationChangeScene::NEXT_A) {
				App->scene->player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
			}
			else if ((*position)->ent_type == "nextB" && player_next_pos == LocationChangeScene::NEXT_B) {
				App->scene->player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
			}
			else if ((*position)->ent_type == "default" && player_next_pos == LocationChangeScene::NONE) {
				App->scene->player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
			}
		}
	}
	App->scene->player->CenterPlayerInTile();
	App->render->CenterCameraOnPlayer(App->scene->player->position);
}

void RoomManager::LoadColliders() // sensors in the doors
{
	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->name == "room_collider") {
			if ((*position)->ent_type == "nextA") {
				std::vector<Room*>::iterator item = rooms.begin();
				for (; item != rooms.end(); ++item) {
					if ((*item) != nullptr && (*item)->active) {
						ChangeScene * c = DBG_NEW ChangeScene(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, LocationChangeScene::NEXT_A, (*position)->properties.GetValue("next_id"));
						(*item)->change_scene_points.push_back(c);
						App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_NEXT_A, (m1Module*)App->map);
						break;
					}
				}
			}
			if ((*position)->ent_type == "nextB") {
				std::vector<Room*>::iterator item = rooms.begin();
				for (; item != rooms.end(); ++item) {
					if ((*item) != nullptr && (*item)->active) {
						ChangeScene * c = DBG_NEW ChangeScene(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, LocationChangeScene::NEXT_B, (*position)->properties.GetValue("next_id"));
						(*item)->change_scene_points.push_back(c);
						App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_NEXT_B, (m1Module*)App->map);
						break;
					}
				}
			}
			if ((*position)->ent_type == "lastA") {
				std::vector<Room*>::iterator item = rooms.begin();
				for (; item != rooms.end(); ++item) {
					if ((*item) != nullptr && (*item)->active) {
						ChangeScene * c = DBG_NEW ChangeScene(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, LocationChangeScene::LAST_A, (*position)->properties.GetValue("next_id"));
						(*item)->change_scene_points.push_back(c);
						App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_LAST_A, (m1Module*)App->map);
						break;
					}
				}
			}
			if ((*position)->ent_type == "lastB") {
				std::vector<Room*>::iterator item = rooms.begin();
				for (; item != rooms.end(); ++item) {
					if ((*item) != nullptr && (*item)->active) {
						ChangeScene * c = DBG_NEW ChangeScene(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, LocationChangeScene::LAST_B, (*position)->properties.GetValue("next_id"));
						(*item)->change_scene_points.push_back(c);
						App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_LAST_B, (m1Module*)App->map);
						break;
					}
				}
			}
		}
	}
	

}

ChangeScene::ChangeScene(const int & x, const int & y, LocationChangeScene type, const uint & id)
{
	location = { x,y };
	location = App->map->WorldToMap(location.x, location.y);
	change_type = type;
	id_next_room = id;
}
