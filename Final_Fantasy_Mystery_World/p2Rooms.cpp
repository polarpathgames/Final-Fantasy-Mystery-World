#include "p2Rooms.h"
#include "m1Collisions.h"
#include "m1Map.h"
#include "m1FadeToBlack.h"
#include "App.h"
#include "m1EasingSplines.h"
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

Room::Room(const std::string &tmx_location, const uint &id, const std::string &type, const std::string &cutscene_location, bool door_closed, const uint &update_number, const std::string &music_location)
	: tmx_location(tmx_location), id(id),door_closed(door_closed),update_number(update_number)
{
	if (!cutscene_location.empty()) {
		this->cutscene_location = cutscene_location;
	}

	if (!music_location.empty()) {
		music = App->audio->LoadMusic(music_location.data());
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
			delete (*it);
			(*it) = nullptr;
		}

	}
	map_indicators.clear();

	std::vector<DropInfo*>::iterator i = drops.begin();
	for (; i != drops.end(); ++i) {
		if ((*i) != nullptr) {
			delete (*i);
			(*i) = nullptr;
		}
	}
	drops.clear();

	entities.clear();

	properties.CleanUp();
}

RoomManager::RoomManager(const char* name)
{
	pugi::xml_parse_result result = room_manager_file.load_file("assets/xml/Rooms.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", "assets/xml/Rooms.xml", result.description());
	}
	else {
		LOG("XML was loaded succesfully!");

		if (strcmp(name, "tutorial") == 0) {
			mini_rect_map[0] = { 2132,2972,128,64 }; 
			mini_rect_map[1] = { 2260,2972,128,64 };
			mini_rect_map[2] = { 2388,2972,128,64 };
			mini_rect_map[3] = { 2516,2972,128,64 };
		}
		else if (strcmp(name, "quest2") == 0) {
			mini_rect_map[0] = { 2132,3067,128,64 };
			mini_rect_map[1] = { 2260,3067,128,64 };
			mini_rect_map[2] = { 2388,3067,128,64 };
			mini_rect_map[3] = { 2516,3067,128,64 };
		}
		else if (strcmp(name, "final_quest") == 0) {
			mini_rect_map[0] = { 2132,3156,128,64 };
			mini_rect_map[1] = { 2260,3156,128,64 };
			mini_rect_map[2] = { 2388,3156,128,64 };
			mini_rect_map[3] = { 2516,3156,128,64 };
		}

		map_background = App->gui->AddImage(-1600, 100, { 2078,4117,(int)App->win->width - 200, (int)App->win->height - 300 }, nullptr, App->gui->screen, false, false, false, false);
		map_zone = App->gui->AddImage(0, 0, { 200,1736,(int)App->win->width - 200, (int)App->win->height - 300 }, nullptr, map_background, false, false, false, false);

		for (pugi::xml_node room_node = room_manager_file.child("room_manager").child(name).child("room"); room_node; room_node = room_node.next_sibling("room")) {
			Room * r = DBG_NEW Room(room_node.child("location").child_value(), room_node.child("id").attribute("num").as_uint(), room_node.child("type").child_value(),
				room_node.child("cut_scene").child_value(), room_node.child("door").attribute("active").as_bool(false), room_node.child("update").attribute("num").as_uint(0u),
				room_node.child("music").child_value());
			for (pugi::xml_node property_room = room_node.child("properties").child("property"); property_room; property_room = property_room.next_sibling()) {
				r->properties.AddProperty(property_room.attribute("name").as_string("no_property"), property_room.attribute("value").as_int());
			}
			rooms.push_back(r);
		}
		if (strcmp(name,"quest2") == 0)
			rooms.front()->map_room_image = App->gui->AddImage(125, 125, mini_rect_map[2], nullptr, (u1GUI*)map_zone, false, false, false, false);

		else
			rooms.front()->map_room_image = App->gui->AddImage(125, 125, mini_rect_map[0], nullptr, (u1GUI*)map_zone, false, false, false, false);
		player_pos = App->gui->AddImage(0, 0, { 1830,2170,128,64 }, nullptr, rooms.front()->map_room_image, false, false, false, false);
		LoadRoom(1);
		
	}

	room_manager_file.reset();
}

