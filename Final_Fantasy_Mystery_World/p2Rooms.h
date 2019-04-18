#ifndef _P2ROOMS_H_
#define _P2ROOMS_H_

#include "p2Point.h"
#include "PugiXml/src/pugixml.hpp"
#include <vector>
#include "e1Enemy.h"
#include <map>

struct Collider;

enum class LocationChangeScene {
	NEXT_A,
	NEXT_B,
	LAST_A,
	LAST_B,

	NONE
};

enum class RoomType {
	COMBAT,
	FOUNTAIN,
	BOSS,
	PACEFUL,

	NONE
};

struct ChangeScene {
	ChangeScene(const int & x, const int &y, LocationChangeScene type, const uint &id);
	iPoint location = { 0,0 };
	LocationChangeScene change_type = LocationChangeScene::NONE;
	uint id_next_room = 0;
};

class Room {

public:

	Room(const std::string &tmx_location, const int &id, const std::string &type, const std::string &cutscene_location);
	~Room();


public:
	std::string tmx_location;  
	uint id = 0; 
	std::vector<ChangeScene*> change_scene_points; 
	bool active = false;
	RoomType room_type = RoomType::NONE;
	std::string cutscene_location;
	std::map<int, int> entities;

};

class RoomManager {

public:

	RoomManager(pugi::xml_node &node);
	~RoomManager();

	void OnCollision(Collider* c1, Collider* C2);
	void LoadRoom(const int & id);
	void PlacePlayer();
	void LoadColliders();
	void PlayMusic();
	void PlayCutScene();

	void AddEntityToNotRepeat(iPoint pos);

public:
	Room* actual_room = nullptr;
	Room* last_room = nullptr;
	std::vector<Room*> rooms;
	LocationChangeScene player_next_pos = LocationChangeScene::NONE;



};
#endif // !_P2ROOMS_H

