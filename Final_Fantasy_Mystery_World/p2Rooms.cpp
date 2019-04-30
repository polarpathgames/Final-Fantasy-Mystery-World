#include "p2Rooms.h"
#include "m1Collisions.h"
#include "m1Map.h"
#include "m1FadeToBlack.h"
#include "App.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1Input.h"
#include "u1Image.h"
#include "m1DialogSystem.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "e1Rock.h"
#include "m1Window.h"
#include "SDL/include/SDL.h"
#include "m1Cutscene.h"
#include "m1EntityManager.h"
#include "m1GUI.h"
#include "m1Pathfinding.h"

Room::Room(const std::string &tmx_location, const uint &id, const std::string &type, const std::string &cutscene_location, bool door_closed, const uint &update_number)
{
	this->tmx_location = tmx_location;
	this->id = id;
	this->door_closed = door_closed;
	this->update_number = update_number;

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
	change_scene_points.clear();

	std::vector<MapIndicators*>::iterator it = map_indicators.begin();
	for (; it != map_indicators.end(); ++it) {
		if ((*it) != nullptr) {
			if ((*it)->indicator_image != nullptr)
				(*it)->indicator_image->to_delete = true;
			delete (*it);
			(*it) = nullptr;
		}

	}
	map_indicators.clear();

	entities.clear();
}

RoomManager::RoomManager(const char* name)
{

	mus_paceful = App->audio->LoadMusic("assets/audio/music/6.Final Fantasy TA - Unhideable Anxiety.ogg");
	mus_combat = App->audio->LoadMusic("assets/audio/music/20.Final Fantasy TA - Painful Battle.ogg");
	mus_boss = App->audio->LoadMusic("assets/audio/music/39.Final Fantasy TA - Incarnation.ogg");
	mus_fountain = App->audio->LoadMusic("assets/audio/music/5.Final Fantasy TA - Crystal.ogg");

	pugi::xml_parse_result result = room_manager_file.load_file("assets/xml/Rooms.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", "assets/xml/Rooms.xml", result.description());
	}
	else {
		LOG("XML was loaded succesfully!");

		map_background = App->gui->AddImage(100, 100, { 200,1736,(int)App->win->width - 200, (int)App->win->height - 200 }, nullptr, App->gui->screen, false, false, false, false);

		for (pugi::xml_node room_node = room_manager_file.child("room_manager").child(name).child("room"); room_node; room_node = room_node.next_sibling("room")) {
			Room * r = DBG_NEW Room(room_node.child("location").child_value(), room_node.child("id").attribute("num").as_uint(), room_node.child("type").child_value(),
				room_node.child("cut_scene").child_value(), room_node.child("door").attribute("active").as_bool(false), room_node.child("update").attribute("num").as_uint(0u));
			rooms.push_back(r);
		}

		LoadRoom(1);
		actual_room->map_room_image = App->gui->AddImage(125, 125, { 1317,2170,128,64 }, nullptr, (u1GUI*)map_background, false, false, false, false);
	}

	room_manager_file.reset();
}

RoomManager::~RoomManager()
{
	map_background->to_delete = true;
}

void RoomManager::OnCollision(Collider * c1, Collider * c2)
{
	iPoint pos_coll = { c1->rect.x,c1->rect.y };
	pos_coll = App->map->WorldToMap(pos_coll.x, pos_coll.y);

	if (App->scene->player->actual_tile == pos_coll)
		ChangeRoom(c1->type, false);


}

