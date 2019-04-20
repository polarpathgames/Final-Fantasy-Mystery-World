#ifndef _P2ROOMS_H_
#define _P2ROOMS_H_

#include "p2Point.h"
#include "PugiXml/src/pugixml.hpp"
#include <vector>
#include "SDL_mixer/include/SDL_mixer.h"
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
	BOSS_TUTORIAL,

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

	Room(const std::string &tmx_location, const uint &id, const std::string &type, const std::string &cutscene_location, bool door_closed, const uint & update_number);
	~Room();


public:
	std::string tmx_location;  
	uint id = 0u; 
	std::vector<ChangeScene*> change_scene_points; 
	bool active = false;
	RoomType room_type = RoomType::NONE;
	std::string cutscene_location;
	std::vector<iPoint> entities;
	bool door_closed = false;
	uint update_number = 0u;
};

class RoomManager {

public:

	RoomManager(pugi::xml_node &node);
	~RoomManager();

	void OnCollision(Collider* c1, Collider* C2);
	void LoadRoom(const int & id);
	void AddEntityToNotRepeat(iPoint pos);
	void UpdateRoomEvents();

private:

	void LoadEntities();
	void PlacePlayer();
	void LoadColliders();
	void PlayMusic();
	void PlayCutScene();
	
public:

	Room* actual_room = nullptr;
	Room* last_room = nullptr;
	std::vector<Room*> rooms;
	LocationChangeScene player_next_pos = LocationChangeScene::NONE;

	Mix_Music* mus_paceful;
	Mix_Music* mus_boss;
	Mix_Music* mus_combat;
	Mix_Music* mus_fountain;



};
#endif // !_P2ROOMS_H

