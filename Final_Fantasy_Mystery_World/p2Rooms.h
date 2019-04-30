#ifndef _P2ROOMS_H_
#define _P2ROOMS_H_

#include "p2Point.h"
#include "PugiXml/src/pugixml.hpp"
#include <vector>
#include "SDL_mixer/include/SDL_mixer.h"
#include "e1Enemy.h"
#include "e1Drop.h"
#include "SDL/include/SDL_rect.h"

class u1Image;

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

enum COLLIDER_TYPE;


struct ChangeScene {
	ChangeScene(const int & x, const int &y, LocationChangeScene type, const uint &id);
	iPoint location = { 0,0 };
	LocationChangeScene change_type = LocationChangeScene::NONE;
	uint id_next_room = 0;
};

struct MapIndicators {
	MapIndicators(const int &x, const int &y, const std::string indicator_type,u1Image * image) : location(x,y), indicator_image(image), indicator_type(indicator_type) {}
	iPoint location{ 0,0 };
	u1Image * indicator_image = nullptr;
	std::string indicator_type;
};

struct DropInfo {
	DropInfo(const int &x, const int &y, const DropsType &type) : location(x,y), type(type) {}
	iPoint location{ 0,0 };
	DropsType type = DropsType::NONE;
};

class Room {

public:

	Room(const std::string &tmx_location, const uint &id, const std::string &type, const std::string &cutscene_location, bool door_closed, const uint & update_number);
	~Room();


public:

	std::string tmx_location;  
	std::string cutscene_location;

	uint id = 0u; 
	uint update_number = 0u;

	std::vector<ChangeScene*> change_scene_points; 
	std::vector<iPoint> entities;
	std::vector<DropInfo*> drops;
	std::vector<MapIndicators*> map_indicators;

	bool active = false;
	bool door_closed = false;
	
	RoomType room_type = RoomType::NONE;
	
	u1Image * map_room_image = nullptr;

};

class RoomManager {

public:

	RoomManager(const char* name);
	~RoomManager();

	void OnCollision(Collider* c1, Collider* C2);
	bool ChangeRoom(COLLIDER_TYPE type, bool debug_change = false);
	void LoadRoom(const int & id);
	void AddEntityToNotRepeat(iPoint pos);
	void AddDrop(iPoint pos, DropsType type);
	void DeleteDrop(iPoint pos, DropsType type);
	void UpdateRoomEvents();

private:

	void LoadEntities();
	void PlacePlayer();
	void LoadColliders();
	void PlayMusic();
	void PlayCutScene();
	void UpdateMap();
	
public:

	Room* actual_room = nullptr;
	Room* last_room = nullptr;
	std::vector<Room*> rooms;
	LocationChangeScene player_next_pos = LocationChangeScene::NONE;

	pugi::xml_document room_manager_file;

	Mix_Music* mus_paceful;
	Mix_Music* mus_boss;
	Mix_Music* mus_combat;
	Mix_Music* mus_fountain;

private:

	u1Image * map_background = nullptr;



};
#endif // !_P2ROOMS_H