bool RoomManager::ChangeRoom(COLLIDER_TYPE type, bool debug_pass)
{
	bool ret = false;
	if (actual_room != nullptr) {
		if ((actual_room->active && !actual_room->door_closed) || debug_pass) {
			std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
			switch (type)
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
							ret = true;
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
							ret = true;
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
							ret = true;
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
							ret = true;
							break;
						}
					}
				}
				break;
			}
		}
	}
	return ret;
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
			actual_room->active = true;
			break;
		}
	}
	int w = 0, h = 0;
	uchar* data = nullptr;
	if (App->map->CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);

	LoadColliders();
	UpdateMap();
	LoadEntities();
	PlacePlayer();
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
					rock->hitted = true;
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
					std::vector<MapIndicators*>::iterator item = actual_room->map_indicators.begin();
					bool created = false;
					for (; item != actual_room->map_indicators.end(); ++item) {
						if ((*item) != nullptr) {
							if ((*item)->location == point) {
								created = true;
								break;
							}
						}
					}
					if (!created) {
						MapIndicators* indicator = DBG_NEW MapIndicators(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, "enemy", App->gui->AddImage(0, 0, { 1392,2123,13,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
						actual_room->map_indicators.push_back(indicator);
					}
				}
			}
			else if ((*position)->ent_type == "BlueDog") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::BLUE_DOG, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					std::vector<MapIndicators*>::iterator item = actual_room->map_indicators.begin();
					bool created = false;
					for (; item != actual_room->map_indicators.end(); ++item) {
						if ((*item) != nullptr) {
							if ((*item)->location == point) {
								created = true;
								break;
							}
						}
					}
					if (!created) {
						MapIndicators* indicator = DBG_NEW MapIndicators(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, "enemy", App->gui->AddImage(0, 0, { 1392,2123,13,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
						actual_room->map_indicators.push_back(indicator);
					}
				}
			}
			else if ((*position)->ent_type == "StrangeFrog") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(),actual_room->entities.end(),point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::STRANGE_FROG, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					std::vector<MapIndicators*>::iterator item = actual_room->map_indicators.begin();
					bool created = false;
					for (; item != actual_room->map_indicators.end(); ++item) {
						if ((*item) != nullptr) {
							if ((*item)->location == point) {
								created = true;
								break;
							}
						}
					}
					if (!created) {
						MapIndicators* indicator = DBG_NEW MapIndicators(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, "enemy", App->gui->AddImage(0, 0, { 1392,2123,13,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
						actual_room->map_indicators.push_back(indicator);
					}
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

void RoomManager::LoadColliders() // colliders in the doors
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
						if (!actual_room->door_closed) {
							App->map->data.no_walkables.remove(c->location + iPoint{ 0,-1 });
						}
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
						if (!actual_room->door_closed) {
							App->map->data.no_walkables.remove(c->location + iPoint{ 0,-1 });
						}
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
			App->audio->PlayMusic(mus_paceful, 5);
			break;
		case RoomType::FOUNTAIN:
			App->audio->PlayMusic(mus_fountain, 0.5);
			break;
		case RoomType::COMBAT:
			App->audio->PlayMusic(mus_combat, 0.5);
			break;
		case RoomType::BOSS:
			App->audio->PlayMusic(mus_boss, 0.5);
			break;
		default:
			App->audio->PlayMusic(mus_paceful, 5);
			break;
		}
	}
}

void RoomManager::PlayCutScene()
{
	if (!actual_room->cutscene_location.empty()) {
		App->scene->player->BlockControls(true);
		if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneTutorial.xml") == 0 && !App->globals.CutSceneTutorialGirlEscapingPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			App->globals.CutSceneTutorialGirlEscapingPlayed = true;
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneFinalRoom.xml") == 0 && !App->globals.CutSceneFinalRoomTutorialPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneMiddleRoom.xml") == 0 && !App->globals.CutSceneMiddleRoomTutorialPlayed) {
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			App->globals.CutSceneMiddleRoomTutorialPlayed = true;
		}
	}
		
}

