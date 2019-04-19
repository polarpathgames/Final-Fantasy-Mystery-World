#include "p2Rooms.h"
#include "m1Collisions.h"
#include "m1Map.h"
#include "m1FadeToBlack.h"
#include "App.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1DialogSystem.h"
#include "GlobalGameAdvances.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "e1Rock.h"
#include "SDL/include/SDL.h"
#include "m1Cutscene.h"
#include "m1EntityManager.h"
#include "m1Pathfinding.h"

Room::Room(const std::string &tmx_location, const int &id, const std::string &type, const std::string &cutscene_location)
{
	this->tmx_location = tmx_location;
	this->id = id;

	if (!cutscene_location.empty()) {
		this->cutscene_location = cutscene_location;
	}

	if (strcmp(type.data(), "paceful") == 0) {
		room_type = RoomType::PACEFUL;
	}
	else if (strcmp(type.data(), "combat") == 0) {
		room_type = RoomType::COMBAT;
	}
	else if (strcmp(type.data(), "boss") == 0) {
		room_type = RoomType::BOSS;
	}
	else if (strcmp(type.data(), "fountain") == 0) {
		room_type = RoomType::FOUNTAIN;
		App->dialog->dialogTrees[1]->karma = 0;
	}
}

Room::~Room()
{

	std::vector<ChangeScene*>::iterator item = change_scene_points.begin();
	for (; item != change_scene_points.end(); ++item) {
		delete (*item);
		(*item) = nullptr;
	}
	entities.clear();
}

RoomManager::RoomManager(pugi::xml_node &node)
{

	pugi::xml_node room_node;

	for (room_node = node.child("maps").child("tutorial").child("room"); room_node; room_node = room_node.next_sibling("room")) {
		Room * r = nullptr;
		r = DBG_NEW Room(room_node.child("location").child_value(), room_node.child("id").attribute("num").as_int(), room_node.child("type").child_value(), room_node.child("cut_scene").child_value());
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

	if (App->scene->player->actual_tile == pos_coll && actual_room->active) {
		std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
		switch (c1->type)
		{
		case COLLIDER_NEXT_A:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::NEXT_A) {
						App->scene->player->BlockControls(true);
						actual_room->active = false;
						last_room = actual_room;
						player_next_pos = LocationChangeScene::NEXT_A;
						std::vector<Room*>::iterator item2 = rooms.begin();
						for (; item2 != rooms.end(); ++item2) {
							if ((*item) != nullptr && (*item2)->id == (*item)->id_next_room) {
								actual_room = (*item2);
								break;
							}
						}
						App->fade_to_black->FadeToBlack(true, 0.5f);
						App->audio->PlayFx(App->scene->fx_door_enter);
						break;
					}
				}
			}
			break;
		case COLLIDER_LAST_A:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::LAST_A) {
						App->scene->player->BlockControls(true);
						actual_room->active = false;
						last_room = actual_room;
						player_next_pos = LocationChangeScene::LAST_A;
						std::vector<Room*>::iterator item2 = rooms.begin();
						for (; item2 != rooms.end(); ++item2) {
							if ((*item) != nullptr && (*item2)->id == (*item)->id_next_room) {
								actual_room = (*item2);
								break;
							}
						}
						App->fade_to_black->FadeToBlack(true, 0.5f);
						App->audio->PlayFx(App->scene->fx_door_enter);
						break;
					}
				}
			}
			break;
		case COLLIDER_NEXT_B:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::NEXT_B) {
						App->scene->player->BlockControls(true);
						actual_room->active = false;
						last_room = actual_room;
						player_next_pos = LocationChangeScene::NEXT_B;
						std::vector<Room*>::iterator item2 = rooms.begin();
						for (; item2 != rooms.end(); ++item2) {
							if ((*item) != nullptr && (*item2)->id == (*item)->id_next_room) {
								actual_room = (*item2);
								break;
							}
						}
						App->fade_to_black->FadeToBlack(true, 0.5f);
						App->audio->PlayFx(App->scene->fx_door_enter);
						break;
					}
				}
			}
			break;
		case COLLIDER_LAST_B:
			for (; item != actual_room->change_scene_points.end(); ++item) {
				if ((*item) != nullptr) {
					if ((*item)->change_type == LocationChangeScene::LAST_B) {
						App->scene->player->BlockControls(true);
						actual_room->active = false;
						last_room = actual_room;
						player_next_pos = LocationChangeScene::LAST_B;
						std::vector<Room*>::iterator item2 = rooms.begin();
						for (; item2 != rooms.end(); ++item2) {
							if ((*item) != nullptr && (*item2)->id == (*item)->id_next_room) {
								actual_room = (*item2);
								break;
							}
						}
						App->fade_to_black->FadeToBlack(true, 0.5f);
						App->audio->PlayFx(App->scene->fx_door_enter);
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

	LoadEntities();
	PlacePlayer();
	LoadColliders();
	PlayMusic();
	PlayCutScene();
}

void RoomManager::LoadEntities()
{
	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->ent_type == "static") {
			if ((*position)->name == "rock") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
				else {
					e1Rock* rock = (e1Rock*)App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					rock->frame = { 955,91,32,37 };
					App->map->data.no_walkables.remove(rock->actual_tile + iPoint{ 0,-1 });
				}
			}
			else if ((*position)->name == "ability1") {
				App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}
			else
				App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->name == "enemy") {
			if ((*position)->ent_type == "CarnivorousPlant") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::CARNIVOROUS_PLANT, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
			}
			else if ((*position)->ent_type == "BlueDog") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_DOG, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
			}
			else if ((*position)->ent_type == "StrangeFrog") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(),actual_room->entities.end(),point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::STRANGE_FROG, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
			}
		}
	}
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
	App->scene->player->Init();
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