RoomManager::~RoomManager()
{
	if (App->gui->IsInUIList(map_background))
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
							if ((App->globals.quest2_rocks_cave_destroyed && actual_room->update_number == 2) || actual_room->update_number != 2) {
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

	if (last_room != nullptr && last_room->update_number == 1 && actual_room->id == 1)
		App->globals.quest2_rocks_cave_destroyed = true;

	if (actual_room->room_type == RoomType::FOUNTAIN) {
		if (actual_room->fountain_drunk) {
			App->dialog->dialogTrees[1]->karma = -1;
		}
		else {
			App->dialog->dialogTrees[1]->karma = 0;
		}
	}



LoadColliders();
UpdateMap();
LoadEntities();
PlacePlayer();
PlayMusic();
PlayCutScene();

// Properties
if (actual_room->properties.GetValue("blizzard") == 1) {
	App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, 0, 0, "blizzard");
}

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
			else if ((*position)->name == "white_rock") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
				else {
					e1Rock* rock = (e1Rock*)App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					rock->hitted = true;
					rock->frame = { 955,187,32,37 };
					App->map->data.no_walkables.remove(rock->actual_tile + iPoint{ 0,-1 });
				}
			}

			else if ((*position)->name == "grey_rock") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
				else {
					e1Rock* rock = (e1Rock*)App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					rock->hitted = true;
					rock->frame = { 955,140,32,37 };
					App->map->data.no_walkables.remove(rock->actual_tile + iPoint{ 0,-1 });
				}
			}
			else if ((*position)->name == "breakable_barrel") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
				else {
					e1Rock* rock = (e1Rock*)App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					rock->hitted = true;
					rock->frame = { 613,122,35,31 };
					App->map->data.no_walkables.remove(rock->actual_tile + iPoint{ 0,-1 });
				}
			}
			else if ((*position)->name == "breakable_snowman") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
				else {
					e1Rock* rock = (e1Rock*)App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					rock->hitted = true;
					rock->frame = { 613,205,35,37 };
					App->map->data.no_walkables.remove(rock->actual_tile + iPoint{ 0,-1 });
				}
			}
			else if ((*position)->name == "ability1") {
				if (!App->globals.ability1_gained)
					App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}
			else if ((*position)->name == "ability_flash") {
				if (!App->globals.ability2_gained)
					App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}
			else if ((*position)->name == "rocks_door") {
				if (!App->globals.quest2_rocks_cave_destroyed)
					App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}
			else if ((*position)->name == "treasure_1" || (*position)->name == "treasure_boss" || (*position)->name == "treasure_quest3") {
				e1StaticEntity* treasure = (e1StaticEntity*)App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				if ((*position)->name == "treasure_1") {
					if ((App->globals.treasure_quest2_opened)) {
						treasure->frame = { 0,0,0,0 };
						treasure->interacting_state = e1StaticEntity::InteractingStates::NONE;
					}
				}
				else if ((*position)->name == "treasure_boss") {
					if ((App->globals.treasure_boss_opened)) {
						treasure->frame = { 0,0,0,0 };
						treasure->interacting_state = e1StaticEntity::InteractingStates::NONE;
					}
				}
				else if ((*position)->name == "treasure_quest3") {
					if ((App->globals.treasure_quest3_opened)) {
						treasure->frame = { 0,0,0,0 };
						treasure->interacting_state = e1StaticEntity::InteractingStates::NONE;
					}
				}

			}
			else if ((*position)->name == "InstaGoldRuppe" || (*position)->name == "InstaRedRuppe" || (*position)->name == "InstaBlueRuppe" || (*position)->name == "InstaGreenRuppe") {
				iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
				if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
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
						MapIndicators* indicator = DBG_NEW MapIndicators(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, "drop", App->gui->AddImage(0, 0, { 1380,2123,12,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
						actual_room->map_indicators.push_back(indicator);
					}
				}
			}
			else 
				App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->name == "enemy") {
			iPoint point = { App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y };
			e1Entity::EntityType ent_type = e1Entity::EntityType::NO_TYPE;
			if (std::find(actual_room->entities.begin(), actual_room->entities.end(), point) == actual_room->entities.end()) {
				if ((*position)->ent_type == "CarnivorousPlant") {
					ent_type = e1Entity::EntityType::CARNIVOROUS_PLANT;
				}
				else if ((*position)->ent_type == "BlueDog") {
					ent_type = e1Entity::EntityType::BLUE_DOG;
				}
				else if ((*position)->ent_type == "SuperPurpleFrog") {
					ent_type = e1Entity::EntityType::SUPER_PURPLE_FROG;
				}
				else if ((*position)->ent_type == "BlueSlime") {
					ent_type = e1Entity::EntityType::BLUE_SLIME;
				}
				else if ((*position)->ent_type == "StrangeFrog") {
					ent_type = e1Entity::EntityType::STRANGE_FROG;
				}
				else if ((*position)->ent_type == "MegaEye") {
					ent_type = e1Entity::EntityType::MEGA_EYE;
				}
				else if ((*position)->ent_type == "Spider") {
					ent_type = e1Entity::EntityType::SPIDER;
				}
				else if ((*position)->ent_type == "Cassio") {
					ent_type = e1Entity::EntityType::CASSIO;
				}
				else if ((*position)->ent_type == "BabyDrake") {
					ent_type = e1Entity::EntityType::BABY_DRAKE;
				}
				else if ((*position)->ent_type == "Frozen") {
					ent_type = e1Entity::EntityType::FROZEN;
				}
				App->entity_manager->CreateEntity(ent_type, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
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
	std::vector<DropInfo*>::iterator item = actual_room->drops.begin();
	for (; item != actual_room->drops.end(); ++item) {
		if ((*item) != nullptr) {
			switch ((*item)->type) {
			case DropsType::GREEN_RUPEE: {
				e1Drop* drop = (e1Drop*)App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "green_rupee");
				drop->SetGold(App->random.Generate(15, 25));
				break; }
			case DropsType::RED_RUPEE: {
				e1Drop* drop = (e1Drop*)App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "red_rupee");
				drop->SetGold(App->random.Generate(90, 110));
				break; }
			case DropsType::GOLD_RUPEE: {
				e1Drop* drop = (e1Drop*)App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "gold_rupee");
				drop->SetGold(App->random.Generate(300, 400));
				break; }
			case DropsType::BLUE_RUPEE: {
				e1Drop* drop = (e1Drop*)App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "blue_rupee");
				drop->SetGold(App->random.Generate(45, 65));
				break; }
			case DropsType::HEALTH_POTION:
				App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "health_potion");
				break;
			case DropsType::MANA_POTION:
				App->entity_manager->CreateEntity(e1Entity::EntityType::DROP, (*item)->location.x, (*item)->location.y, "mana_potion");
				break;
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
	App->audio->PlayMusic(actual_room->music, 1);
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
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneQueenQuest2.xml") == 0 && !App->globals.CutSceneQueenQuest2)
		{
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			App->globals.CutSceneQueenQuest2 = true;
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneFinalRoomQuest2.xml") == 0 && !App->globals.CutSceneFinalRoomQuest2)
		{
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
			App->globals.CutSceneFinalRoomQuest2 = true;
		}
		else if (strcmp(actual_room->cutscene_location.data(), "assets/xml/CutsceneAbility2Quest2.xml") == 0 && !App->globals.ability2_gained)
		{
			App->cutscene_manager->PlayCutscene(actual_room->cutscene_location.data());
		}
	}
		
}