void RoomManager::UpdateMap()
{
	if (actual_room->id != 1 && actual_room->map_room_image == nullptr) {
		if (player_next_pos == LocationChangeScene::NEXT_A) {
			if (actual_room->change_scene_points.size() >= 3) { // it has 2 new doors
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1573,2170,128,64 }, nullptr, map_background, false, false, false, false);
			}
			else if (actual_room->change_scene_points.size() == 1) { // no new doors, just an exit door 
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1702,2170,128,64 }, nullptr, map_background, false, false, false, false);
			}
			else { // it has one new door 
				std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
				for (; item != actual_room->change_scene_points.end(); ++item) {
					if ((*item) != nullptr) {
						if ((*item)->change_type == LocationChangeScene::NEXT_A) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1317,2170,128,64 }, nullptr, map_background, false, false, false, false);
							break;
						}
						else if ((*item)->change_type == LocationChangeScene::NEXT_B) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1445,2170,128,64 }, nullptr, map_background, false, false, false, false);
							break;
						}
					}
				}
			}
		}
		else if (player_next_pos == LocationChangeScene::NEXT_B) {
			if (actual_room->change_scene_points.size() >= 3) { // it has 2 new doors
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1573,2170,128,64 }, nullptr, map_background, false, false, false, false);
			}
			else if (actual_room->change_scene_points.size() == 1) { // no new doors, just an exit door 
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1702,2170,128,64 }, nullptr, map_background, false, false, false, false);
			}
			else { // it has one new door 
				std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
				for (; item != actual_room->change_scene_points.end(); ++item) {
					if ((*item) != nullptr) {
						if ((*item)->change_type == LocationChangeScene::NEXT_A) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1317,2170,128,64 }, nullptr, map_background, false, false, false, false);
							break;
						}
						else if ((*item)->change_type == LocationChangeScene::NEXT_B) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, { 1445,2170,128,64 }, nullptr, map_background, false, false, false, false);
							break;
						}
					}
				}
			}
		}
		if (actual_room->room_type == RoomType::FOUNTAIN) {
			if (actual_room->map_indicators.size() == 0) {
				MapIndicators* indicator = DBG_NEW MapIndicators(0, 0, "fountain", App->gui->AddImage(0, 0, { 1405,2123,13,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
				actual_room->map_indicators.push_back(indicator);
			}
		}
	}
}

void RoomManager::AddEntityToNotRepeat(iPoint pos)
{
	actual_room->entities.push_back(pos);

	std::vector<MapIndicators*>::iterator item = actual_room->map_indicators.begin();
	for (; item != actual_room->map_indicators.end(); ++item) {
		if ((*item) != nullptr && (*item)->indicator_image != nullptr && pos == (*item)->location) {
			(*item)->indicator_image->to_delete = true;
			delete (*item);
			(*item) = nullptr;
			actual_room->map_indicators.erase(item);
			break;
		}
	}
}

void RoomManager::UpdateRoomEvents()
{

	switch (actual_room->update_number) { // IM SURE WE WILL USE THIS METHOD // ORIOL 21/04/2019 0:25
	default:
		break;
	}
	
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		if (map_background->drawable) {
			map_background->drawable = false;
			std::vector<Room*>::iterator item = rooms.begin();
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr) {
					(*item)->map_room_image->drawable = false;
					std::vector<MapIndicators*>::iterator it = (*item)->map_indicators.begin();
					for (; it != (*item)->map_indicators.end(); ++it) {
						(*it)->indicator_image->drawable = false;
					}
				}
			}
			App->scene->player->BlockControls(false);
		}
		else {
			int distance_x = actual_room->map_room_image->GetLocalPosition().x, distance_y = actual_room->map_room_image->GetLocalPosition().y;
			actual_room->map_room_image->SetPosRespectParent(CENTERED);
			distance_x = actual_room->map_room_image->GetLocalPosition().x - distance_x;
			distance_y = actual_room->map_room_image->GetLocalPosition().y - distance_y;
			map_background->drawable = true;
			actual_room->map_room_image->drawable = true;
			std::vector<MapIndicators*>::iterator it = actual_room->map_indicators.begin();
			int cont = 0;
			for (; it != actual_room->map_indicators.end(); ++it) {
				if ((*it) != nullptr && (*it)->indicator_image != nullptr) {
					(*it)->indicator_image->SetPosRespectParent((Position_Type)cont);
					(*it)->indicator_image->drawable = true;
					++cont;
				}
			}
			std::vector<Room*>::iterator item = rooms.begin();
			
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr && (*item) != actual_room) {
					(*item)->map_room_image->drawable = true;
					(*item)->map_room_image->SetPos((*item)->map_room_image->GetLocalPosition().x + distance_x, (*item)->map_room_image->GetLocalPosition().y + distance_y);
					std::vector<MapIndicators*>::iterator ind = (*item)->map_indicators.begin();
					cont = 0;
					for (; ind != (*item)->map_indicators.end(); ++ind) {
						if ((*ind) != nullptr && (*ind)->indicator_image != nullptr) {
							(*ind)->indicator_image->SetPosRespectParent((Position_Type)cont);
							(*ind)->indicator_image->drawable = true;
							++cont;
						}
					}
				}
			}
			App->scene->player->BlockControls(true);
		}
	}




	// if no more enemies door opens
	if (actual_room != nullptr && actual_room->active && actual_room->door_closed && !App->entity_manager->ThereAreEnemies()) {
		actual_room->door_closed = false;
		std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
		for (; item != actual_room->change_scene_points.end(); ++item) {
			if ((*item) != nullptr && ((*item)->change_type == LocationChangeScene::NEXT_A || (*item)->change_type == LocationChangeScene::NEXT_B)) {
				App->map->data.no_walkables.remove((*item)->location + iPoint{ 0,-1 });
			}
		}
	}

	if (actual_room != nullptr && actual_room->active && !App->entity_manager->ThereAreEnemies() && actual_room->room_type == RoomType::BOSS && !App->globals.Tutorial_first_time) {
		App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
}

ChangeScene::ChangeScene(const int & x, const int & y, LocationChangeScene type, const uint & id)
{
	location = { x,y };
	location = App->map->WorldToMap(location.x, location.y);
	change_type = type;
	id_next_room = id;
}