void RoomManager::PlayMusic()
{
	// ROOM TYPE
	if (last_room == nullptr || (last_room->room_type != actual_room->room_type)) {
		switch (actual_room->room_type)
		{
		case RoomType::PACEFUL:
			App->audio->PlayMusic("assets/audio/music/6.Final Fantasy TA - Unhideable Anxiety.ogg", 5);
			break;
		case RoomType::FOUNTAIN:
			App->audio->PlayMusic("assets/audio/music/5.Final Fantasy TA - Crystal.ogg", 0.5);
			break;
		case RoomType::COMBAT:
			App->audio->PlayMusic("assets/audio/music/20.Final Fantasy TA - Painful Battle.ogg", 0.5);
			break;
		case RoomType::BOSS:
			App->audio->PlayMusic("assets/audio/music/39.Final Fantasy TA - Incarnation.ogg", 0.5);
			break;
		default:
			App->audio->PlayMusic("assets/audio/music/6.Final Fantasy TA - Unhideable Anxiety.ogg", 5);
			break;
		}
	}
}

void RoomManager::PlayCutScene()
{
	if (!actual_room->cutscene_location.empty()) {
		App->scene->player->BlockControls(true);
		if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneTutorial.xml") == 0 && !CutSceneTutorialGirlEscapingPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			CutSceneTutorialGirlEscapingPlayed = true;
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneFinalRoom.xml") == 0 && !CutSceneFinalRoomTutorialPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			CutSceneFinalRoomTutorialPlayed = true;
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneMiddleRoom.xml") == 0 && !CutSceneMiddleRoomTutorialPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			CutSceneFinalRoomTutorialPlayed = true;
		}
	}
		
}

void RoomManager::AddEntityToNotRepeat(iPoint pos)
{
	actual_room->entities.push_back(pos);
}

ChangeScene::ChangeScene(const int & x, const int & y, LocationChangeScene type, const uint & id)
{
	location = { x,y };
	location = App->map->WorldToMap(location.x, location.y);
	change_type = type;
	id_next_room = id;
}