void RoomManager::UpdateMap()
{
	if (actual_room->id != 1 && actual_room->map_room_image == nullptr && actual_room->update_number != 1) {
		if (player_next_pos == LocationChangeScene::NEXT_A) {
			if (actual_room->change_scene_points.size() >= 3) { // it has 2 new doors
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[2], nullptr, map_zone, false, false, false, false);
			}
			else if (actual_room->change_scene_points.size() == 1) { // no new doors, just an exit door 
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[3], nullptr, map_zone, false, false, false, false);
			}
			else { // it has one new door 
				std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
				for (; item != actual_room->change_scene_points.end(); ++item) {
					if ((*item) != nullptr) {
						if ((*item)->change_type == LocationChangeScene::NEXT_A) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[0], nullptr, map_zone, false, false, false, false);
							break;
						}
						else if ((*item)->change_type == LocationChangeScene::NEXT_B) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[1], nullptr, map_zone, false, false, false, false);
							break;
						}
					}
				}
			}
		}
		else if (player_next_pos == LocationChangeScene::NEXT_B) {
			if (actual_room->change_scene_points.size() >= 3) { // it has 2 new doors
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[2], nullptr, map_zone, false, false, false, false);
			}
			else if (actual_room->change_scene_points.size() == 1) { // no new doors, just an exit door 
				actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[3], nullptr, map_zone, false, false, false, false);
			}
			else { // it has one new door 
				std::vector<ChangeScene*>::iterator item = actual_room->change_scene_points.begin();
				for (; item != actual_room->change_scene_points.end(); ++item) {
					if ((*item) != nullptr) {
						if ((*item)->change_type == LocationChangeScene::NEXT_A) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[0], nullptr, map_zone, false, false, false, false);
							break;
						}
						else if ((*item)->change_type == LocationChangeScene::NEXT_B) {
							actual_room->map_room_image = App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x - 96, last_room->map_room_image->GetLocalPosition().y - 48, mini_rect_map[1], nullptr, map_zone, false, false, false, false);
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
	else if (actual_room->map_room_image == nullptr && actual_room->update_number == 1){
		actual_room->map_room_image = App->gui->AddImage(rooms.front()->map_room_image->GetLocalPosition().x - 96, rooms.front()->map_room_image->GetLocalPosition().y - 48, mini_rect_map[3], nullptr, map_zone, false, false, false, false);
		App->gui->AddImage(last_room->map_room_image->GetLocalPosition().x + 50, last_room->map_room_image->GetLocalPosition().y - 125, mini_rect_map[3], nullptr, actual_room->map_room_image, true, false, false, false);
		
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

void RoomManager::AddDrop(iPoint pos, DropsType type)
{
	DropInfo* drop = DBG_NEW DropInfo(pos.x, pos.y, type);
	actual_room->drops.push_back(drop);
	MapIndicators* indicator = DBG_NEW MapIndicators(pos.x, pos.y, "drop", App->gui->AddImage(0, 0, { 1380,2123,12,13 }, nullptr, actual_room->map_room_image, false, false, false, false));
	actual_room->map_indicators.push_back(indicator);
}

void RoomManager::DeleteDrop(iPoint pos, DropsType type)
{
	std::vector<DropInfo*>::iterator item = actual_room->drops.begin();
	for (; item != actual_room->drops.end(); ++item) {
		if ((*item) != nullptr && (*item)->location == pos && (*item)->type == type) {
			delete (*item);
			(*item) = nullptr;
			actual_room->drops.erase(item);
			break;
		}
	}
	std::vector < MapIndicators*>::iterator it = actual_room->map_indicators.begin();
	for (; it != actual_room->map_indicators.end(); ++it) {
		if ((*it) != nullptr && (*it)->location == pos && (*it)->indicator_type == "drop") {
			(*it)->indicator_image->to_delete = true;
			delete (*it);
			(*it) = nullptr;
			actual_room->map_indicators.erase(it);
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
	
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_BACK)) {
		if (!map_active && App->scene->menu_state == StatesMenu::NO_MENU && App->scene->player->state == State::IDLE && !App->scene->player->turn_done) {
			int distance_x = actual_room->map_room_image->GetLocalPosition().x, distance_y = actual_room->map_room_image->GetLocalPosition().y;
			player_pos->parent = actual_room->map_room_image;
			player_pos->SetPosRespectParent(CENTERED);
			player_pos->drawable = true;
			map_zone->SetPosRespectParent(CENTERED);
			actual_room->map_room_image->SetPosRespectParent(CENTERED);
			distance_x = actual_room->map_room_image->GetLocalPosition().x - distance_x;
			distance_y = actual_room->map_room_image->GetLocalPosition().y - distance_y;
			map_background->drawable = true;
			actual_room->map_room_image->drawable = true;
			std::vector<MapIndicators*>::iterator it = actual_room->map_indicators.begin();
			int cont = 0;
			for (; it != actual_room->map_indicators.end(); ++it) {
				if ((*it) != nullptr && (*it)->indicator_image != nullptr && (*it)->indicator_image->parent != nullptr) {
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
			map_background->SetPos(-1600, map_background->GetLocalPosition().y);
			App->easing_splines->CreateSpline(&map_background->position.x, 100, 1500, TypeSpline::EASE_OUT_QUINT);
			App->scene->player->BlockControls(true);
			App->scene->SetMenuState(StatesMenu::MAP);
			map_active = true;
		}
		else if (map_active){
			App->easing_splines->CreateSpline(&map_background->position.x, -1600, 1500, TypeSpline::EASE_OUT_QUINT);
			App->scene->player->BlockControls(false);
			App->scene->SetMenuState(StatesMenu::NO_MENU);
			map_active = false;
		}
	}

	if (map_active) {
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			Room* last_down = rooms.front();
			std::vector<Room*>::iterator item = rooms.begin();
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr && (*item)->map_room_image->GetGlobalPosition().y > last_down->map_room_image->GetGlobalPosition().y) {
					last_down = (*item);
				}
			}
			if (last_down->map_room_image->GetGlobalPosition().y >= map_background->GetGlobalPosition().y) {
				map_zone->SetPos(map_zone->GetLocalPosition().x, map_zone->GetLocalPosition().y - 300 * App->GetDeltaTime());
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			Room* first_up = rooms.front();
			std::vector<Room*>::iterator item = rooms.begin();
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr && (*item)->map_room_image->GetGlobalPosition().y < first_up->map_room_image->GetGlobalPosition().y) {
					first_up = (*item);
				}
			}
			if (first_up->map_room_image->GetGlobalPosition().y + first_up->map_room_image->section.h <= map_background->GetGlobalPosition().y + map_background->section.h) {
				map_zone->SetPos(map_zone->GetLocalPosition().x, map_zone->GetLocalPosition().y + 300 * App->GetDeltaTime());
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			Room* right = rooms.front();
			std::vector<Room*>::iterator item = rooms.begin();
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr && (*item)->map_room_image->GetGlobalPosition().x < right->map_room_image->GetGlobalPosition().x) {
					right = (*item);
				}
			}
			if (right->map_room_image->GetGlobalPosition().x + right->map_room_image->section.w <= map_background->GetGlobalPosition().x + map_background->section.w) {
				map_zone->SetPos(map_zone->GetLocalPosition().x + 300 * App->GetDeltaTime(), map_zone->GetLocalPosition().y);
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			Room* left = rooms.front();
			std::vector<Room*>::iterator item = rooms.begin();
			for (; item != rooms.end(); ++item) {
				if ((*item) != nullptr && (*item)->map_room_image != nullptr && (*item)->map_room_image->GetGlobalPosition().x > left->map_room_image->GetGlobalPosition().x) {
					left = (*item);
				}
			}
			if (left->map_room_image->GetGlobalPosition().x >= map_background->GetGlobalPosition().x) {
				map_zone->SetPos(map_zone->GetLocalPosition().x - 300 * App->GetDeltaTime(), map_zone->GetLocalPosition().y);
			}
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

	if (actual_room != nullptr && actual_room->active && !App->entity_manager->ThereAreEnemies() && actual_room->room_type == RoomType::BOSS && !App->globals.Tutorial_first_time && App->map->actual_map == Maps::TUTORIAL) {
		App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
	if (actual_room != nullptr && actual_room->active && !App->entity_manager->ThereAreEnemies() && actual_room->room_type == RoomType::BOSS && App->map->actual_map == Maps::QUEST2) {
		App->globals.ice_queen_killed = true;
		/*App->fade_to_black->FadeToBlack(Maps::LOBBY);*/
	}
	if (actual_room != nullptr && actual_room->active && !App->entity_manager->ThereAreEnemies() && actual_room->room_type == RoomType::BOSS && App->map->actual_map == Maps::FINAL_QUEST && !App->globals.CutsceneFinalGame) {
		App->cutscene_manager->PlayCutscene("CutsceneFinalGame.xml");
		App->globals.CutsceneFinalGame = true;
		/*App->fade_to_black->FadeToBlack(Maps::LOBBY);*/
	}
}

ChangeScene::ChangeScene(const int & x, const int & y, LocationChangeScene type, const uint & id)
{
	location = { x,y };
	location = App->map->WorldToMap(location.x, location.y);
	change_type = type;
	id_next_room = id;
}
